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
/**
 * Macros que son exportadas y permiten ser invocadas para utilizar el metodo estatico loggear de la clase Logging. */
#define LOG_INFO(mensaje) Logging::Loggear(INFO, mensaje, __FILE__, __LINE__)
#define LOG_DEBUG(mensaje) Logging::Loggear(DEBUG, mensaje, __FILE__, __LINE__)

class Logging {

public:
    static NivelDeLogging ObtenerNivelDeLogging(string nivelDeLog);

    /** Inicializa el log seteando el nivel de logging introducido por el usuario.*/
    static void Inicializar(NivelDeLogging nivelDeLogging);

    /** Escribe el mensaje que recibe como  el archivo acorde al nivel de log especificado. Soporta escrituras
     * concurrentes, ya que antes de escribir el mensaje adquiere un lock sobre el archivo a escribir. Ademas del
     * mensaje, se incluyen el nombre del archivo que invoco la macro para loggear y la hora en la que se hizo.*/
    static void Loggear(NivelDeLogging nivelDeLogging, string mensaje, string archivo, long linea);

    /** Finaliza el log. Indica el fin de la simulacion.*/
    static void Finalizar();

private:
    static NivelDeLogging nivelDeLogging;
    static vector<string> nivelLogStrings;
    /** Obtiene un string con el tiempo que luego sera agregado cuando se logee una linea.*/
    static string obtenerTiempo();
    /** Obtiene el nombre del archivo desde el cual se invoco la macro para loggear. */
    static string obtenerNombreArchivo(string);
    static int numeroMagicoDePadding;
    static LockFile lock;
    static string ruta;

    Logging();
    ~Logging();
};


#endif //CONCU_BREAD_LOGGING_H
