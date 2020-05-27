//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_MAESTROPANADERO_H
#define CONCU_BREAD_MAESTROPANADERO_H

#include "Maestro.h"

/**
 * Clase que representa al maestro panadero..*/
class MaestroPanadero : public Maestro {
public:
    MaestroPanadero();
    ~MaestroPanadero();
private:
    int TIEMPO_COCCION_PAN = 30000;

    /**
     * Override del metodo de la clase Maestro. Siempre devuelve PAN como TipoDePedido. */
    TipoDePedido cocinar(MasaMadre masaMadre) override;
};


#endif //CONCU_BREAD_MAESTROPANADERO_H
