//
// Created by urielkelman on 16/5/20.
//

#include "Recepcionista.h"
#include <unistd.h>

#include "Panaderia.h"

Recepcionista::Recepcionista() : lockComunicacionConPanaderia(LockFile("Recepcionista.cpp")) {
    this->cadenaIdentificadora = "recepcionista";
}

void Recepcionista::esperarPorSolicitudes() {
    Pedido pedido;
    bool continuarProcesandoPedidos = true;
    while(continuarProcesandoPedidos){
        this->lockComunicacionConPanaderia.tomarLock();
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Lock adquirido para leer del pipe de "
                                                                   "comunicacion con la panaderia.");
        this->comunicacionConPanaderia.leer(static_cast<void*>(&pedido), sizeof(Pedido));
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Llego un pedido "
                  "de " + Panaderia::TIPO_A_CADENA[pedido.tipoDePedido] + ". Numero de pedido: " + to_string(pedido.numeroDePedido));
        this->lockComunicacionConPanaderia.liberarLock();
        sleep(1);
    }
}

Recepcionista::~Recepcionista() {

}

void Recepcionista::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConPanaderia = primerPipe;
    this->comunicacionConMaestrosPanaderos = segundoPipe;
    this->comunicacionConMaestrosPizzeros = tercerPipe;
}
