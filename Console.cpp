#include "Console.h"
#include "Config.h"
#include <iostream>
using namespace std;

void Console::drawConsole(const Matrice& mat) {
    cout << "Generation : " << cptIterations << "\n";
    for (int i = 0; i < mat.getRow(); i++) {
        for (int j = 0; j < mat.getColumn(); j++) {
            cout << (mat.matrice[i][j]->getState() == 1 ? '#' : '.');
        }
        cout << '\n';
    }
    cout << '\n';
}

void Console::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
