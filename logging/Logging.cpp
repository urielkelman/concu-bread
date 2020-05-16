//
// Created by urielkelman on 14/5/20.
//

#include <fstream>
#include "Logging.h"
#include <sys/time.h>
#include <ctime>
#include <sstream>

using namespace std;

NivelDeLogging Logging::nivelDeLogging;
ofstream Logging::file;
vector<string> Logging::nivelLogStrings = {"INFO", "DEBUG"};
int Logging::numeroMagicoDePadding = 22;

NivelDeLogging Logging::ObtenerNivelDeLogging(string nivelDeLog) {
    if(nivelLogStrings[INFO] == nivelDeLog){
        return INFO;
    } else if (nivelLogStrings[DEBUG] == nivelDeLog){
        return DEBUG;
    } else {
        throw "Valor de nivel de logging invalido. Utilice DEBUG o INFO";
    }
}

void Logging::Inicializar(const string& ruta, NivelDeLogging _nivelDeLogging) {
    file.open(ruta);
    nivelDeLogging = _nivelDeLogging;

    LOG_INFO("Inicializando log.");
}

void Logging::Loggear(NivelDeLogging _nivelDeLogging, string mensaje, string pathArchivo, long numeroDelinea) {
    if(_nivelDeLogging > nivelDeLogging) return;
    else {
        string archivo = obtenerNombreArchivo(pathArchivo);
        string time = obtenerTiempo();
        stringstream linea;
        linea << "[" << nivelLogStrings[_nivelDeLogging] << "] ";
        string archivoMasLinea = archivo + ":" + to_string(numeroDelinea);
        string archivoMasLineaPaddeado = archivoMasLinea.append(numeroMagicoDePadding - archivoMasLinea.length(), ' ');
        linea << archivoMasLineaPaddeado;
        linea << time << " | ";
        linea << mensaje << "\n";
        string l = linea.str();
        file << l;
        file.flush();
    }
}

string Logging::obtenerTiempo() {
    time_t ahora = time(nullptr);
    struct tm *timeinfo;
    char buffer[100];
    time(&ahora);
    timeinfo = localtime(&ahora);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    string tiempo = string(buffer);
    return tiempo;
}

void Logging::Finalizar() {
    LOG_INFO("Cerrando archivo de log.");
    file.close();
}

string Logging::obtenerNombreArchivo(string rutaArchivo) {
    istringstream ss(rutaArchivo);
    vector<string> routes;
    string buf;
    while(getline(ss, buf, '/')) {
        routes.push_back(buf);
    }

    return routes.back();
}








