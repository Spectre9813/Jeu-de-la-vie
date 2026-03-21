cmake_minimum_required(VERSION 3.16)
project(Jeu_de_la_vie)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(Jeu_de_la_vie
        main.cpp
        Game.cpp      Game.h
        Matrice.cpp   Matrice.h
        Console.cpp   Console.h
        Ui.cpp        Ui.h
        Cell.h
        CellVivante.h
        CellMorte.h
        CellObstacle.h
        IRule.h
        RuleConway.h
        Rules.h
        Config.h)

target_link_libraries(Jeu_de_la_vie SFML::Graphics SFML::Window SFML::System)
