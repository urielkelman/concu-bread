//
// Created by urielkelman on 16/5/20.
//

#include "Maestro.h"
#include "Panaderia.h"

Maestro::Maestro() {}

void Maestro::esperarPorSolicitudes() {
    Pedido pedido;
    while(this->continuarAtendiendoPedidos){

    }

    LOG_DEBUG( this->cadenaIdentificadora + " esperando por pedidos. Id: " + to_string(getpid()));
    sleep(1);
    exit(0);
}

Maestro::~Maestro() {

}

void Maestro::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConRecepcionistas = primerPipe;
    this->comunicacionConMaestroMasaMadre = segundoPipe;
    this->recepcionMasaMadre = tercerPipe;
}


