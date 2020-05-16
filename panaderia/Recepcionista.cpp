//
// Created by urielkelman on 16/5/20.
//

#include "Recepcionista.h"
#include <unistd.h>

Recepcionista::Recepcionista() {
    this->cadenaIdentificadora = "recepcionista";
}

void Recepcionista::esperarPorSolicitudes() {
    while(true){
        LOG_DEBUG("Esperando por pedidos. Id: " + to_string(getpid()));
        sleep(10);
    }
}

Recepcionista::~Recepcionista() {

}
