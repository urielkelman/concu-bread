//
// Created by urielkelman on 15/5/20.
//

#ifndef CONCU_BREAD_CONFIG_H
#define CONCU_BREAD_CONFIG_H


class Config {
public:
    Config();
    void configurarMaestrosPizzeros(int maestrosPizzeros);
    void configurarMaestrosPanaderos(int maestrosPanaderos);
    void configurarRecepcionistas(int recepcionistas);
    void configurarCorrectitud(bool correctitud);
    bool fueCorrectamenteIngresada();

private:
    int maestrosPizzeros;
    int maestrosPanaderos;
    int recepcionistas;
    bool correctitud;
};



#endif //CONCU_BREAD_CONFIG_H
