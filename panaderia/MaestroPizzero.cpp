//
// Created by urielkelman on 17/5/20.
//

#include "MaestroPizzero.h"

MaestroPizzero::MaestroPizzero() : Maestro("maestroPizzero.lock") {
    this->cadenaIdentificadora = "Maestro pizzero";
}

MaestroPizzero::~MaestroPizzero() {

}

void MaestroPizzero::cocinar(MasaMadre) {
    int tiempoDeCoccionAleatoria = this->obtenerTiempoDeCoccionAleatoria();
    LOG_DEBUG("Maestro panadero con id: " + to_string(getpid()) + ". Comenzando a preparar pizza. "
              "Tiempo de coccion: " + to_string(tiempoDeCoccionAleatoria));
    sleep(tiempoDeCoccionAleatoria);
    LOG_DEBUG("Maestro panadero con id: " + to_string(getpid()) + ". Pizza preparado. Entregado a repartidor.");
}

int MaestroPizzero::obtenerTiempoDeCoccionAleatoria() {
    srand(time(NULL));
    int numeroRandom = 2 + rand() % 3 + 1;
    return numeroRandom;
}
