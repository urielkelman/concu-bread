//
// Created by urielkelman on 16/5/20.
//

#include "Maestro.h"

Maestro::Maestro() {
    this->cadenaIdentificadora = "maestro pizzero";
}

void Maestro::esperarPorSolicitudes() {
    while(true){
        LOG_DEBUG("Maestro pizzero esperando por pedidos. Id: " + to_string(getpid()));
        sleep(10);
    }
}

Maestro::~Maestro() {

}

void Maestro::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConRecepcionistas = primerPipe;
    this->comunicacionConMaestroMasaMadre = segundoPipe;
    this->recepcionMasaMadre = tercerPipe;
}


