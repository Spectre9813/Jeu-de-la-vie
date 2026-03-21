#include "Game.h"
#include <fstream>
#include <iostream>
using namespace std;

Game::Game(const string& filePath, int nbIteration)
    : mat(filePath + ".txt"),
      ui(mat.getColumn(), mat.getRow(), CELL_SIZE),
      rule(make_unique<RuleConway>())
{
    saveFileName  = filePath + "_out.txt";
    NB_ITERATIONS = nbIteration;
}

void Game::nextGeneration() {
    mat.nextGeneration(*rule);
}

bool Game::isStable() {
    return mat.isStable();
}

void Game::draw() {
    if (UI) {
        ui.handleEvents();
        ui.drawUi(mat);
    } else if (CONSOLE) {
        console.clearConsole();
        console.drawConsole(mat);
    }
}

void Game::save() {
    ofstream saveFile(saveFileName, ios::app);
    if (!saveFile) { cerr << "Erreur de sauvegarde\n"; return; }

    saveFile << cptIterations << '\n';
    for (int i = 0; i < mat.getRow(); i++) {
        for (int j = 0; j < mat.getColumn(); j++) {
            const auto& cell = mat.matrice[i][j];
            int val = cell->getLockState()
                ? cell->getState() + 2
                : cell->getState();
            saveFile << val;
            if (j < mat.getColumn() - 1) saveFile << ' ';
        }
        saveFile << '\n';
    }
    saveFile.close();
}

bool Game::isRunning() {
    if (UI) return ui.isOpen();
    return true;
}
