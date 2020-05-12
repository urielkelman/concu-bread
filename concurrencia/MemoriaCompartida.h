//
// Created by urielkelman on 12/5/20.
//

#ifndef CONCU_BREAD_MEMORIACOMPARTIDA_H
#define CONCU_BREAD_MEMORIACOMPARTIDA_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>


template <class T> class MemoriaCompartida {

private:
    int	shmId;
    T*	datos;
    int	cantidadProcesosAdosados() const;

public:
    MemoriaCompartida();
    MemoriaCompartida(const std::string& archivo, const char letra);
    ~MemoriaCompartida();

    void crear(const std::string& archivo, const char letra);
    void liberar();

    void escribir ( const T& dato );
    T leer () const;
};

template <class T> MemoriaCompartida<T> :: MemoriaCompartida(): shmId(0), datos(NULL) {
}

template <class T> MemoriaCompartida <T> :: MemoriaCompartida(const std::string& archivo, const char letra): shmId(0), datos(NULL) {
    this->crear(archivo, letra);
}

template <class T> void MemoriaCompartida<T> :: crear(const std::string& archivo, const char letra) {
    key_t clave = ftok (archivo.c_str(), letra);

    if (clave > 0) {
        this->shmId = shmget (clave, sizeof(T), 0644|IPC_CREAT);

        if (this->shmId > 0) {
            void* tmpPtr = shmat (this->shmId, NULL, 0);
            if (tmpPtr != (void*) -1) {
                this->ptrDatos = static_cast<T*> (tmpPtr);
            } else {
                std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
                throw mensaje;
            }
        } else {
            std::string mensaje = std::string("Error en shmget(): ") + std::string(strerror(errno));
            throw mensaje;
        }
    } else {
        std::string mensaje = std::string("Error en ftok(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}



template <class T> void MemoriaCompartida<T> :: liberar() {
    int errorDt = shmdt ((void *) this->datos);

    if (errorDt != -1) {
        int procAdosados = this->cantidadProcesosAdosados();
        if(procAdosados == 0) {
            shmctl (this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::string mensaje = std::string("Error en shmdt(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}

template <class T> MemoriaCompartida<T> :: ~MemoriaCompartida () {
    int errorDt = shmdt (static_cast<void*> (this->ptrDatos));

    if (errorDt != -1) {
        int procAdosados = this->cantidadProcesosAdosados();
        if (procAdosados == 0) {
            shmctl(this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::cerr << "Error en shmdt(): " << strerror(errno) << std::endl;
    }
}

template <class T> void MemoriaCompartida<T> :: escribir (const T& dato) {
    *(this->ptrDatos) = dato;
}

template <class T> T MemoriaCompartida<T> :: leer() const {
    return *(this->ptrDatos);
}

#endif //CONCU_BREAD_MEMORIACOMPARTIDA_H
