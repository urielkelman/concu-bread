#include <iostream>
#include <Config.h>
#include "logging/Logging.h"
#include "concurrencia/pipes/Pipe.h"

using namespace std;

const string RUTA_DE_LOGEO = "log.txt";
const string DESCRIPCION_DE_USO = "Uso: ./concubread --m $MAESTROS_PANADEROS --n $MAESTROS_PIZZEROS --r $RECEPCIONISTAS "
                                  "-l $NIVEL_DE_LOG";

int determinarCantidadDeParametros(char* argv[]) {
    int i = 0;
    while(argv[i]) i++;
    return i - 1;
}

Config popularParametros(char *argv[]){
    Config config;
    int i = 1;
    if(argv[1] != "--m" || argv[3] != "--n" || argv[5] != "--r" || argv[7] != "l") {
        config.configurarCorrectitud(false);
        return config;
    } else {

    }
}

int main(int argc, char *argv[]) {
    int cantidadDeParametros = determinarCantidadDeParametros(argv);
    cout << cantidadDeParametros;
    if(cantidadDeParametros < 8) {
        cout << DESCRIPCION_DE_USO << "\n";
        return 0;
    } else {
        Config config = popularParametros(argv);
        if(!config.fueCorrectamenteIngresada()) {
            cout << DESCRIPCION_DE_USO << "\n";
            return 0;
        } else {

        }
    }

    Logging::Inicializar(RUTA_DE_LOGEO, INFO);

    // LOG_DEBUG("Mensaje de prueba de logeo");

    Logging::Finalizar();

    return 0;
}

