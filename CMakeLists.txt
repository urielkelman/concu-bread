cmake_minimum_required(VERSION 3.16)
project(concu_bread)

set(CMAKE_CXX_STANDARD 14)

include_directories(concurrencia/fifos)
include_directories(concurrencia/memoria)
include_directories(concurrencia/pipes)
include_directories(concurrencia/seniales)
include_directories(config)
include_directories(logging)
include_directories(panaderia)

add_executable(concu_bread
        concurrencia/fifos/Fifo.cpp
        concurrencia/fifos/Fifo.h
        concurrencia/fifos/FifoEscritura.cpp
        concurrencia/fifos/FifoEscritura.h
        concurrencia/fifos/FifoLectura.cpp
        concurrencia/fifos/FifoLectura.h
        concurrencia/memoria/MemoriaCompartida.h
        concurrencia/pipes/Pipe.cpp
        concurrencia/pipes/Pipe.h
        concurrencia/seniales/EventHandler.h
        concurrencia/seniales/SIGINT_handler.h
        concurrencia/seniales/SignalHandler.cpp
        concurrencia/seniales/SignalHandler.h
        config/Config.cpp
        config/Config.h
        logging/Logging.cpp
        logging/Logging.h
        panaderia/Empleado.cpp
        panaderia/Empleado.h
        panaderia/Panaderia.cpp
        panaderia/Panaderia.h
        panaderia/Recepcionista.cpp
        panaderia/Recepcionista.h
        main.cpp concurrencia/locks/LockFile.cpp concurrencia/locks/LockFile.h panaderia/MaestroPanadero.cpp panaderia/MaestroPanadero.h panaderia/Maestro.cpp panaderia/Maestro.h panaderia/MaestroPizzero.cpp panaderia/MaestroPizzero.h)
