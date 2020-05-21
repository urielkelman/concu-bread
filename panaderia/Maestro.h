//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_MAESTRO_H
#define CONCU_BREAD_MAESTRO_H

#include "Empleado.h"
#include "../concurrencia/pipes/Pipe.h"
#include "../concurrencia/locks/LockFile.h"
#include "../concurrencia/memoria/MemoriaCompartida.h"
#include "Panaderia.h"

class Maestro : public Empleado {
public:
    Maestro(string lockComunicacionConRecepcionistas);

    ~Maestro();

    void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) override;
    void esperarPorSolicitudes() override;

private:
    LockFile lockComunicacionConRecepcionistas;
    LockFile lockPedidosVigentes;
    Pipe comunicacionConRecepcionistas;
    Pipe comunicacionConMaestroMasaMadre;
    Pipe recepcionMasaMadre;
    MemoriaCompartida<int> pedidosVigentes;

    void procesarPedido(Pedido pedido);

    virtual void cocinar() = 0;
};


#endif //CONCU_BREAD_MAESTRO_H
