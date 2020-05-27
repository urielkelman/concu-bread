//
// Created by urielkelman on 15/5/20.
//

#include <iostream>
#include "Config.h"

Config::Config() {}
Config::~Config() {}

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
    if(this->recepcionistas < 1 || this->maestrosPizzeros < 1 || this->maestrosPanaderos < 1){
        this->correctitud = false;
    } else {
        this->correctitud = correctitud;
    }
}

bool Config::fueCorrectamenteIngresada() {
    return this->correctitud;
}

void Config::configurarNivelDeLogging(string nivel) {
    try {
        nivelDeLogging = Logging::ObtenerNivelDeLogging(nivel);
    } catch (const char* mensajeDeError) {
        cout << mensajeDeError << "\n";
        this->configurarCorrectitud(false);
    }
}

int Config::obtenerMaestrosPizzeros() {
    return this->maestrosPizzeros;
}

int Config::obtenerMaestrosPanaderos() {
    return this->maestrosPanaderos;
}

int Config::obtenerRecepcionistas() {
    return this->recepcionistas;
}

NivelDeLogging Config::obtenerNivelDeLogging() {
    return this->nivelDeLogging;
}

void Config::configurarCantidadDePedidos(int cantidadDePedidos) {
    this->cantidadDePedidos = cantidadDePedidos;
}

int Config::obtenerCantidadDePedidos() {
    return this->cantidadDePedidos;
}



