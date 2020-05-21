//
// Created by urielkelman on 20/5/20.
//

#ifndef CONCU_BREAD_MAESTROMASAMADRE_H
#define CONCU_BREAD_MAESTROMASAMADRE_H

#include "../concurrencia/pipes/Pipe.h"
#include "../concurrencia/locks/LockFile.h"
#include "../concurrencia/memoria/MemoriaCompartida.h"

struct MasaMadre {
    int cantidadDeAlimento = 0;
};

class MaestroMasaMadre {
public:
    MaestroMasaMadre(Pipe comunicacionPedidosDeMasaMadre, Pipe comunicacionEntregaDeMasaMadre, int cantidadDeCocineros);
    ~MaestroMasaMadre();

private:
    LockFile lockComunicacionPedidosDeMasaMadre;
    LockFile lockPedidosVigentes;
    MemoriaCompartida<int> pedidosVigentes;
    Pipe comunicacionPedidosDeMasaMadre;
    Pipe comunicacionEntregaDeMasaMadre;
    int cantidadDeCocineros;
    bool continuarProcesandoPedidos = true;
    MasaMadre masaMadre;

    void esperarPorSolicitudes();
    bool hayPedidosEnEspera();
    bool hayRacionDeMasaDisponible();
    void alimentarMasaMadre();

};


#endif //CONCU_BREAD_MAESTROMASAMADRE_H
