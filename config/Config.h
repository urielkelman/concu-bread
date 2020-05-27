//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_CONFIG_H
#define CONCU_BREAD_CONFIG_H


#include "../logging/Logging.h"

/**
 * Clase que encapsula toda la informacion contenida en la configuracion inicial que introduce el usuario.
 * Posee todos los getters y setters para cumplir con su funcion. Ademas, contiene un atributo y su getter
 * correspondiente para determinar si el ingreso de la configuracion por parte del usuario fue correcta o no.*/
class Config {
public:
    Config();
    ~Config();
    void configurarMaestrosPizzeros(int maestrosPizzeros);
    void configurarMaestrosPanaderos(int maestrosPanaderos);
    void configurarRecepcionistas(int recepcionistas);
    void configurarCorrectitud(bool correctitud);
    void configurarNivelDeLogging(string nivelDeLogging);
    void configurarCantidadDePedidos(int cantidadDePedidos);
    bool fueCorrectamenteIngresada();

    int obtenerMaestrosPizzeros();
    int obtenerMaestrosPanaderos();
    int obtenerRecepcionistas();
    int obtenerCantidadDePedidos();
    NivelDeLogging obtenerNivelDeLogging();

private:
    int maestrosPizzeros;
    int maestrosPanaderos;
    int recepcionistas;
    int cantidadDePedidos;
    NivelDeLogging nivelDeLogging;
    bool correctitud;
};



#endif //CONCU_BREAD_CONFIG_H
