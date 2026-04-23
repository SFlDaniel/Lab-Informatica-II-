cmake_minimum_required(VERSION 3.16)

project(practica-3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(practica-3 main.cpp
    rle.h rle.cpp
    lz78.h lz78.cpp
    crypto.h crypto.cpp)

include(GNUInstallDirs)
install(TARGETS practica-3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
