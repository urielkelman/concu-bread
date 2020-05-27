//
// Created by urielkelman on 24/5/20.
//

#ifndef CONCU_BREAD_REPARTIDOR_H
#define CONCU_BREAD_REPARTIDOR_H

#include "../logging/Logging.h"
#include "../concurrencia/fifos/FifoLectura.h"
#include "Panaderia.h"
#include "Maestro.h"

class Repartidor {
public:
    Repartidor();
    ~Repartidor();

    void liberarRecursos();
private:
    FifoLectura comunicacionConMaestros;
    bool continuarRepartiendo = true;
    int TIEMPO_EN_ENTREGA = 20000;

    void escucharPorPedidosTerminados();
    void entregarPedido(CajaConPedido pedidoTerminado);
};


#endif //CONCU_BREAD_REPARTIDOR_H
