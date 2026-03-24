#include "Game.h"
#include "Config.h"
#include "Tests.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
    // Mode test : ./Jeu_de_la_vie --test
    if (argc > 1 && string(argv[1]) == "--test") {
        Tests::runAll();
        return 0;
    }

    string filePath = (argc > 1) ? argv[1] : "matrice";
    int    nbIter   = (argc > 2) ? stoi(argv[2]) : 1000;

    try {
        Game game(filePath, nbIter);

        bool stable = false;

        while (game.isRunning()
               && (NB_ITERATIONS == 0 || cptIterations < NB_ITERATIONS)
               && !stable)
        {
            clock_t begin = clock();

            game.draw();
            game.nextGeneration();

            if (cptIterations > 0)
                stable = game.isStable();

            if (cptIterations % NB_IT_SAVE == 0)
                game.save();

            cptIterations++;

            while (clock() - begin < TIME) {}
        }

    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << '\n';
        return 1;
    }

    return 0;
}
