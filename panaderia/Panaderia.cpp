//
// Created by urielkelman on 15/5/20.
//

#include <unistd.h>
#include <wait.h>
#include "Panaderia.h"
#include "Empleado.h"
#include "Recepcionista.h"
#include "MaestroPanadero.h"
#include "MaestroPizzero.h"
#include "MaestroMasaMadre.h"

vector<string> Panaderia::TIPO_A_CADENA = {"PAN", "PIZZA", "NOTIFICACION_DE_CIERRE"};
vector<string> Panaderia::CONTENIDO_A_CADENA = {"LLENO", "VACIO"};

Panaderia::Panaderia(Config config) {
    LOG_DEBUG("Inicializando panaderia. Mi id de proceso es: " + to_string(getpid()));
    this->config = config;
    this->canalConRecepcionistas = Pipe();
    Pipe canalRecepcionistasMaestroPanadero;
    Pipe canalRecepcionistaMaestroPizzero;
    Pipe canalMaestroAMaestroMasaMadre;
    Pipe canalMaestroMasaMadreAMaestro;
    Recepcionista recepcionista;
    this->generarMaestroDeMasaMadre(canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);

    this->generarEntidad(&recepcionista, config.obtenerRecepcionistas(), this->canalConRecepcionistas,
                         canalRecepcionistasMaestroPanadero, canalRecepcionistaMaestroPizzero);
    MaestroPanadero maestroPanadero;
    this->generarEntidad(&maestroPanadero, config.obtenerMaestrosPanaderos(), canalRecepcionistasMaestroPanadero,
                         canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);
    MaestroPizzero maestroPizzero;
    this->generarEntidad(&maestroPizzero, config.obtenerMaestrosPizzeros(), canalRecepcionistaMaestroPizzero,
                         canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);
}

Panaderia::~Panaderia() {
}

void Panaderia::generarEntidad(Empleado *empleado, int cantidad, Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    for(int i = 1; i <= cantidad; i++){
        pid_t id = fork();
        if(id == 0){
            empleado->configurarIdentificador(i);
            empleado->configurarPipes(primerPipe, segundoPipe, tercerPipe);
            empleado->esperarPorSolicitudes();
        }
    }
}

TipoDePedido Panaderia::generarPedidoAleatoriamente(){
    srand(time(NULL));
    int numeroRandom = rand() % 10 + 1;
    if(numeroRandom > 5){
        return PAN;
    } else {
        return PIZZA;
    }
}

void Panaderia::enviarPedidosVacios(TipoDePedido tipoDePedido, int cantidadDePedidos) {
    for(int i = 1; i <= cantidadDePedidos; i++){
        Pedido pedido;
        pedido.tipoDePedido = tipoDePedido;
        pedido.contenidoDePedido = VACIO;
        pedido.numeroDePedido = -i;
        LOG_DEBUG("Enviando notificacion" + to_string(i) + "de finalizacion de pedidos de " + TIPO_A_CADENA[tipoDePedido] + " a recepcionistas.");
        this->canalConRecepcionistas.escribir(static_cast<const void*>(&pedido), sizeof(Pedido));
    }
}

void Panaderia::notificarFinalizacion() {
    this->enviarPedidosVacios(PAN, this->config.obtenerMaestrosPanaderos());
    this->enviarPedidosVacios(PIZZA, this->config.obtenerMaestrosPizzeros());
    for(int i = 1; i <= this->config.obtenerRecepcionistas(); i++){
        Pedido pedido;
        pedido.tipoDePedido = NOTIFICACION_DE_CIERRE;
        LOG_DEBUG("Enviando notificacion " + to_string(i) + " de cierre de panaderia.");
        this->canalConRecepcionistas.escribir(static_cast<const void*>(&pedido), sizeof(Pedido));
    }
    pid_t waitingPid;
    int status;
    //while((waitingPid = wait(&status)) > 0);
}

void Panaderia::comenzarSimulacion(int cantidadDePedidos) {
    for(int i = 1; i <= cantidadDePedidos; i++){
        Pedido pedido;
        TipoDePedido tipoDePedido = this->generarPedidoAleatoriamente();
        pedido.tipoDePedido = tipoDePedido;
        pedido.numeroDePedido = i;
        pedido.contenidoDePedido = LLENO;
        LOG_DEBUG("Depositando pedido con id: " + to_string(i) + ". El pedido es de: " + TIPO_A_CADENA[tipoDePedido]);
        this->canalConRecepcionistas.escribir(static_cast<const void*>(&pedido), sizeof(Pedido));
    }

    this->notificarFinalizacion();
}

void Panaderia::generarMaestroDeMasaMadre(Pipe canalMaestroAMasaMadre, Pipe canalMaestroMasaMadreAMaestro) {
    pid_t id = fork();
    if(id == 0){
        int cocineros = this->config.obtenerMaestrosPanaderos() + this->config.obtenerMaestrosPizzeros();
        MaestroMasaMadre maestroMasaMadre(canalMaestroAMasaMadre, canalMaestroMasaMadreAMaestro,
                                          cocineros);
    }
}



