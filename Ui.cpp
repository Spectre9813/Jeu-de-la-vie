#include "Ui.h"

Ui::Ui(int width, int height, int cellSize_)
    : window(sf::VideoMode({
                static_cast<unsigned int>(width  * cellSize_),
                static_cast<unsigned int>(height * cellSize_)
              }), "Jeu de la Vie"),
      cellSize(cellSize_),
      cellShape(sf::Vector2f(cellSize_ - 1.0f, cellSize_ - 1.0f))
{
    window.setFramerateLimit(60);
}

Ui::~Ui() {
    if (window.isOpen()) window.close();
}

void Ui::drawUi(const Matrice& mat) {
    window.clear(sf::Color::Black);

    for (int i = 0; i < mat.getRow(); i++) {
        for (int j = 0; j < mat.getColumn(); j++) {
            const auto& cell = mat.matrice[i][j];
            int  state  = cell->getState();
            bool locked = cell->getLockState();

            if (state == 0 && !locked) continue;

            if (locked)
                cellShape.setFillColor(state == 1 ? sf::Color::Green : sf::Color::Blue);
            else
                cellShape.setFillColor(sf::Color::White);

            cellShape.setPosition(sf::Vector2f(
                static_cast<float>(j * cellSize),
                static_cast<float>(i * cellSize)));

            window.draw(cellShape);
        }
    }

    window.display();
}

void Ui::handleEvents() {
    // SFML 3 : pollEvent retourne un optional
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            if (key->code == sf::Keyboard::Key::Escape)
                window.close();
    }
}

bool Ui::isOpen()  { return window.isOpen(); }
void Ui::clear()   { window.clear(sf::Color::Black); }
void Ui::display() { window.display(); }
