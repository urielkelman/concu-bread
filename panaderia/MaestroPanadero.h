//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_MAESTROPANADERO_H
#define CONCU_BREAD_MAESTROPANADERO_H

#include "Maestro.h"

class MaestroPanadero : public Maestro {
public:
    MaestroPanadero();
    ~MaestroPanadero();
private:
    int TIEMPO_COCCION_PAN = 30000;

    TipoDePedido cocinar(MasaMadre masaMadre) override;
};


#endif //CONCU_BREAD_MAESTROPANADERO_H
