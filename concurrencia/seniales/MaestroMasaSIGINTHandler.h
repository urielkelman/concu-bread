//
// Created by urielkelman on 24/5/20.
//

#ifndef CONCU_BREAD_MAESTROMASASIGINTHANDLER_H
#define CONCU_BREAD_MAESTROMASASIGINTHANDLER_H


#include "EventHandler.h"
#include "../../panaderia/MaestroMasaMadre.h"
#include "../../logging/Logging.h"

class MaestroMasaSIGINTHandler : public EventHandler {
private:
    MaestroMasaMadre* maestroMasaMadre;
public:
    MaestroMasaSIGINTHandler(MaestroMasaMadre* maestroMasaMadre) : maestroMasaMadre(maestroMasaMadre){
    }

    ~MaestroMasaSIGINTHandler() {}

    int handleSignal(int signum){
        LOG_DEBUG("Inicializando SIGINT handler para maestro de la masa madre");
        this->maestroMasaMadre->liberarRecursosDeComunicacion();
        LOG_DEBUG("Evacuando maestro de la masa madre!!!");
        exit(-1);
    }
};


#endif //CONCU_BREAD_MAESTROMASASIGINTHANDLER_H
