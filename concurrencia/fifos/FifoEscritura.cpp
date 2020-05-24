//
// Created by urielkelman on 14/5/20.
//

#include "FifoEscritura.h"

FifoEscritura::FifoEscritura(const char* nombre) : Fifo(nombre) {
}

FifoEscritura::~FifoEscritura() {
}

void FifoEscritura::abrir() {
    fd = open(nombre, O_WRONLY);
}

ssize_t FifoEscritura::escribir(const void* buffer, const ssize_t buffsize) const {
    return write(fd, buffer, buffsize);
}
