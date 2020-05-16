//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_CONFIG_H
#define CONCU_BREAD_CONFIG_H


#include "../logging/Logging.h"

class Config {
public:
    Config();
    ~Config();
    void configurarMaestrosPizzeros(int maestrosPizzeros);
    void configurarMaestrosPanaderos(int maestrosPanaderos);
    void configurarRecepcionistas(int recepcionistas);
    void configurarCorrectitud(bool correctitud);
    void configurarNivelDeLogging(string nivelDeLogging);
    bool fueCorrectamenteIngresada();

    int obtenerMaestrosPizzeros();
    int obtenerMaestrosPanaderos();
    int obtenerRecepcionistas();
    NivelDeLogging obtenerNivelDeLogging();

private:
    int maestrosPizzeros;
    int maestrosPanaderos;
    int recepcionistas;
    NivelDeLogging nivelDeLogging;
    bool correctitud;
};



#endif //CONCU_BREAD_CONFIG_H