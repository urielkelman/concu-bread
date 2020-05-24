//
// Created by urielkelman on 20/5/20.
//

#include "../logging/Logging.h"
#include "MaestroMasaMadre.h"
#include "Maestro.h"
#include "../concurrencia/seniales/MaestroMasaSIGINTHandler.h"
#include "../concurrencia/seniales/SignalHandler.h"

MaestroMasaMadre::MaestroMasaMadre(Pipe comunicacionPedidosDeMasaMadre, Pipe comunicacionEntregaDeMasaMadre, int cantidadDeCocineros) :
lockComunicacionPedidosDeMasaMadre("maestromasamadre.lock"),
lockPedidosVigentes("pedidosvigentes.lock"),
pedidosVigentes(MemoriaCompartida<int>('A')),
comunicacionPedidosDeMasaMadre(comunicacionPedidosDeMasaMadre),
comunicacionEntregaDeMasaMadre(comunicacionEntregaDeMasaMadre),
cantidadDeCocineros(cantidadDeCocineros),
comunicacionRepartidor("/tmp/fifo-repartidores"){
    LOG_DEBUG("Registrando maestro de la masa madre. Mi id de proceso es: " + to_string(getpid()) + ", y el de mi "
              "padre es: " + to_string(getppid()));

    MaestroMasaSIGINTHandler maestroMasaSigintHandler(this);
    SignalHandler::getInstance()->registrarHandler(SIGINT, &maestroMasaSigintHandler);

    this->pedidosVigentes.escribir(0);
    LOG_DEBUG("Inicializando memoria compartida de pedidos vigentes en 0.");
    this->esperarPorNotificaciones();
}

MaestroMasaMadre::~MaestroMasaMadre() {

}

void MaestroMasaMadre::esperarPorNotificaciones() {
    this->comunicacionRepartidor.abrir();
    while(this->continuarProcesandoPedidos){        /*
         * TODO: Ojo que la segunda condicion obliga a tener una masa madre disponible mientras que puede no necesitarse,
         * TODO: ya que la notificacion puede ser de cierre.
         */
        if(this->hayPedidosEnEspera() && this->hayRacionDeMasaDisponible()){
            char notificacion[1];
            this->comunicacionPedidosDeMasaMadre.leer(&notificacion, sizeof(NotificacionMaestro));
            this->procesarNotificacion(*notificacion);
        }
        this->alimentarMasaMadre();
    }


    this->liberarRecursosDeComunicacion();
}

void MaestroMasaMadre::procesarNotificacion(char notificacion) {
    if (notificacion == 'P') {
        LOG_DEBUG("Procesando notificacion de pedido de masa madre.");
        this->masaMadre.cantidadDeAlimento -= this->MASA_MADRE_POR_RACION;
        LOG_DEBUG("Se deposita la racion de masa madre en el pipe de comunicacion con los cocineros.");
        this->comunicacionEntregaDeMasaMadre.escribir("M", sizeof(char));
    } else {
        LOG_DEBUG("Procesando notificacion de cierre de cocinero.");
        this->cantidadDeCocineros -= 1;
        if(this->cantidadDeCocineros == 0){
            LOG_DEBUG("Todos los cocineros han notificado que cierran por el dia de hoy. Procedere a hacer lo mismo.");
            this->continuarProcesandoPedidos = false;
            this->avisarCierreARepartidor();
        }
    }

    this->lockPedidosVigentes.tomarLock();
    LOG_DEBUG("Lock adquirido para disminuir cantidad de pedidos vigentes.");
    int totalPedidosVigentes = this->pedidosVigentes.leer();
    LOG_DEBUG("Se leyeron " + to_string(totalPedidosVigentes) + " pedidos vigentes. Se escriben " +
              to_string(totalPedidosVigentes - 1) + " pedidos vigentes.");
    this->pedidosVigentes.escribir(totalPedidosVigentes - 1);
    this->lockPedidosVigentes.liberarLock();
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
    return this->masaMadre.cantidadDeAlimento >= this->MASA_MADRE_POR_RACION;
}

void MaestroMasaMadre::liberarRecursosDeComunicacion() {
    SignalHandler::destruir();

    LOG_DEBUG("Cerrando comunicacion con el repartidor");
    this->comunicacionRepartidor.cerrar();

    LOG_DEBUG("Cerrando canal de comunicacion de pedidos de masa madre");
    this->comunicacionEntregaDeMasaMadre.cerrar();

    LOG_DEBUG("Cerrando canal de comunicacion de entregas de masa madre");
    this->comunicacionEntregaDeMasaMadre.cerrar();

    LOG_DEBUG("Cerrando memoria compartida de pedidos vigentes");
    this->pedidosVigentes.liberar();

    exit(0);
}

void MaestroMasaMadre::avisarCierreARepartidor() {
    PedidoTerminado pedidoTerminado;
    pedidoTerminado.tipoDePedido = NOTIFICACION_DE_CIERRE;
    LOG_DEBUG("Avisando a repartidor que el dia laboral ha terminado.");
    this->comunicacionRepartidor.escribir(static_cast<void*>(&pedidoTerminado), sizeof(PedidoTerminado));
}


