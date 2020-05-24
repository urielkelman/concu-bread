//
// Created by urielkelman on 14/5/20.
//

#include "FifoLectura.h"

FifoLectura::FifoLectura(const char* nombre) : Fifo(nombre) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
    fd = open(nombre, O_RDONLY);
}

ssize_t FifoLectura::leer(void* buffer,const ssize_t buffsize) const {
    return read (fd, buffer, buffsize);
}
