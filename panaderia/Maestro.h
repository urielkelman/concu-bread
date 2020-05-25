//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_MAESTRO_H
#define CONCU_BREAD_MAESTRO_H

#include "Empleado.h"
#include "../concurrencia/pipes/Pipe.h"
#include "../concurrencia/locks/LockFile.h"
#include "../concurrencia/memoria/MemoriaCompartida.h"
#include "../concurrencia/fifos/FifoEscritura.h"
#include "Panaderia.h"
#include "MaestroMasaMadre.h"

typedef char NotificacionMaestro;

struct CajaConPedido {
    int numeroDePedido;
    TipoDePedido tipoDePedido;
};

class Maestro : public Empleado {
public:
    Maestro(const char* nombreLockComunicacionConRecepcionistas);

    ~Maestro();

    void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) override;
    void esperarPorSolicitudes() override;
    void liberarRecursos() override;
private:
    LockFile lockComunicacionConRecepcionistas;
    LockFile lockPedidosVigentes;
    LockFile lockMasaMadre;
    Pipe comunicacionConRecepcionistas;
    Pipe comunicacionConMaestroMasaMadre;
    Pipe recepcionMasaMadre;
    MemoriaCompartida<int> pedidosVigentes;
    FifoEscritura comunicacionConRepartidores;
    int numeroDePedidoActual = 0;

    void procesarPedido(Pedido pedido);
    MasaMadre retirarMasaMadre();
    virtual TipoDePedido cocinar(MasaMadre masaMadre) = 0;
    void entregarPedido(TipoDePedido tipoDePedido);
};


#endif //CONCU_BREAD_MAESTRO_H
