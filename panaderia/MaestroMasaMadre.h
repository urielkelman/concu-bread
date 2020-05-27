//
// Created by urielkelman on 20/5/20.
//

#ifndef CONCU_BREAD_MAESTROMASAMADRE_H
#define CONCU_BREAD_MAESTROMASAMADRE_H

#include "../concurrencia/pipes/Pipe.h"
#include "../concurrencia/locks/LockFile.h"
#include "../concurrencia/memoria/MemoriaCompartida.h"
#include "../concurrencia/fifos/FifoEscritura.h"

struct MasaMadre {
    int cantidadDeAlimento = 0;
};

typedef char RacionMasaMadre;

/**
 * Clase que representa al maestro especialista en masa madre. En el programa concurrente existira uno solo.
 * Contiene la logica para recibir y enviar pedidos de masa madre, ademas de alimentar la masa madre para
 * tener disponible raciones cuando le sean solicitadas. */
class MaestroMasaMadre {
public:
    MaestroMasaMadre(Pipe comunicacionPedidosDeMasaMadre, Pipe comunicacionEntregaDeMasaMadre, int cantidadDeCocineros);

    /**
     * Metodo que sirve*/
    void liberarRecursosDeComunicacion();
    ~MaestroMasaMadre();

private:
    LockFile lockComunicacionPedidosDeMasaMadre;
    LockFile lockPedidosVigentes;
    MemoriaCompartida<int> pedidosVigentes;
    Pipe comunicacionPedidosDeMasaMadre;
    Pipe comunicacionEntregaDeMasaMadre;
    int cantidadDeCocineros;
    FifoEscritura comunicacionRepartidor;
    bool continuarProcesandoPedidos = true;
    MasaMadre masaMadre;
    int MASA_MADRE_POR_RACION = 3;

    /**
     * Funcion que contiene la logica necesaria para escuchar por pedidos y no bloquearse en caso de no
     * haya raciones de masa madre disponible.*/
    void esperarPorNotificaciones();

    /**
     * Procesa la notificacion de solicitud de masa madre. Esta notificacion puede ser efectivamente un pedido
     * de masa madre, o tambien puede indicar el cierre de un cocinero. */
    void procesarNotificacion(char notificacion);

    /**
     * Lee la memoria compartida y devuelve un valor booleano indicando si hay pedidos vigentes o no. */
    bool hayPedidosEnEspera();

    /**
     * Metodo interno que indica si hay racion de masa disponible.*/
    bool hayRacionDeMasaDisponible();

    /**
     * Encapsula la logica de la alimentacion de la masa madre. Esto consiste en incrementar el alimento que el
     * especialista va a agregando a la masa en una unidad. Cuando posea mas de 3 unidades de alimento, entonces
     * podra quitar esa cantidad teniendo una racion de masa disponible.*/
    void alimentarMasaMadre();

    /**
     * Cuando el especialista debe finalizar su ejecucion, tambien notifica al repartidor para que haga lo
     * mismo. */
    void avisarCierreARepartidor();

};


#endif //CONCU_BREAD_MAESTROMASAMADRE_H
