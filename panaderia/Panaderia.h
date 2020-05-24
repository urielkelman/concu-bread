//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_PANADERIA_H
#define CONCU_BREAD_PANADERIA_H

#include "../concurrencia/pipes/Pipe.h"
#include "../config/Config.h"
#include "Empleado.h"

enum ContenidoDePedido {LLENO = 0, VACIO = 1};
enum TipoDePedido {PAN = 0, PIZZA = 1, NOTIFICACION_DE_CIERRE = 2};

struct Pedido {
    TipoDePedido tipoDePedido;
    ContenidoDePedido contenidoDePedido;
    int numeroDePedido;
};

class Panaderia {
public:
    Panaderia(Config config);
    ~Panaderia();

    void comenzarSimulacion();

    static vector<string> TIPO_A_CADENA;
    static vector<string> CONTENIDO_A_CADENA;

private:
    Config config;
    Pipe canalConRecepcionistas;

    void generarEntidad(Empleado *empleado, int cantidad, Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe);
    TipoDePedido generarPedidoAleatoriamente();
    void notificarFinalizacion();
    void enviarPedidosVacios(TipoDePedido tipoDePedido, int cantidadDePedidos);
    void generarMaestroDeMasaMadre(Pipe canalMaestroAMasaMadre, Pipe canalMaestroMasaMadreAMaestro);
};


#endif //CONCU_BREAD_PANADERIA_H
