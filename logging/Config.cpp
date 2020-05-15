//
// Created by urielkelman on 15/5/20.
//

#include "Config.h"

void Config::configurarMaestrosPizzeros(int maestrosPizzeros) {
    this->maestrosPizzeros = maestrosPizzeros;
}

void Config::configurarMaestrosPanaderos(int maestrosPanaderos) {
    this->maestrosPanaderos = maestrosPanaderos;
}

void Config::configurarRecepcionistas(int recepcionistas) {
    this->recepcionistas = recepcionistas;
}

void Config::configurarCorrectitud(bool correctitud) {
    this->correctitud = correctitud;
}

bool Config::fueCorrectamenteIngresada() {
    return this->correctitud;
}
