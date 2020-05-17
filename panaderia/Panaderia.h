//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_PANADERIA_H
#define CONCU_BREAD_PANADERIA_H

#include "../concurrencia/pipes/Pipe.h"
#include "../config/Config.h"
#include "Empleado.h"

enum TipoDePedido {PAN = 0, PIZZA = 1};

struct Pedido {
    TipoDePedido tipoDePedido;
    int numeroDePedido;
};

class Panaderia {
public:
    Panaderia(Config config);
    ~Panaderia();

    void comenzarSimulacion(int cantidadDePedidos);

private:
    Pipe canalConRecepcionistas;
    void generarEntidad(Empleado *empleado, int cantidad, Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe);
    TipoDePedido generarPedidoAleatoriamente();
};


#endif //CONCU_BREAD_PANADERIA_H
