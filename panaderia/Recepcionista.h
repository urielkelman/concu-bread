//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_RECEPCIONISTA_H
#define CONCU_BREAD_RECEPCIONISTA_H


#include "Empleado.h"

class Recepcionista : public Empleado {
public:
    Recepcionista();
    ~Recepcionista();

private:
    void esperarPorSolicitudes() override;
};


#endif //CONCU_BREAD_RECEPCIONISTA_H
