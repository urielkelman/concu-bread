//
// Created by urielkelman on 16/5/20.
//

#include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero() : Maestro("maestroPanadero.lock"){
    this->cadenaIdentificadora = "Maestro panadero";
}

MaestroPanadero::~MaestroPanadero() {

}

void MaestroPanadero::cocinar(MasaMadre masaMadre) {
    LOG_DEBUG("Maestro panadero con id: " + to_string(getpid()) + ". Comenzando a preparar par...");
    sleep(this->TIEMPO_COCCION_PAN);
    LOG_DEBUG("Maestro panadero con id: " + to_string(getpid()) + ". Pan preparado. Entregado a repartidor.");
}

