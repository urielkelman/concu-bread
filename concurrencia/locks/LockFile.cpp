//
// Created by urielkelman on 16/5/20.
//

#include "LockFile.h"

#include <utility>

LockFile::LockFile (std::string nombre){
    this->nombre = std::move(nombre);
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open (this->nombre.c_str(), O_CREAT|O_WRONLY, 0777);
}

int LockFile::tomarLock () {
    this->fl.l_type = F_WRLCK;
    return fcntl(this->fd, F_SETLKW, &(this->fl));
}

int LockFile::liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl(this->fd, F_SETLK, &(this->fl));
}

ssize_t LockFile::escribir(const char* buffer, const ssize_t buffsize) const {
    lseek(this->fd, 0, SEEK_END);
    return write(this->fd, buffer, buffsize);
}

LockFile::~LockFile () {
    close(this->fd);
}

LockFile::LockFile() {

}
