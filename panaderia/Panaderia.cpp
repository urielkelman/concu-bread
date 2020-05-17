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

void Panaderia::comenzarSimulacion() {
    while(true){
        LOG_DEBUG("Esperando para comenzar simulacion..");
        sleep(10);
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
