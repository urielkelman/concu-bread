//
// Created by urielkelman on 15/5/20.
//

#include <unistd.h>
#include <wait.h>
#include <string.h>
#include "Panaderia.h"
#include "Empleado.h"
#include "Recepcionista.h"
#include "MaestroPanadero.h"
#include "MaestroPizzero.h"
#include "MaestroMasaMadre.h"
#include "Repartidor.h"
#include "../concurrencia/seniales/PanaderiaSIGINTHandler.h"

/**
 * Estos dos vectores sirven para poder loggear el tipo de pedido para que aparezca
 * el string correspondiente en vez del numero del enum.*/
vector<string> Panaderia::TIPO_A_CADENA = {"PAN", "PIZZA", "NOTIFICACION_DE_CIERRE"};
vector<string> Panaderia::CONTENIDO_A_CADENA = {"LLENO", "VACIO"};

int Panaderia::BUFFSIZE_PEDIDO = 10;

Panaderia::Panaderia(Config config) {
    LOG_DEBUG("Inicializando panaderia. Mi id de proceso es: " + to_string(getpid()));
    this->config = config;
    this->canalConRecepcionistas = Pipe();
    this->empleados = new vector<pid_t>;
    Pipe canalRecepcionistasMaestroPanadero;
    Pipe canalRecepcionistaMaestroPizzero;
    Pipe canalMaestroAMaestroMasaMadre;
    Pipe canalMaestroMasaMadreAMaestro;
    Recepcionista recepcionista;
    this->generarMaestroDeMasaMadre(canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);
    this->generarRepartidor();
    this->generarEmpleado(&recepcionista, config.obtenerRecepcionistas(), this->canalConRecepcionistas,
                          canalRecepcionistasMaestroPanadero, canalRecepcionistaMaestroPizzero);
    MaestroPanadero maestroPanadero;
    this->generarEmpleado(&maestroPanadero, config.obtenerMaestrosPanaderos(), canalRecepcionistasMaestroPanadero,
                          canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);
    MaestroPizzero maestroPizzero;
    this->generarEmpleado(&maestroPizzero, config.obtenerMaestrosPizzeros(), canalRecepcionistaMaestroPizzero,
                          canalMaestroAMaestroMasaMadre, canalMaestroMasaMadreAMaestro);
}

Panaderia::~Panaderia() {
}

void Panaderia::generarEmpleado(Empleado *empleado, int cantidad, Pipe primerPipe, Pipe segundoPipe, Pipe tercerPipe) {
    for(int i = 1; i <= cantidad; i++){
        pid_t id = fork();
        if(id == 0){
            delete this->empleados;
            empleado->configurarIdentificador(i);
            empleado->configurarPipes(primerPipe, segundoPipe, tercerPipe);
            empleado->esperarPorSolicitudes();
        } else {
            this->empleados->push_back(id);
        }
    }
}

TipoDePedido Panaderia::generarPedidoAleatoriamente(){
    int numeroRandom = rand() % 10 + 1;
    return numeroRandom > 5 ? PAN : PIZZA;
}

void Panaderia::enviarPedidosVacios(TipoDePedido tipoDePedido, int cantidadDePedidos) {
    for(int i = 1; i <= cantidadDePedidos; i++){
        Pedido pedido;
        pedido.tipoDePedido = tipoDePedido;
        pedido.contenidoDePedido = VACIO;
        pedido.numeroDePedido = -i;
        LOG_DEBUG("Enviando notificacion " + to_string(i) + " de finalizacion de pedidos de " + TIPO_A_CADENA[tipoDePedido] + " a recepcionistas.");
        string pedidoSerializado = SerializadorDePedidos::serializarPedido(pedido);
        this->canalConRecepcionistas.escribir(static_cast<const void*>(pedidoSerializado.c_str()), BUFFSIZE_PEDIDO);
    }
}

