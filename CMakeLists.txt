cmake_minimum_required(VERSION 3.27)
project(ProjetPOO)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjetPOO main.cpp
        include/Ressource.h
        include/Ressource.h
        include/Revue.h
        include/Vhs.h
        include/RessourceNumerique.h
        include/Mediatheque.h
        include/Livre.h
        include/Dvd.h
        include/Cd.h
        src/Cd.cpp
        src/Dvd.cpp
        src/Livre.cpp
        src/Mediatheque.cpp
        src/Ressource.cpp
        src/RessourceNumerique.cpp
        src/Revue.cpp
        src/Vhs.cpp
        src/ajout.cpp)
