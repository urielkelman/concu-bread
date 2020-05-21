//
// Created by urielkelman on 20/5/20.
//

#include <Logging.h>
#include "MaestroMasaMadre.h"

MaestroMasaMadre::MaestroMasaMadre(Pipe comunicacionPedidosDeMasaMadre, Pipe comunicacionEntregaDeMasaMadre, int cantidadDeCocineros):
lockComunicacionPedidosDeMasaMadre(LockFile("maestromasamadre.lock")),
lockPedidosVigentes(LockFile("pedidosvigentes.lock")){
    LOG_DEBUG("ASDADWADWA");
    this->comunicacionPedidosDeMasaMadre = comunicacionPedidosDeMasaMadre;
    this->comunicacionEntregaDeMasaMadre = comunicacionEntregaDeMasaMadre;
    this->cantidadDeCocineros = cantidadDeCocineros;
    /*LOG_DEBUG("Registrando maestro de la masa madre. Mi id de proceso es: " + to_string(getpid()) + ", y el de mi "
              "padre es: " + to_string(getppid()));
    this->pedidosVigentes = MemoriaCompartida<int>("Maestro.cpp", 'A')  ;
    LOG_DEBUG("Inicializando memoria compartida de pedidos vigentes en 0.");
    this->pedidosVigentes.escribir(0);
    this->esperarPorSolicitudes();*/
}

MaestroMasaMadre::~MaestroMasaMadre() {

}

void MaestroMasaMadre::esperarPorSolicitudes() {
    while(this->continuarProcesandoPedidos){
        if(this->hayPedidosEnEspera() && this->hayRacionDeMasaDisponible()){
            char notificacion[1];
            this->comunicacionPedidosDeMasaMadre.leer(&notificacion, sizeof(char));
            LOG_DEBUG("Se leyo una notificacion de tipo " + string(notificacion));
            exit(0);
        }
    }
}

bool MaestroMasaMadre::hayPedidosEnEspera() {
    this->lockPedidosVigentes.tomarLock();
    int totalPedidosVigentes = this->pedidosVigentes.leer();
    LOG_DEBUG("Se leyeron el total de " + to_string(totalPedidosVigentes) + " pedidos vigentes.");
    this->lockPedidosVigentes.liberarLock();
    return totalPedidosVigentes > 0;
}

void MaestroMasaMadre::alimentarMasaMadre() {
    LOG_DEBUG("Alimentando masa madre. Incrementando alimento en una unidad a: " + to_string(this->masaMadre.cantidadDeAlimento + 1));
    sleep(1);
    this->masaMadre.cantidadDeAlimento += 1;
}

bool MaestroMasaMadre::hayRacionDeMasaDisponible() {
    return this->masaMadre.cantidadDeAlimento > 3;
}


