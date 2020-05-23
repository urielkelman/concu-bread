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
    std::string archivo = "/bin/bash";

public:
    MemoriaCompartida();
    MemoriaCompartida(const char letra);
    ~MemoriaCompartida();

    void crear(const char letra);
    void liberar();

    void escribir ( const T& dato );
    T leer () const;
};

template <class T> MemoriaCompartida<T> :: MemoriaCompartida(): shmId(0), datos(NULL) {
}

template <class T> MemoriaCompartida <T> :: MemoriaCompartida(const char letra): shmId(0), datos(NULL) {
    this->crear(letra);
}

template <class T> void MemoriaCompartida<T> :: crear(const char letra) {
    key_t clave = ftok(archivo.c_str(), letra);

    if (clave > 0) {
        this->shmId = shmget (clave, sizeof(T), 0644|IPC_CREAT);

        if (this->shmId > 0) {
            void* tmpPtr = shmat (this->shmId, NULL, 0);
            if (tmpPtr != (void*) -1) {
                this->datos = static_cast<T*> (tmpPtr);
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
    int errorDt = shmdt (static_cast<void*> (this->datos));

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
    *(this->datos) = dato;
}

template <class T> T MemoriaCompartida<T> :: leer() const {
    return *(this->datos);
}

template <class T> int MemoriaCompartida<T> :: cantidadProcesosAdosados () const {
    shmid_ds estado;
    shmctl ( this->shmId,IPC_STAT,&estado );
    return estado.shm_nattch;
}

#endif //CONCU_BREAD_MEMORIACOMPARTIDA_H
