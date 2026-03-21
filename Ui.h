#pragma once
#include <SFML/Graphics.hpp>
#include "Matrice.h"

class Ui {
private:
    sf::RenderWindow   window;
    int                cellSize;
    sf::RectangleShape cellShape;

public:
    Ui(int width, int height, int cellSize_);
    ~Ui();

    void drawUi(const Matrice& mat);
    void handleEvents();
    bool isOpen();
    void clear();
    void display();
};
