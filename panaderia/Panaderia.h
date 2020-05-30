//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_PANADERIA_H
#define CONCU_BREAD_PANADERIA_H

#include "../concurrencia/seniales/SignalHandler.h"
#include "../concurrencia/pipes/Pipe.h"
#include "../config/Config.h"
#include "../utilidades/SerializadorDePedidos.h"
#include "Empleado.h"

/**
 * Clase que reprensenta la panaderia a un nivel macro. Sus metodos se ejecutan en el hilo principal del programa. */
class Panaderia {
public:
    Panaderia(Config config);
    ~Panaderia();

    /**
     * Metodo que dispara la simulacion una vez que se han creado los procesos que se corresponden con los distintos
     * empleados de la panaderia.*/
    void comenzarSimulacion();

    /**
     * Libera los recursos de comunicacion que la panaderia utiliza para comunicarse con los recepcionistas.*/
    void liberarRecursos();

    /**
     * Inicia la evacuacion (finalizacion) de todos los empleados (procesos) en caso de que se inicie un fuego
     * en la panaderia. Para esto, envia la señal SIGINT a todos los pid que tiene almacenados en el vector de empleados. */
    void iniciarEvacuacion();

    static vector<string> TIPO_A_CADENA;
    static vector<string> CONTENIDO_A_CADENA;

private:
    Config config;
    Pipe canalConRecepcionistas;
    vector<pid_t> *empleados;

    static int BUFFSIZE;

    /**
     * Genera los procesos asociados al tipo de empleado que utiliza por para parametros en forma polimorfica para las
     * distintas clases hijas de Empleado, utilizando la llamada al sistema operativor fork(). */
    void generarEmpleado(Empleado *empleado, int cantidad, Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe);

    /**
     * Metodo que sirve para generar un pedido de PAN o PIZZA aleatoriamente utilizando la funcion rand(). */
    TipoDePedido generarPedidoAleatoriamente();

    /**
     * Contiene la logica de todos los pedidos que deben ser enviados a modo de notificacion de cierre para indicarle
     * a todos los empleados que deben finalizar su ejecucion.*/
    void notificarFinalizacion();

    /**
     * Envia los pedidos vacios que contienen la informacion para que cierren los maestros panaderos y pizzeros. */
    void enviarPedidosVacios(TipoDePedido tipoDePedido, int cantidadDePedidos);

    /**
     * Inicializa el proceso asociado al maestro de la masa madre utilizando la llamada al SO fork().
     */
    void generarMaestroDeMasaMadre(Pipe canalMaestroAMasaMadre, Pipe canalMaestroMasaMadreAMaestro);

    /**
     * Inicializa el proceso asociado al repartidor utilizando la llamada al SO fork().
     */
    void generarRepartidor();
};


#endif //CONCU_BREAD_PANADERIA_H
