//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_EMPLEADO_H
#define CONCU_BREAD_EMPLEADO_H

using namespace std;

#include "../logging/Logging.h"
#include "../concurrencia/pipes/Pipe.h"

/** Clase abstracta de la cual descienden todos aquellos empleados que en su estructura interna utilicen tres pipes.*/
class Empleado {
public:
    /** Permite configurar un idenficador correspondiente al numero de empleado de determinado tipo.*/
    void configurarIdentificador(int numeroDeEmpleado);
    /**
     * Metodo para configurar los tres pipes que utilizara el empleado para establecer su comunicacion
     * con otros procesos. Notese que se podria implementar este metodo y setear los tres pipes y ya,
     * pero que es preferible implementarlos en los hijos debido a que los nombres genericos
     * podrian resultar confusos cuando se este implementando la funcionalidad.*/
    virtual void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) = 0;

    /**
     * Metodo que servira para que las clases que desciendan de Empleado implementen la escucha de solicitudes
     * de pedidos.*/
    virtual void esperarPorSolicitudes() = 0;

    /** Metodo que servira para liberar los distintos recursos de comunicacion que se hayan utilizado, entre ellos
     * los tres pipes.*/
    virtual void liberarRecursos() = 0;

    string obtenerIdentificacion();

protected:
    int numeroDeEmpleado;
    const char* cadenaIdentificadora;
    bool continuarAtendiendoPedidos = true;
};


#endif //CONCU_BREAD_EMPLEADO_H
