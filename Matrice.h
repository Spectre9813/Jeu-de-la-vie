#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Cell.h"
#include "IRule.h"
using namespace std;

class Matrice {
private:
    int row, column;

public:
    vector<vector<unique_ptr<Cell>>> matrice;
    vector<vector<unique_ptr<Cell>>> buffer;

    explicit Matrice(const string& fileName);

    [[nodiscard]] int getRow()    const { return row; }
    [[nodiscard]] int getColumn() const { return column; }

    // Calcule la génération suivante selon la règle injectée (Strategy)
    void nextGeneration(const IRule& rule);

    // Détecte si la grille n'évolue plus
    [[nodiscard]] bool isStable() const;

private:
    void copyToBuffer();
};
