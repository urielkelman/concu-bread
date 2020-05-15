//
// Created by urielkelman on 13/5/20.
//

#ifndef CONCU_BREAD_EVENTHANDLER_H
#define CONCU_BREAD_EVENTHANDLER_H


class EventHandler {

public:
    virtual int handleSignal ( int signum ) = 0;
    virtual ~EventHandler () {};
};


#endif //CONCU_BREAD_EVENTHANDLER_H
