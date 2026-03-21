#include "Matrice.h"
#include "CellVivante.h"
#include "CellMorte.h"
#include "CellObstacle.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

static unique_ptr<Cell> makeCell(int code, int x, int y) {
    switch (code) {
        case 1:  return make_unique<CellVivante>(x, y);
        case 2:  return make_unique<CellObstacle>(0, x, y);
        case 3:  return make_unique<CellObstacle>(1, x, y);
        default: return make_unique<CellMorte>(x, y);
    }
}

Matrice::Matrice(const string& fileName) {
    ifstream file(fileName);
    if (!file) throw runtime_error("Fichier introuvable : " + fileName);

    file >> row >> column;

    // resize sans valeur par défaut, puis remplissage manuel (unique_ptr non copiable)
    matrice.resize(row);
    for (int i = 0; i < row; i++) {
        matrice[i].resize(column);
        for (int j = 0; j < column; j++) {
            int code; file >> code;
            matrice[i][j] = makeCell(code, j, i);
        }
    }

    copyToBuffer();
}

void Matrice::copyToBuffer() {
    buffer.resize(row);
    for (int i = 0; i < row; i++) {
        buffer[i].resize(column);
        for (int j = 0; j < column; j++) {
            int code = matrice[i][j]->getLockState()
            ? matrice[i][j]->getState() + 2
            : matrice[i][j]->getState();
            buffer[i][j] = makeCell(code, j, i);
        }
    }
}

void Matrice::nextGeneration(const IRule& rule) {
    copyToBuffer();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (matrice[i][j]->getLockState()) continue;

            int nb = 0;
            for (int k = -1; k <= 1; k++)
                for (int m = -1; m <= 1; m++) {
                    if (k == 0 && m == 0) continue;
                    int r = (i + k + row)    % row;
                    int c = (j + m + column) % column;
                    if (matrice[r][c]->getState() == 1) nb++;
                }

                int newState = rule.apply(matrice[i][j]->getState(), nb);

            // Cast explicite vers unique_ptr<Cell> pour éviter l'ambiguïté du ?:
            if (newState == 1)
                buffer[i][j] = unique_ptr<Cell>(make_unique<CellVivante>(j, i));
            else
                buffer[i][j] = unique_ptr<Cell>(make_unique<CellMorte>(j, i));
        }
    }

    matrice.swap(buffer);
}

bool Matrice::isStable() const {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            if (matrice[i][j]->getState() != buffer[i][j]->getState())
                return false;
    return true;
}
