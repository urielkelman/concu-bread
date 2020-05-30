//
// Created by urielkelman on 30/5/20.
//

#include <sstream>
#include "SerializadorDePedidos.h"
#include <string.h>

vector<TipoDePedido> SerializadorDePedidos::ENTERO_A_TIPO = {PAN, PIZZA, NOTIFICACION_DE_CIERRE};
vector<ContenidoDePedido> SerializadorDePedidos::ENTERO_A_CONTENIDO = {LLENO, VACIO};

const char* SerializadorDePedidos::serializarPedido(Pedido pedido) {
    stringstream streamPedido;
    streamPedido << to_string(pedido.tipoDePedido);
    streamPedido << to_string(pedido.contenidoDePedido);
    streamPedido << stoi(to_string(pedido.numeroDePedido));
    string pedidoSerializado = streamPedido.str();
    return pedidoSerializado.c_str();
}

Pedido SerializadorDePedidos::deserializarPedido(const char* cadenaPedido) {
    Pedido pedido;
    string a = string(1, cadenaPedido[0]);
    pedido.tipoDePedido = ENTERO_A_TIPO[stoi(a)];
    string b = string(1, cadenaPedido[1]);
    pedido.contenidoDePedido = ENTERO_A_CONTENIDO[stoi(b)];
    int cantidadDeDigitosNumeroDePedido = strlen(cadenaPedido) - 2;
    string numeroDePedidoCadena;
    for(int i = 2; i < cantidadDeDigitosNumeroDePedido + 2; i++){
        numeroDePedidoCadena.push_back(cadenaPedido[i]);
    }
    pedido.numeroDePedido = stoi(numeroDePedidoCadena);
    return pedido;
}
