//
// Created by urielkelman on 17/5/20.
//

#ifndef CONCU_BREAD_MAESTROPIZZERO_H
#define CONCU_BREAD_MAESTROPIZZERO_H

#include "Maestro.h"

class MaestroPizzero : public Maestro{
public:
    MaestroPizzero();
    ~MaestroPizzero();

private:
    void cocinar() override;
};


#endif //CONCU_BREAD_MAESTROPIZZERO_H
