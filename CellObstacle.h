#pragma once
#include "Cell.h"

class CellObstacle : public Cell {
private:
    int state;
public:
    CellObstacle(int state_, int posX_, int posY_)
        : Cell(posX_, posY_), state(state_) {
        lockState = true;
    }
    [[nodiscard]] int getState() const override { return state; }
    void setState(int) override {}  // obstacle figé : ne change jamais
};
