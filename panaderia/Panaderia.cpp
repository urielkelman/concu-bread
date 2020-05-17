//
// Created by urielkelman on 15/5/20.
//

#include <unistd.h>
#include "Panaderia.h"
#include "Empleado.h"
#include "Recepcionista.h"
#include "MaestroPanadero.h"
#include "Maestro.h"

Panaderia::Panaderia(Config config) {
    LOG_DEBUG("Inicializando panaderia. Mi id de proceso es: " + to_string(getpid()));
    this->canalConRecepcionistas = Pipe();
    Pipe canalRecepcionistasMaestroPanadero;
    Pipe canalRecepcionistaMaestroPizzero;
    Pipe canalMaestroAMaestroMasaMadre;
    Pipe canalMaestroMasaMadreAMaestro;
    Recepcionista recepcionista;
    this->generarEntidad(&recepcionista, config.obtenerRecepcionistas(), this->canalConRecepcionistas,
            canalRecepcionistasMaestroPanadero, canalRecepcionistaMaestroPizzero);
    MaestroPanadero maestroPanadero;
    this->generarEntidad(&maestroPanadero, config.obtenerMaestrosPanaderos(), canalRecepcionistasMaestroPanadero,
            canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);
    Maestro maestroPizzero;
    this->generarEntidad(&maestroPizzero, config.obtenerMaestrosPizzeros(), canalRecepcionistaMaestroPizzero,
            canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);
}

Panaderia::~Panaderia() {

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

void Panaderia::comenzarSimulacion(int cantidadDePedidos) {
    for(int i = 1; i <= cantidadDePedidos; i++){
        Pedido pedido;
        TipoDePedido tipoDePedido = this->generarPedidoAleatoriamente();
        pedido.tipoDePedido = tipoDePedido;
        pedido.numeroDePedido = i;
        LOG_DEBUG("Despositando pedido con id: " + to_string(i) + ". El pedido es de: " + to_string(tipoDePedido));
        this->canalConRecepcionistas.escribir(static_cast<const void*>(&pedido), sizeof(Pedido));
    }
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
