#pragma once
#include <string>
using namespace std;

inline string SAVE_FILE_PATH = "";

// Nombre d'itérations pour déclencher une sauvegarde
inline int NB_IT_SAVE = 10;

// Compteur d'itérations global
inline int cptIterations = 0;

// Modes d'affichage
inline bool UI      = true;
inline bool CONSOLE = false;

// Taille des cellules en pixels
inline int CELL_SIZE = 10;

// Nombre max d'itérations (0 = infini)
inline int NB_ITERATIONS = 0;

// Délai minimal entre deux itérations (en clock ticks)
inline int TIME = 50;
