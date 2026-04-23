cmake_minimum_required(VERSION 3.16)

project(Lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab main.cpp
    dinero.h
    dinero.cpp
    cadenas.h
    cadenas.cpp
    bloques.h
    bloques.cpp
    repetidos.h
    repetidos.cpp
    convertir.h
    convertir.cpp)

include(GNUInstallDirs)
install(TARGETS Lab
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
