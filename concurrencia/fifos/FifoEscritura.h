//
// Created by urielkelman on 14/5/20.
//

#ifndef CONCU_BREAD_FIFOESCRITURA_H
#define CONCU_BREAD_FIFOESCRITURA_H

#include "Fifo.h"

class FifoEscritura : public Fifo {
public:
    FifoEscritura(const char* nombre);
    ~FifoEscritura();

    void abrir();
    ssize_t escribir(const void* buffer,const ssize_t buffsize) const;
};


#endif //CONCU_BREAD_FIFOESCRITURA_H
