//
// Created by urielkelman on 16/5/20.
//

#include "Recepcionista.h"
#include <unistd.h>

#include "Panaderia.h"

Recepcionista::Recepcionista() : lockComunicacionConPanaderia("recepcionista.lock"){
    this->cadenaIdentificadora = "Recepcionista";
}

void Recepcionista::esperarPorSolicitudes() {
    Pedido pedido;
    while(this->continuarAtendiendoPedidos){
        this->lockComunicacionConPanaderia.tomarLock();
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Lock adquirido para leer del pipe de "
                                                                   "comunicacion con la panaderia.");
        this->comunicacionConPanaderia.leer(static_cast<void*>(&pedido), sizeof(Pedido));
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Llego un pedido "
                  "de " + Panaderia::TIPO_A_CADENA[pedido.tipoDePedido] + ". Numero de pedido: " + to_string(pedido.numeroDePedido));
        this->lockComunicacionConPanaderia.liberarLock();

        if(pedido.tipoDePedido == NOTIFICACION_DE_CIERRE){
            LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Procedo con la orden, el dia de trabajo "
                      "ha terminado. Voy a cerrarme e ir a mi casa.");
            this->continuarAtendiendoPedidos = false;
        } else {
            this->entregarPedidoAMaestro(pedido);
        }

        usleep(100);
    }

    exit(0);
}

Recepcionista::~Recepcionista() {
}

void Recepcionista::configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    this->comunicacionConPanaderia = primerPipe;
    this->comunicacionConMaestrosPanaderos = segundoPipe;
    this->comunicacionConMaestrosPizzeros = tercerPipe;
}

void Recepcionista::entregarPedidoAMaestro(Pedido pedido) {
    if (pedido.tipoDePedido == PAN) {
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Entregando pedido de pan con "
                                                                   "id: " + to_string(pedido.numeroDePedido));
        this->comunicacionConMaestrosPanaderos.escribir(static_cast<const void *>(&pedido), sizeof(Pedido));
    } else {
        LOG_DEBUG("Recepcionista con id: " + to_string(getpid()) + ". Entregando pedido de pizza con "
                                                                   "id: " + to_string(pedido.numeroDePedido));
        this->comunicacionConMaestrosPizzeros.escribir(static_cast<const void *>(&pedido), sizeof(Pedido));
    }
}