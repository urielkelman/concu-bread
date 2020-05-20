//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_RECEPCIONISTA_H
#define CONCU_BREAD_RECEPCIONISTA_H


#include "Empleado.h"
#include "../concurrencia/pipes/Pipe.h"
#include "Panaderia.h"

class Recepcionista : public Empleado {
public:
    Recepcionista();
    ~Recepcionista();
    void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) override;
    void esperarPorSolicitudes() override;

private:
    Pipe comunicacionConPanaderia;
    Pipe comunicacionConMaestrosPanaderos;
    Pipe comunicacionConMaestrosPizzeros;
    LockFile lockComunicacionConPanaderia;
    void entregarPedidoAMaestro(Pedido pedido);
};


#endif //CONCU_BREAD_RECEPCIONISTA_H
