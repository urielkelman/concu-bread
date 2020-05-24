//
// Created by urielkelman on 13/5/20.
//
#include <iostream>
#include "SignalHandler.h"
#include "../../logging/Logging.h"

SignalHandler* SignalHandler :: instance = NULL;
EventHandler* SignalHandler :: signalHandlers [ NSIG ];

SignalHandler::SignalHandler(){
}

SignalHandler* SignalHandler::getInstance () {
    if (instance == NULL) instance = new SignalHandler();
    return instance;
}

void SignalHandler::destruir() {
    if (instance != NULL) {
        delete (instance);
        instance = NULL;
    }
}

EventHandler* SignalHandler::registrarHandler(int signum, EventHandler* eventHandler) {
    EventHandler* oldEventHandler = SignalHandler::signalHandlers[signum];
    SignalHandler::signalHandlers[signum] = eventHandler;
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SignalHandler::dispatcher;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, signum);
    sigaction(signum, &sa, 0);
    return oldEventHandler;
}

void SignalHandler::dispatcher(int signum) {
    if (SignalHandler::signalHandlers[signum] != NULL){
        SignalHandler::signalHandlers[signum]->handleSignal(signum);
    }
}

int SignalHandler::removerHandler ( int signum ) {

    SignalHandler :: signalHandlers [ signum ] = NULL;
    return 0;
}