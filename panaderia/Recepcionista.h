//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_RECEPCIONISTA_H
#define CONCU_BREAD_RECEPCIONISTA_H


#include "Panaderia.h"
#include "Empleado.h"
#include "../concurrencia/pipes/Pipe.h"

/**
 * Clase que representa al recepcionista, cuya funcion principal es recibir pedidos y entregarselos a los maestros. */
class Recepcionista : public Empleado {
public:
    Recepcionista();
    ~Recepcionista();

    /**
     * Los tres metodos publicos son overrides de la clase Empleado. */
    void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) override;
    void esperarPorSolicitudes() override;
    void liberarRecursos() override;

private:
    Pipe comunicacionConPanaderia;
    Pipe comunicacionConMaestrosPanaderos;
    Pipe comunicacionConMaestrosPizzeros;
    LockFile lockComunicacionConPanaderia;

    static int BUFFSIZE_PEDIDO;
    /**
     * Contiene la logica para enrutar el pedido segun su tipo y enviarlo al pipe de maestro que corresponda.
     */
    void entregarPedidoAMaestro(Pedido pedido);
};


#endif //CONCU_BREAD_RECEPCIONISTA_H
