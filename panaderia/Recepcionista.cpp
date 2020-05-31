//
// Created by urielkelman on 16/5/20.
//

#include "Recepcionista.h"
#include <unistd.h>

#include "Panaderia.h"
#include "../concurrencia/seniales/EmpleadoSIGINTHandler.h"

int Recepcionista::BUFFSIZE_PEDIDO = 10;

Recepcionista::Recepcionista() : lockComunicacionConPanaderia("locks/recepcionista.lock"){
    this->cadenaIdentificadora = "Recepcionista";

}

void Recepcionista::esperarPorSolicitudes() {
    EmpleadoSIGINTHandler recepcionistaSIGINTHandler(this);
    SignalHandler::getInstance()->registrarHandler(SIGINT, &recepcionistaSIGINTHandler);

    Pedido pedido;
    while(this->continuarAtendiendoPedidos){
        char buffer[BUFFSIZE_PEDIDO];
        this->lockComunicacionConPanaderia.tomarLock();
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Lock adquirido para leer del pipe de "
                                                                   "comunicacion con la panaderia.");
        this->comunicacionConPanaderia.leer(static_cast<void*>(buffer), BUFFSIZE_PEDIDO);
        pedido = SerializadorDePedidos::deserializarPedido(buffer);
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Llego un pedido "
                  "de " + Panaderia::TIPO_A_CADENA[pedido.tipoDePedido] + ". Numero de pedido: " + to_string(pedido.numeroDePedido));
        this->lockComunicacionConPanaderia.liberarLock();

        if(pedido.tipoDePedido == NOTIFICACION_DE_CIERRE){
            LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Procedo con la orden, el dia de trabajo "
                      "ha terminado. Voy a cerrarme e ir a mi casa.");
            this->continuarAtendiendoPedidos = false;
        } else {
            this->entregarPedidoAMaestro(pedido);
        }
    }
    this->liberarRecursos();
    exit(0);
}

Recepcionista::~Recepcionista() {
}

void Recepcionista::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConPanaderia = primerPipe;
    this->comunicacionConMaestrosPanaderos = segundoPipe;
    this->comunicacionConMaestrosPizzeros = tercerPipe;
}

void Recepcionista::entregarPedidoAMaestro(Pedido pedido) {
    if(pedido.tipoDePedido == PAN) {
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Entregando pedido de pan con "
                  "id: " + to_string(pedido.numeroDePedido));
        string pedidoSerializado = SerializadorDePedidos::serializarPedido(pedido);
        printf("Recepcionista escribe: %s\n", pedidoSerializado.c_str());
        this->comunicacionConMaestrosPanaderos.escribir(static_cast<const void*>(pedidoSerializado.c_str()), BUFFSIZE_PEDIDO);
    } else {
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Entregando pedido de pizza con "
                 "id: " + to_string(pedido.numeroDePedido));
        string pedidoSerializado = SerializadorDePedidos::serializarPedido(pedido);
        printf("Recepcionista escribe: %s\n", pedidoSerializado.c_str());
        this->comunicacionConMaestrosPizzeros.escribir(static_cast<const void*>(pedidoSerializado.c_str()), BUFFSIZE_PEDIDO);
    }
}

void Recepcionista::liberarRecursos() {
    SignalHandler::destruir();

    LOG_DEBUG("Recepcionista con id: "+ to_string(getpid()) + ". Cerrando comunicacion con panaderia.");
    this->comunicacionConPanaderia.cerrar();
    LOG_DEBUG("Recepcionista con id: "+ to_string(getpid()) + ". Cerrando comunicacion con maestros pizzeros.");
    this->comunicacionConMaestrosPizzeros.cerrar();
    LOG_DEBUG("Recepcionista con id: "+ to_string(getpid()) + ". Cerrando comunicacion con maestros panaderos.");
    this->comunicacionConMaestrosPanaderos.cerrar();

}
