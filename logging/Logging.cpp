//
// Created by urielkelman on 14/5/20.
//

#include <fstream>
#include "Logging.h"
#include <sys/time.h>
#include <sstream>

using namespace std;

NivelDeLogging Logging::nivelDeLogging;
ofstream Logging::file;
vector<string> Logging::nivelLogStrings = {"INFO", "DEBUG"};

void Logging::Inicializar(const string& ruta, NivelDeLogging _nivelDeLogging) {
    file.open(ruta);
    nivelDeLogging = _nivelDeLogging;

    LOG_INFO("Inicializando log");
}

void Logging::Loggear(NivelDeLogging _nivelDeLogging, std::string mensaje, string pathArchivo, long numeroDelinea) {
    if(_nivelDeLogging > nivelDeLogging) return;
    else {
        string archivo = obtenerNombreArchivo(pathArchivo);
        string time = obtenerTiempo();
        stringstream linea;
        linea << "[" << nivelLogStrings[nivelDeLogging] << "] ";
        linea << archivo << ":" << numeroDelinea << " ";
        linea << time << " | ";
        linea << mensaje << "\n";
        string l = linea.str();
        file << l;
    }
}

string Logging::obtenerTiempo() {
    timeval time;
    gettimeofday(&time, nullptr);

    tm timeinfo;
    localtime_r(&(time.tv_sec), &timeinfo);

    return to_string(timeinfo.tm_hour) + ":" + to_string(timeinfo.tm_min) + ":" + to_string(timeinfo.tm_sec);
}

void Logging::Finalizar() {
    LOG_INFO("Cerrando archivo de log..");
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






