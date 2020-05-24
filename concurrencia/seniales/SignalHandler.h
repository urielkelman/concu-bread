//
// Created by urielkelman on 13/5/20.
//

#ifndef CONCU_BREAD_SIGNALHANDLER_H
#define CONCU_BREAD_SIGNALHANDLER_H

#include <signal.h>
#include <stdio.h>
#include <memory.h>

#include "EventHandler.h"

class SignalHandler {

private:
    static SignalHandler* instance;
    static EventHandler* signalHandlers [ NSIG ];

    SignalHandler ( void );
    static void dispatcher ( int signum );

public:
    static SignalHandler* getInstance ();
    static void destruir ();
    EventHandler* registrarHandler ( int signum,EventHandler* eventHandler );
    int removerHandler ( int signum );

};


#endif //CONCU_BREAD_SIGNALHANDLER_H
