//
// Created by urielkelman on 14/5/20.
//

#include "Fifo.h"

Fifo::Fifo(const char* nombre) : nombre(nombre), fd(-1) {
    mknod(nombre,S_IFIFO|0666,0);
}

Fifo::~Fifo() {
}

void Fifo::cerrar() {
    close(fd);
    fd = -1;
}

void Fifo::eliminar() const {
    unlink(nombre);
}
