//
// Created by urielkelman on 30/5/20.
//

#ifndef CONCU_BREAD_SERIALIZADORDEPEDIDOS_H
#define CONCU_BREAD_SERIALIZADORDEPEDIDOS_H

#include <vector>

using namespace std;

enum ContenidoDePedido {LLENO = 0, VACIO = 1};
enum TipoDePedido {PAN = 0, PIZZA = 1, NOTIFICACION_DE_CIERRE = 2};

struct Pedido {
    TipoDePedido tipoDePedido;
    ContenidoDePedido contenidoDePedido;
    int numeroDePedido;
};

class SerializadorDePedidos {

public:
    static const char* serializarPedido(Pedido pedido);
    static Pedido deserializarPedido(const char* cadenaPedido);

private:
    /**
     * Vectores de strings que sirven para realizar un mapeo entre el contenido de las
     * cadenas que se envian serializadas y los tipos y contenidos de pedidos a los que
     * mapean.*/
    static vector<TipoDePedido> ENTERO_A_TIPO;
    static vector<ContenidoDePedido> ENTERO_A_CONTENIDO;
};


#endif //CONCU_BREAD_SERIALIZADORDEPEDIDOS_H
