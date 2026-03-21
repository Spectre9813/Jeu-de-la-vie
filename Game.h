#pragma once
#include <string>
#include <memory>
#include "Matrice.h"
#include "IRule.h"
#include "RuleConway.h"
#include "Ui.h"
#include "Console.h"
#include "Config.h"
using namespace std;

class Game {
private:
    string            saveFileName;
    Matrice           mat;
    Console           console;
    Ui                ui;
    unique_ptr<IRule> rule;   // règle injectable (pattern Strategy)

public:
    explicit Game(const string& filePath, int nbIteration);
    ~Game() = default;

    void draw();
    void save();
    void nextGeneration();
    bool isRunning();
    bool isStable();
};
