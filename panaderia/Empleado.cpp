//
// Created by urielkelman on 15/5/20.
//

#include "Empleado.h"
#include <unistd.h>

void Empleado::configurarIdentificador(int numeroDeEmpleado) {
    this->numeroDeEmpleado = numeroDeEmpleado;
    LOG_DEBUG("Registrando " + string(this->cadenaIdentificadora) + " numero: " + to_string(numeroDeEmpleado) + ". "
              "Mi id de proceso es: " + to_string(getpid()) + ", y el de mi padre: " + to_string(getppid()));
}
