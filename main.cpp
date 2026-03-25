#include "Tests.h"
#include "Game.h"
#include "Config.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

void printUsage(const string& prog) {
    cerr << "Usage:\n"
         << "  " << prog << " --test\n"
         << "  " << prog << " <fichier> <iterations> --ui\n"
         << "  " << prog << " <fichier> <iterations> --console\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--test") {
        Tests::runAll();
        return 0;
    }

    if (argc < 4) {
        printUsage(argv[0]);
        return 1;
    }

    string filePath = argv[1];
    int    nbIter   = stoi(argv[2]);
    string mode     = argv[3];

    // UI et CONSOLE définis AVANT la construction de Game
    if (mode == "--ui") {
        UI      = true;
        CONSOLE = false;
    } else if (mode == "--console") {
        UI      = false;
        CONSOLE = true;
    } else {
        cerr << "Mode invalide : " << mode << "\n";
        printUsage(argv[0]);
        return 1;
    }

    try {
        // Game construit ICI, après que UI/CONSOLE soient définis
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