#pragma once
#include "Matrice.h"

class Console {
public:
    Console()  = default;
    ~Console() = default;

    void drawConsole(const Matrice& mat);
    void clearConsole();
};
