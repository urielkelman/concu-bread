//
// Created by urielkelman on 15/5/20.
//

#include <unistd.h>
#include "Panaderia.h"
#include "Empleado.h"
#include "Recepcionista.h"

Panaderia::Panaderia(Config config) {
    LOG_DEBUG("Inicializando panaderia. Mi id de proceso es: " + to_string(getpid()));
    Recepcionista recepcionista;
    this->generarEntidad(&recepcionista, config.obtenerRecepcionistas());
}

Panaderia::~Panaderia() {

}

void Panaderia::comenzarSimulacion() {
    while(true){
        LOG_DEBUG("Esperando para comenzar simulacion..");
        sleep(10);
    }
}

/*
 * TODO: Ver si no es posible hacer algo un poco mas generico. Los tres metodos que siguen son muy parecidos.
 * TODO: Una opcion podria ser instanciar la entidad y pasarla en el constructor (aprovechando el fork),
 * TODO: y que todas las entidades soporten algun metodo en comun para setear el identificador.*/

void Panaderia::generarEntidad(Empleado *empleado, int cantidad) {
    for(int i = 1; i <= cantidad; i++){
        pid_t id = fork();
        if(id == 0){
            empleado->configurarIdentificador(i);
        }
    }
}
