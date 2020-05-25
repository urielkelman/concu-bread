//
// Created by urielkelman on 14/5/20.
//

#ifndef CONCU_BREAD_FIFO_H
#define CONCU_BREAD_FIFO_H


#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class Fifo {

public:
    Fifo(const char* nombre);
    virtual ~Fifo();
    virtual void abrir() = 0;
    void cerrar();
    void eliminar() const;

protected:
    const char* nombre;
    int fd;
};

#endif //CONCU_BREAD_FIFO_H
