//
// Created by urielkelman on 24/5/20.
//

#include "Repartidor.h"
#include "../concurrencia/seniales/RepartidorSIGINTHandler.h"
#include "../concurrencia/seniales/SignalHandler.h"

Repartidor::Repartidor() : comunicacionConMaestros("/tmp/fifo-repartidores") {
    LOG_DEBUG("Inicializando repartidor. Id de proceso: " + to_string(getpid()));
    this->escucharPorPedidosTerminados();
}

Repartidor::~Repartidor() {
}

void Repartidor::escucharPorPedidosTerminados() {
    RepartidorSIGINTHandler repartidorSigintHandler(this);
    SignalHandler::getInstance()->registrarHandler(SIGINT, &repartidorSigintHandler);

    this->comunicacionConMaestros.abrir();
    while(this->continuarRepartiendo){
        LOG_DEBUG("Esperando por un pedido listo para entregar");
        CajaConPedido pedidoTerminado;
        this->comunicacionConMaestros.leer(static_cast<void*>(&pedidoTerminado), sizeof(CajaConPedido));
        this->entregarPedido(pedidoTerminado);
    }
    this->liberarRecursos();
    exit(0);
}

void Repartidor::entregarPedido(CajaConPedido pedidoTerminado) {
    if(pedidoTerminado.tipoDePedido == NOTIFICACION_DE_CIERRE) {
        LOG_DEBUG("Ha llegado notificacion de cierre. Procedere a subirme a mi moto e irme a mi casa.");
        this->continuarRepartiendo = false;
    } else {
        LOG_DEBUG("Debo entregar el pedido de: " + Panaderia::TIPO_A_CADENA[pedidoTerminado.tipoDePedido] + ", "
                   "cuyo numero es: " + to_string(pedidoTerminado.numeroDePedido));
        sleep(this->TIEMPO_EN_ENTREGA);
        LOG_INFO("Se entrego el pedido numero: " + to_string(pedidoTerminado.numeroDePedido) + ". Dicho pedido era "
                 "de " + Panaderia::TIPO_A_CADENA[pedidoTerminado.tipoDePedido]);
    }

}


void Repartidor::liberarRecursos() {
    SignalHandler::destruir();
    LOG_DEBUG("Cerrando comunicacion con maestros.");
    this->comunicacionConMaestros.cerrar();
    this->comunicacionConMaestros.eliminar();
}

