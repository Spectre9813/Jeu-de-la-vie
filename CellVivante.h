#pragma once
#include "Cell.h"

class CellVivante : public Cell {
public:
    CellVivante(int posX_, int posY_) : Cell(posX_, posY_) {}
    [[nodiscard]] int getState() const override { return 1; }
};
