//
// Created by urielkelman on 24/5/20.
//

#ifndef CONCU_BREAD_EMPLEADOSIGINTHANDLER_H
#define CONCU_BREAD_EMPLEADOSIGINTHANDLER_H

#include "EventHandler.h"
#include "../../panaderia/Empleado.h"

class EmpleadoSIGINTHandler : public EventHandler{
private:
    Empleado* empleado;

public:
    EmpleadoSIGINTHandler(Empleado* empleado) : empleado(empleado){
    }

    ~EmpleadoSIGINTHandler() {
    }

    int handleSignal(int signum){
        LOG_DEBUG("Inicializando handler SIGINT para empleado: " + this->empleado->obtenerIdentificacion() + ". "
                  "Con id: " + to_string(getpid()));
        empleado->liberarRecursos();
        LOG_DEBUG("Evacuando empleado de tipo: " + this->empleado->obtenerIdentificacion() + ". "
                  "Con id: " + to_string(getpid()));
        exit(-1);
    }

};


#endif //CONCU_BREAD_EMPLEADOSIGINTHANDLER_H
