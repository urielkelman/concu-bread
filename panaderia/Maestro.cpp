//
// Created by urielkelman on 16/5/20.
//


#include "Maestro.h"
#include "../concurrencia/seniales/SignalHandler.h"
#include "../concurrencia/seniales/EmpleadoSIGINTHandler.h"

Maestro::Maestro(const char* nombreLockComunicacionConRecepcionistas) :
        lockComunicacionConRecepcionistas(nombreLockComunicacionConRecepcionistas),
        lockPedidosVigentes("locks/pedidosvigentes.lock"),
        lockMasaMadre("locks/masamadre.lock"),
        pedidosVigentes(MemoriaCompartida<int>('A')),
        comunicacionConRepartidor("/tmp/fifo-repartidores"){

}

Maestro::~Maestro() {

}

void Maestro::esperarPorSolicitudes() {
    this->comunicacionConRepartidor.abrir();
    EmpleadoSIGINTHandler maestroSIGINTHandler(this);
    SignalHandler::getInstance()->registrarHandler(SIGINT, &maestroSIGINTHandler);

    Pedido pedido;
    while(this->continuarAtendiendoPedidos){
        this->lockComunicacionConRecepcionistas.tomarLock();
        LOG_DEBUG(

        string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Lock adquirido para leer del pipe de "
                  "comunicacion con los recepcionistas.");
        this->comunicacionConRecepcionistas.leer(static_cast<void*>(&pedido), sizeof(Pedido));
        LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Se recibio un pedido " +
                  Panaderia::CONTENIDO_A_CADENA[pedido.contenidoDePedido] + " de " + Panaderia::TIPO_A_CADENA[pedido.tipoDePedido] +
                  ". El numero de pedido es: " + to_string(pedido.numeroDePedido));
        this->lockComunicacionConRecepcionistas.liberarLock();
        this->numeroDePedidoActual = pedido.numeroDePedido;
        this->procesarPedido(pedido);
    }

    this->liberarRecursos();
    exit(0);
}

void Maestro::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConRecepcionistas = primerPipe;
    this->comunicacionConMaestroMasaMadre = segundoPipe;
    this->recepcionMasaMadre = tercerPipe;
}

void Maestro::procesarPedido(Pedido pedido) {
    string codigoDePedido;
    if(pedido.contenidoDePedido == VACIO){
        LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Se proceso pedido con id "
                  + to_string(pedido.numeroDePedido) + ". Procedo con la orden, mi dia laboral ha terminado. Me voy a mi casa, "
                  "no sin antes avisar al maestro de la masa madre.");
        codigoDePedido = "C";
        this->continuarAtendiendoPedidos = false;
    } else {
        LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Se proceso pedido con id "
                  + to_string(pedido.numeroDePedido) + ". Solicitando masa madre al gran maestro.");
        codigoDePedido = "P";
    }

    this->comunicacionConMaestroMasaMadre.escribir(codigoDePedido.c_str(), sizeof(NotificacionMaestro));
    this->lockPedidosVigentes.tomarLock();
    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + + ". Adquirido lock para leer "
              "la memoria compartida de pedidos vigentes.");
    int totalPedidosVigentes = this->pedidosVigentes.leer();
    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + + ". Se leyeron " + to_string(totalPedidosVigentes) +
              " pedidos vigentes. Se escriben " + to_string(totalPedidosVigentes+1) + " pedidos vigentes.");
    this->pedidosVigentes.escribir(totalPedidosVigentes + 1);
    this->lockPedidosVigentes.liberarLock();

    if(this->continuarAtendiendoPedidos){
        MasaMadre masaMadre = this->retirarMasaMadre();
        TipoDePedido contenido = this->cocinar(masaMadre);
        this->entregarPedido(contenido);
    }
}

void Maestro::liberarRecursos() {
    SignalHandler::destruir();

    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Cerrando memoria compartida de pedidos vigentes");
    this->pedidosVigentes.liberar();

    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Cerrando comunicacion con los recepcionistas.");
    this->comunicacionConRecepcionistas.cerrar();

    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Cerrando comunicacion con el maestro de la masa madre.");
    this->comunicacionConMaestroMasaMadre.cerrar();

    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Cerrando recepcion de masa madre.");
    this->recepcionMasaMadre.cerrar();

    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Cerrando comunicacion con repartidores.");
    this->comunicacionConRepartidor.cerrar();
}

MasaMadre Maestro::retirarMasaMadre() {
    MasaMadre masaMadre;
    this->lockMasaMadre.tomarLock();
    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid()) + ". Adquirido lock para leer el pipe y retirar la masa madre."    );
    this->recepcionMasaMadre.leer(&masaMadre, sizeof(RacionMasaMadre));
    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid())  + ". Recibí masa madre para cocinar. "
              "Sera utilizada para el pedido: " + to_string(this->numeroDePedidoActual));
    this->lockMasaMadre.liberarLock();
    return masaMadre;
}

void Maestro::entregarPedido(TipoDePedido tipoDePedido) {
    CajaConPedido pedidoTerminado;
    pedidoTerminado.numeroDePedido = this->numeroDePedidoActual;
    pedidoTerminado.tipoDePedido = tipoDePedido;
    LOG_DEBUG(string(this->cadenaIdentificadora) + " con id: " + to_string(getpid())  + ". Entregando "
              "pedido terminado numero: " + to_string(this->numeroDePedidoActual));
    this->comunicacionConRepartidor.escribir(static_cast<void*>(&pedidoTerminado), sizeof(CajaConPedido));
}



