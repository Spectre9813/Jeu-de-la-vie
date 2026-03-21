#include "Game.h"
#include "Config.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
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

            // On vérifie la stabilité APRÈS la première génération
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
