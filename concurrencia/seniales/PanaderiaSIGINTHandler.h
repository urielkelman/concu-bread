//
// Created by urielkelman on 24/5/20.
//

#ifndef CONCU_BREAD_PANADERIASIGINTHANDLER_H
#define CONCU_BREAD_PANADERIASIGINTHANDLER_H

#include "../../panaderia/Panaderia.h"
#include "EventHandler.h"

class PanaderiaSIGINTHandler : public EventHandler {
private:
    Panaderia* panaderia;
public:
    PanaderiaSIGINTHandler(Panaderia* pan) : panaderia(pan) {
    }

    ~PanaderiaSIGINTHandler() {
    }

    int handleSignal(int signum) {
        LOG_DEBUG("Inicializando handler SIGINT para panaderia.");
        panaderia->iniciarEvacuacion();
        panaderia->liberarRecursos();
        int status;
        while ((wait(&status)) > 0);
        LOG_DEBUG("Simulacion terminada por fuego en la panaderia.");
        Logging::Finalizar();
        exit(0);
    }
};


#endif //CONCU_BREAD_PANADERIASIGINTHANDLER_H
