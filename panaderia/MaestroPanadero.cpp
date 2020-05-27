//
// Created by urielkelman on 16/5/20.
//

#include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero() : Maestro("locks/maestroPanadero.lock"){
    this->cadenaIdentificadora = "Maestro panadero";
}

MaestroPanadero::~MaestroPanadero() {
}

TipoDePedido MaestroPanadero::cocinar(MasaMadre masaMadre) {
    LOG_DEBUG("Maestro panadero con id: " + to_string(getpid()) + ". Comenzando a preparar pan caliente.");
    usleep(this->TIEMPO_COCCION_PAN);
    LOG_DEBUG("Maestro panadero con id: " + to_string(getpid()) + ". Pan preparado.");
    return PAN;
}

