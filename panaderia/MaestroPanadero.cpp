//
// Created by urielkelman on 16/5/20.
//

#include "MaestroPanadero.h"

MaestroPanadero::MaestroPanadero() : Maestro("maestroPanadero.lock"){
    this->cadenaIdentificadora = "maestro panadero";
}

MaestroPanadero::~MaestroPanadero() {

}

void MaestroPanadero::cocinar() {

}

