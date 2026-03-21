#pragma once
#include "Cell.h"

class CellMorte : public Cell {
public:
    CellMorte(int posX_, int posY_) : Cell(posX_, posY_) {}
    [[nodiscard]] int getState() const override { return 0; }
};
