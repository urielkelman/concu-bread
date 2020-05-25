//
// Created by urielkelman on 24/5/20.
//

#ifndef CONCU_BREAD_REPARTIDORSIGINTHANDLER_H
#define CONCU_BREAD_REPARTIDORSIGINTHANDLER_H

#include "EventHandler.h"
#include "../../panaderia/Repartidor.h"

class RepartidorSIGINTHandler : public EventHandler {
private:
    Repartidor* repartidor;

public:
    RepartidorSIGINTHandler(Repartidor* repartidor) : repartidor(repartidor){

    }

    ~RepartidorSIGINTHandler(){}

    int handleSignal(int signum) {
        LOG_DEBUG("Inicializando handler SIGINT para repartidor");
        repartidor->liberarRecursos();
        LOG_DEBUG("Evacuando repartidor!!!");
        exit(-1);
    }
};


#endif //CONCU_BREAD_REPARTIDORSIGINTHANDLER_H
