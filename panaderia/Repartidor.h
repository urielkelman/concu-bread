//
// Created by urielkelman on 24/5/20.
//

#ifndef CONCU_BREAD_REPARTIDOR_H
#define CONCU_BREAD_REPARTIDOR_H

#include "../logging/Logging.h"
#include "../concurrencia/fifos/FifoLectura.h"
#include "Panaderia.h"
#include "Maestro.h"

/**
 * Clase que representa al repartidor de pedidos.*/
class Repartidor {
public:
    Repartidor();
    ~Repartidor();

    /**
     * Metodo para liberar los recursos de comunicacion, el fifo por el cual recibe pedidos. */
    void liberarRecursos();
private:
    FifoLectura comunicacionConMaestros;
    bool continuarRepartiendo = true;
    int TIEMPO_EN_ENTREGA = 20000;

    /**
     * Contiene la logica necesaria para suscribirse al Fifo por el cual le llegan pedidos que debe entregar.*/
    void escucharPorPedidosTerminados();

    /**
     * Metodo que procesa el pedido y lo entrega. */
    void entregarPedido(CajaConPedido pedidoTerminado);
};


#endif //CONCU_BREAD_REPARTIDOR_H
