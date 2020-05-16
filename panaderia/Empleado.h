//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_EMPLEADO_H
#define CONCU_BREAD_EMPLEADO_H

using namespace std;

#include "../logging/Logging.h"

class Empleado {
public:
    void configurarIdentificador(int numeroDeEmpleado);

protected:
    int numeroDeEmpleado;
    string cadenaIdentificadora;
    virtual void esperarPorSolicitudes() = 0;
};


#endif //CONCU_BREAD_EMPLEADO_H
