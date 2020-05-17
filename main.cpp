#include <iostream>
#include "config/Config.h"
#include "logging/Logging.h"
#include "concurrencia/pipes/Pipe.h"
#include "panaderia/Panaderia.h"
#include <string.h>

using namespace std;

const string DESCRIPCION_DE_USO = "Uso: ./concubread -m $MAESTROS_PANADEROS -n $MAESTROS_PIZZEROS -r $RECEPCIONISTAS "
                                  "-l $NIVEL_DE_LOG";

int determinarCantidadDeParametros(char* argv[]) {
    int i = 0;
    while(argv[i]) i++;
    return i - 1;
}

Config popularParametros(char *argv[]){
    Config config;
    if(strcmp(argv[1], "-m") !=0 || strcmp(argv[3], "-n") != 0 ||
        strcmp(argv[5], "-r") !=0 || strcmp(argv[7], "-l") != 0) {
        config.configurarCorrectitud(false);
        return config;
    } else {
        try {
            config.configurarMaestrosPanaderos(stoi(argv[2]));
            config.configurarMaestrosPizzeros(stoi(argv[4]));
            config.configurarRecepcionistas(stoi(argv[6]));
            config.configurarCorrectitud(true);
            config.configurarNivelDeLogging(argv[8]);
        } catch (const invalid_argument &e) {
            cout << e.what() << "\n";
            config.configurarCorrectitud(false);
        }
        return config;
    }
}

int main(int argc, char *argv[]) {
    int cantidadDeParametros = determinarCantidadDeParametros(argv);
    if(cantidadDeParametros < 8) {
        cout << DESCRIPCION_DE_USO << "\n";
        return 0;
    } else {
        Config config = popularParametros(argv);
        if(!config.fueCorrectamenteIngresada()) {
            cout << DESCRIPCION_DE_USO << "\n";
            return 0;
        } else {
            Logging::Inicializar(config.obtenerNivelDeLogging());
            LOG_INFO("Configuracion correctamente introducida.");
            Panaderia panaderia(config);
            panaderia.comenzarSimulacion(3);
        }
    }

    Logging::Finalizar();

    return 0;
}

