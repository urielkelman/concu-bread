//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_PANADERIA_H
#define CONCU_BREAD_PANADERIA_H

#include "../concurrencia/pipes/Pipe.h"
#include "../config/Config.h"
#include "Empleado.h"

class Panaderia {
public:
    Panaderia(Config config);
    ~Panaderia();

    void comenzarSimulacion();

private:
    void generarEntidad(Empleado *empleado, int cantidad, Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe);
    Pipe canalConRecepcionistas;
};


#endif //CONCU_BREAD_PANADERIA_H
