//
// Created by urielkelman on 14/5/20.
//

#ifndef CONCU_BREAD_PIPE_H
#define CONCU_BREAD_PIPE_H

#include <unistd.h>
#include <fcntl.h>

class Pipe {

private:
    int descriptores[2];
    bool lectura;
    bool escritura;

public:
    static const int LECTURA = 0;
    static const int ESCRITURA = 1;

    Pipe();
    ~Pipe();

    void setearModo (const int modo );

    ssize_t escribir(const void* dato, const int longitudDato);
    ssize_t leer(void* buffer, const int buffSize);

    int getFdLectura () const;
    int getFdEscritura () const;

    void cerrar ();
};


#endif //CONCU_BREAD_PIPE_H