void Panaderia::notificarFinalizacion() {
    PanaderiaSIGINTHandler panaderiaSigintHandler(this);
    SignalHandler::getInstance()->registrarHandler(SIGINT, &panaderiaSigintHandler);
    this->enviarPedidosVacios(PAN, this->config.obtenerMaestrosPanaderos());
    this->enviarPedidosVacios(PIZZA, this->config.obtenerMaestrosPizzeros());
    for(int i = 1; i <= this->config.obtenerRecepcionistas(); i++){
        Pedido pedido;
        pedido.contenidoDePedido = VACIO;
        pedido.tipoDePedido = NOTIFICACION_DE_CIERRE;
        pedido.numeroDePedido = -i;
        LOG_DEBUG("Enviando notificacion " + to_string(i) + " de cierre de panaderia a recepcionistas.");
        string pedidoSerializado = SerializadorDePedidos::serializarPedido(pedido);
        this->canalConRecepcionistas.escribir(static_cast<const void*>(pedidoSerializado.c_str()), BUFFSIZE_PEDIDO);
    }
    int status;
    bool seEvacuoPanaderia = false;
    while ((wait(&status)) > 0){
        if(WEXITSTATUS(status) != 0 && !seEvacuoPanaderia){
            this->iniciarEvacuacion();
            seEvacuoPanaderia = true;
        }
    }
    this->liberarRecursos();
}

void Panaderia::comenzarSimulacion() {
    string aux;
    cout << "Presione una tecla y enter para comenzar \n";
    cin >> aux;
    for(int i = 1; i <= this->config.obtenerCantidadDePedidos(); i++){
        Pedido pedido;
        TipoDePedido tipoDePedido = this->generarPedidoAleatoriamente();
        pedido.tipoDePedido = tipoDePedido;
        pedido.numeroDePedido = i;
        pedido.contenidoDePedido = LLENO;
        LOG_INFO("Depositando pedido con id: " + to_string(i) + ". El pedido es de: " + TIPO_A_CADENA[tipoDePedido]);
        string pedidoSerializado = SerializadorDePedidos::serializarPedido(pedido);
        this->canalConRecepcionistas.escribir(static_cast<const void*>(pedidoSerializado.c_str()), BUFFSIZE_PEDIDO);
    }

    this->notificarFinalizacion();
}

void Panaderia::generarMaestroDeMasaMadre(Pipe canalMaestroAMasaMadre, Pipe canalMaestroMasaMadreAMaestro) {
    pid_t id = fork();
    if(id == 0){
        delete this->empleados;
        int cocineros = this->config.obtenerMaestrosPanaderos() + this->config.obtenerMaestrosPizzeros();
        MaestroMasaMadre maestroMasaMadre(canalMaestroAMasaMadre, canalMaestroMasaMadreAMaestro, cocineros);
    } else {
        this->empleados->push_back(id);
    }
}

void Panaderia::liberarRecursos() {
    SignalHandler::destruir();
    delete this->empleados;
    LOG_DEBUG("Cerrando canal de comunicacion con recepcionistas.");
    this->canalConRecepcionistas.cerrar();
}

void Panaderia::iniciarEvacuacion() {
    LOG_DEBUG("¡Fuego en la panaderia! Se procedera a evacuar a los empleados.");
    int cantidadDeEmpleados = this->empleados->size();
    for(int i = 1; i <= cantidadDeEmpleados; i++){
        pid_t empleado = empleados->back();
        empleados->pop_back();
        LOG_DEBUG("Enviando aviso de evacuacion a proceso con id: " + to_string(empleado));
        kill(empleado, SIGINT);
    }
    LOG_DEBUG("Aviso de evacuacion enviado a todos los empleados");
}

void Panaderia::generarRepartidor() {
    pid_t id = fork();
    if(id == 0){
        delete this->empleados;
        Repartidor repartidor;
    }
    else {
        this->empleados->push_back(id);
    }
}



