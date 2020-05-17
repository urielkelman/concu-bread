//
// Created by urielkelman on 16/5/20.
//

#ifndef CONCU_BREAD_LOCKFILE_H
#define CONCU_BREAD_LOCKFILE_H


#include <unistd.h>
#include <fcntl.h>
#include <string>

class LockFile {

private:
    struct flock fl;
    int fd;
    std::string nombre;

public:
    LockFile ( const std::string nombre );
    ~LockFile();

    int tomarLock ();
    int liberarLock ();
    ssize_t escribir ( const char* buffer, const ssize_t buffsize ) const;
};


#endif //CONCU_BREAD_LOCKFILE_H
