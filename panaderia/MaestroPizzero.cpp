//
// Created by urielkelman on 17/5/20.
//

#include "MaestroPizzero.h"

MaestroPizzero::MaestroPizzero() : Maestro("maestroPizzero.lock") {
    this->cadenaIdentificadora = "maestro pizzero";
}

MaestroPizzero::~MaestroPizzero() {

}

void MaestroPizzero::cocinar() {

}
