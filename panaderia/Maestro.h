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
#include "MaestroMasaMadre.h"

typedef char NotificacionMaestro;

class Maestro : public Empleado {
public:
    Maestro(const char* nombreLockComunicacionConRecepcionistas);

    ~Maestro();

    void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) override;
    void esperarPorSolicitudes() override;

private:
    LockFile lockComunicacionConRecepcionistas;
    LockFile lockPedidosVigentes;
    LockFile lockMasaMadre;
    Pipe comunicacionConRecepcionistas;
    Pipe comunicacionConMaestroMasaMadre;
    Pipe recepcionMasaMadre;
    MemoriaCompartida<int> pedidosVigentes;
    int numeroDePedidoActual = 0;

    void procesarPedido(Pedido pedido);
    void liberarRecursosDeComunicacion();
    MasaMadre retirarMasaMadre();
    virtual void cocinar(MasaMadre masaMadre) = 0;

};


#endif //CONCU_BREAD_MAESTRO_H
