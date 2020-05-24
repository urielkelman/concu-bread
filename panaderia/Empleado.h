//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_EMPLEADO_H
#define CONCU_BREAD_EMPLEADO_H

using namespace std;

#include "../logging/Logging.h"
#include "../concurrencia/pipes/Pipe.h"
class Empleado {
public:
    void configurarIdentificador(int numeroDeEmpleado);
    /*
     * Notese que se podria implementar este metodo y setear los tres pipes y ya,
     * pero que es preferible implementarlos en los hijos debido a que los nombres genericos
     * podrian resultar confusos cuando se este implementando la funcionalidad.*/
    virtual void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) = 0;
    virtual void esperarPorSolicitudes() = 0;

protected:
    int numeroDeEmpleado;
    const char* cadenaIdentificadora;
    bool continuarAtendiendoPedidos = true;
};


#endif //CONCU_BREAD_EMPLEADO_H
