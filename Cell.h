#pragma once

class Cell {
protected:
    int posX, posY;
    bool lockState = false;

public:
    Cell() = default;
    Cell(int posX_, int posY_) : posX(posX_), posY(posY_) {}
    virtual ~Cell() = default;

    [[nodiscard]] virtual int  getState()     const = 0;
    [[nodiscard]] virtual bool getLockState() const { return lockState; }
    [[nodiscard]] int getPosX() const { return posX; }
    [[nodiscard]] int getPosY() const { return posY; }

    virtual void setState(int) {}
};
