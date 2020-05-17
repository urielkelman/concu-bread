//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_MAESTRO_H
#define CONCU_BREAD_MAESTRO_H

#include "Empleado.h"
#include "../concurrencia/pipes/Pipe.h"

class Maestro : public Empleado {
public:
    Maestro();
    ~Maestro();

    void configurarPipes(Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) override;
    void esperarPorSolicitudes() override;

private:
    Pipe comunicacionConRecepcionistas;
    Pipe comunicacionConMaestroMasaMadre;
    Pipe recepcionMasaMadre;
};


#endif //CONCU_BREAD_MAESTRO_H
