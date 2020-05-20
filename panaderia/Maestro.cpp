//
// Created by urielkelman on 16/5/20.
//

#include "Maestro.h"
#include "Panaderia.h"

Maestro::Maestro(string nombreLockComunicacionConRecepcionistas) :
        lockComunicacionConRecepcionistas(LockFile(nombreLockComunicacionConRecepcionistas)) {
}

Maestro::~Maestro() {

}

void Maestro::esperarPorSolicitudes() {
    Pedido pedido;
    while(this->continuarAtendiendoPedidos){
        this->lockComunicacionConRecepcionistas.tomarLock();
        LOG_DEBUG(this->cadenaIdentificadora + " con id: " + to_string(getpid()) + ". Lock adquirido para leer del pipe de "
                  "comunicacion con los recepcionistas.");
        this->comunicacionConRecepcionistas.leer(static_cast<void*>(&pedido), sizeof(Pedido));
        LOG_DEBUG(this->cadenaIdentificadora + " con id: " + to_string(getpid()) + ". Se recibio un pedido " +
                  Panaderia::CONTENIDO_A_CADENA[pedido.contenidoDePedido] + " de " + Panaderia::TIPO_A_CADENA[pedido.tipoDePedido] +
                  ". El numero de pedido es: " + to_string(pedido.numeroDePedido));
        this->lockComunicacionConRecepcionistas.liberarLock();
        this->procesarPedido(pedido);
        usleep(100);
    }

    exit(0);
}

void Maestro::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConRecepcionistas = primerPipe;
    this->comunicacionConMaestroMasaMadre = segundoPipe;
    this->recepcionMasaMadre = tercerPipe;
}

void Maestro::procesarPedido(Pedido pedido) {
    if(pedido.contenidoDePedido == VACIO){
        LOG_DEBUG(this->cadenaIdentificadora + " con id: " + to_string(getpid()) + ". Procedo con la orden, mi dia "
                  "laboral ha terminado. Me voy a mi casa.");
        this->continuarAtendiendoPedidos = false;
    } else{
        LOG_DEBUG(this->cadenaIdentificadora + " con id: " + to_string(getpid()) + ". Solicitando masa madre"
                  "al gran maestro.");
        this->comunicacionConMaestroMasaMadre.escribir("M", sizeof(char));

    }
}


