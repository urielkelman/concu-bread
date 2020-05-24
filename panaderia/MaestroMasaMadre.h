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

class MaestroMasaMadre {
public:
    MaestroMasaMadre(Pipe comunicacionPedidosDeMasaMadre, Pipe comunicacionEntregaDeMasaMadre, int cantidadDeCocineros);
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

    void esperarPorNotificaciones();
    void procesarNotificacion(char notificacion);
    bool hayPedidosEnEspera();
    bool hayRacionDeMasaDisponible();
    void alimentarMasaMadre();
    void avisarCierreARepartidor();

};


#endif //CONCU_BREAD_MAESTROMASAMADRE_H
