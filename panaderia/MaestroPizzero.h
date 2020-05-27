//
// Created by urielkelman on 17/5/20.
//

#ifndef CONCU_BREAD_MAESTROPIZZERO_H
#define CONCU_BREAD_MAESTROPIZZERO_H

#include "Maestro.h"

/**
 * Clase que representa al maestro pizzero..*/
class MaestroPizzero : public Maestro{
public:
    MaestroPizzero();
    ~MaestroPizzero();

private:
    /**
     * Override del metodo de la clase Maestro. Siempre devuelve PIZZA como TipoDePedido. */
    TipoDePedido cocinar(MasaMadre masaMadre) override;

    /**
     * Devuelve un entero que representa el tiempo de coccion aleatoria que llevara al maestro
     * pizzero preprar una pizza.
     */
    int obtenerTiempoDeCoccionAleatoria();
};


#endif //CONCU_BREAD_MAESTROPIZZERO_H
