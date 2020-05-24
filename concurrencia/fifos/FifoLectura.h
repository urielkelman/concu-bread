//
// Created by urielkelman on 14/5/20.
//

#ifndef CONCU_BREAD_FIFOLECTURA_H
#define CONCU_BREAD_FIFOLECTURA_H

#include "Fifo.h"

class FifoLectura : public Fifo {
public:
    FifoLectura(const char* nombre);
    ~FifoLectura();

    void abrir();
    ssize_t leer(void* buffer,const ssize_t buffsize) const;
};


#endif //CONCU_BREAD_FIFOLECTURA_H
