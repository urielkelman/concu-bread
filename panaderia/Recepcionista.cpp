//
// Created by urielkelman on 16/5/20.
//

#include "Recepcionista.h"
#include <unistd.h>

#include "Panaderia.h"

Recepcionista::Recepcionista() {
    this->cadenaIdentificadora = "recepcionista";
}

void Recepcionista::esperarPorSolicitudes() {
    Pedido pedido;
    while(true){
        this->comunicacionConPanaderia.leer(static_cast<void*>(&pedido), sizeof(Pedido));
        LOG_DEBUG("Soy el recepcionista con id: " + to_string(getpid()) + ". Llego un pedido "
                 "de " + to_string(pedido.tipoDePedido) + ". El numero de pedido es: " + to_string(pedido.numeroDePedido));
    }
}

Recepcionista::~Recepcionista() {

}

void Recepcionista::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConPanaderia = primerPipe;
    this->comunicacionConMaestrosPanaderos = segundoPipe;
    this->comunicacionConMaestrosPizzeros = tercerPipe;
}
