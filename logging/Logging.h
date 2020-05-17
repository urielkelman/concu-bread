//
// Created by urielkelman on 14/5/20.
//

#ifndef CONCU_BREAD_LOGGING_H
#define CONCU_BREAD_LOGGING_H

#include <string>
#include <vector>
#include <map>
#include "../concurrencia/locks/LockFile.h"

using namespace std;

enum NivelDeLogging {INFO = 0, DEBUG = 1};

#define LOG_INFO(mensaje) Logging::Loggear(INFO, mensaje, __FILE__, __LINE__)
#define LOG_DEBUG(mensaje) Logging::Loggear(DEBUG, mensaje, __FILE__, __LINE__)

class Logging {

public:
    static NivelDeLogging ObtenerNivelDeLogging(string nivelDeLog);

    static void Inicializar(NivelDeLogging nivelDeLogging);

    static void Loggear(NivelDeLogging nivelDeLogging, string mensaje, string archivo, long linea);

    static void Finalizar();

private:
    static NivelDeLogging nivelDeLogging;
    static vector<string> nivelLogStrings;
    static string obtenerTiempo();
    static string obtenerNombreArchivo(string);
    static int numeroMagicoDePadding;
    static LockFile lock;
    static string ruta;

    Logging();
    ~Logging();
};


#endif //CONCU_BREAD_LOGGING_H
