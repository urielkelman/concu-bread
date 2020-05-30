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

/**
 * Clase abstracta que implementa casi todos los metodos que identifican a un maestro cocinero, ya sea
 * panadero o pizzero.
 * */
class Maestro : public Empleado {
public:
    Maestro(const char* nombreLockComunicacionConRecepcionistas);

    ~Maestro();

    /**
     * Los tres metodos son overrides de los metodos de la clase Empleado.*/
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
    FifoEscritura comunicacionConRepartidor;
    int numeroDePedidoActual = 0;

    static int BUFFSIZE;

    /**
     * Metodo que contiene la logica de procesamiento de pedidos, contemplando los casos en el que el
     * maestro debe procesar un pedido o le llega la orden para que se cierre.*/
    void procesarPedido(Pedido pedido);

    /**
     * Una vez que el maestro solicita masa madre, se invoca al siguiente metodo contiene la logica para
     * escuchar por el pipe de recepcion de raciones de masa madre.*/
    MasaMadre retirarMasaMadre();

    /**
     * Metodo abstracto que deben implementar los maestros panaderos y pizzeros por separado. Conceptualmente,
     * indica que cada uno de los maestros cocineros sabe como cocinar su especialidad. */
    virtual TipoDePedido cocinar(MasaMadre masaMadre) = 0;

    /**
     * Luego de cocinar el pedido, se invoca al siguiente metodo, el cual contiene la logica necesaria para
     * escribir en el canal de comunicacion con el repartidor para que este entregue el pedido. */
    void entregarPedido(TipoDePedido tipoDePedido);
};


#endif //CONCU_BREAD_MAESTRO_H
