//
// Created by urielkelman on 30/5/20.
//

#include <sstream>
#include "SerializadorDePedidos.h"
#include <string.h>

vector<TipoDePedido> SerializadorDePedidos::ENTERO_A_TIPO = {PAN, PIZZA, NOTIFICACION_DE_CIERRE};
vector<ContenidoDePedido> SerializadorDePedidos::ENTERO_A_CONTENIDO = {LLENO, VACIO};
int SerializadorDePedidos::charsNumeroDePedido = 7;

string SerializadorDePedidos::serializarPedido(Pedido pedido) {
    stringstream streamPedido;
    streamPedido << to_string(pedido.tipoDePedido);
    streamPedido << to_string(pedido.contenidoDePedido);
    string numeroDePedido = to_string(pedido.numeroDePedido);
    int charsPadding = charsNumeroDePedido - numeroDePedido.size();
    for(int i = 1; i <= charsPadding; i++){
        streamPedido << "0";
    }
    streamPedido << numeroDePedido;
    string pedidoSerializado = streamPedido.str();
    return pedidoSerializado;
}

Pedido SerializadorDePedidos::deserializarPedido(const char* cadenaPedido) {
    Pedido pedido;
    string a = string(1, cadenaPedido[0]);
    pedido.tipoDePedido = ENTERO_A_TIPO[stoi(a)];
    string b = string(1, cadenaPedido[1]);
    pedido.contenidoDePedido = ENTERO_A_CONTENIDO[stoi(b)];
    string numeroDePedidoCadena;
    int i = 2;
    while(cadenaPedido[i] == '0') i++;
    for( ; i < strlen(cadenaPedido); i++){
        numeroDePedidoCadena.push_back(cadenaPedido[i]);
    }
    pedido.numeroDePedido = stoi(numeroDePedidoCadena);
    return pedido;
}

string SerializadorDePedidos::serializarPedidoTerminado(CajaConPedido cajaConPedido) {
    stringstream streamPedido;
    streamPedido << to_string(cajaConPedido.tipoDePedido);
    string numeroDePedido = to_string(cajaConPedido.numeroDePedido);
    int charsPadding = charsNumeroDePedido - numeroDePedido.size();
    for(int i = 1; i <= charsPadding; i++){
        streamPedido << "0";
    }
    streamPedido << numeroDePedido;
    string pedidoSerializado = streamPedido.str();
    return pedidoSerializado;
}

CajaConPedido SerializadorDePedidos::deserializarPedidoTerminado(const char *cadenaPedidoTerminado) {
    CajaConPedido cajaConPedido;
    string a = string(1, cadenaPedidoTerminado[0]);
    cajaConPedido.tipoDePedido = ENTERO_A_TIPO[stoi(a)];

    string numeroDePedidoCadena;
    int i = 1;
    while(cadenaPedidoTerminado[i] == '0') i++;
    for( ; i < strlen(cadenaPedidoTerminado); i++){
        numeroDePedidoCadena.push_back(cadenaPedidoTerminado[i]);
    }
    cajaConPedido.numeroDePedido = stoi(numeroDePedidoCadena);
    return cajaConPedido;
}


