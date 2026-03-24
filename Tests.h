#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <memory>
#include "Matrice.h"
#include "RuleConway.h"
#include "CellVivante.h"
#include "CellMorte.h"
#include "CellObstacle.h"
using namespace std;

class Tests {
public:
    static void runAll() {
        cout << "=== Lancement des tests unitaires ===\n\n";
        testBlockStable();
        testBlinkerPeriod2();
        testGliderAfter4Steps();
        testDeadCellBorn();
        testLivingCellDies();
        testObstacleUnchanged();
        testTorique();
        cout << "\n=== Tous les tests sont passes ===\n";
    }

private:

    static void assertEqual(Matrice& mat, int row, int col, int expected,
                            const string& testName) {
        int got = mat.matrice[row][col]->getState();
        if (got != expected) {
            cerr << "[ECHEC] " << testName
                 << " -> cellule (" << row << "," << col << ")"
                 << " attendu=" << expected << " obtenu=" << got << "\n";
            assert(false);
        }
    }

    static void runN(Matrice& mat, int n) {
        RuleConway rule;
        for (int i = 0; i < n; i++)
            mat.nextGeneration(rule);
    }

    // Block (2x2) : motif stable
    static void testBlockStable() {
        Matrice mat = makeMatrice(6, 6, {{2,2},{2,3},{3,2},{3,3}});
        runN(mat, 10);
        assertEqual(mat, 2, 2, 1, "Block stable");
        assertEqual(mat, 2, 3, 1, "Block stable");
        assertEqual(mat, 3, 2, 1, "Block stable");
        assertEqual(mat, 3, 3, 1, "Block stable");
        assertEqual(mat, 0, 0, 0, "Block stable (mort)");
        cout << "[OK] Block stable apres 10 iterations\n";
    }

    // Blinker : periode 2
    static void testBlinkerPeriod2() {
        Matrice mat = makeMatrice(7, 7, {{3,2},{3,3},{3,4}});
        runN(mat, 1);
        assertEqual(mat, 2, 3, 1, "Blinker vertical");
        assertEqual(mat, 3, 3, 1, "Blinker vertical");
        assertEqual(mat, 4, 3, 1, "Blinker vertical");
        assertEqual(mat, 3, 2, 0, "Blinker horizontal mort");
        assertEqual(mat, 3, 4, 0, "Blinker horizontal mort");
        runN(mat, 1);
        assertEqual(mat, 3, 2, 1, "Blinker retour horizontal");
        assertEqual(mat, 3, 3, 1, "Blinker retour horizontal");
        assertEqual(mat, 3, 4, 1, "Blinker retour horizontal");
        cout << "[OK] Blinker periode 2\n";
    }

    // Glider : meme forme apres 4 iterations (decale d'une case)
    static void testGliderAfter4Steps() {
        Matrice mat = makeMatrice(10, 10, {{1,2},{2,3},{3,1},{3,2},{3,3}});
        runN(mat, 4);
        assertEqual(mat, 2, 3, 1, "Glider apres 4 steps");
        assertEqual(mat, 3, 4, 1, "Glider apres 4 steps");
        assertEqual(mat, 4, 2, 1, "Glider apres 4 steps");
        assertEqual(mat, 4, 3, 1, "Glider apres 4 steps");
        assertEqual(mat, 4, 4, 1, "Glider apres 4 steps");
        cout << "[OK] Glider apres 4 iterations\n";
    }

    // Cellule morte avec 3 voisins -> nait
    static void testDeadCellBorn() {
        Matrice mat = makeMatrice(5, 5, {{3,2},{3,3},{3,4}});
        runN(mat, 1);
        assertEqual(mat, 2, 3, 1, "Cellule morte nait");
        assertEqual(mat, 4, 3, 1, "Cellule morte nait");
        cout << "[OK] Cellule morte avec 3 voisins nait\n";
    }

    // Cellule vivante avec 4 voisins -> meurt
    static void testLivingCellDies() {
        Matrice mat = makeMatrice(5, 5, {{2,2},{1,2},{3,2},{2,1},{2,3}});
        runN(mat, 1);
        assertEqual(mat, 2, 2, 0, "Cellule meurt (4 voisins)");
        cout << "[OK] Cellule vivante avec 4 voisins meurt\n";
    }

    // Obstacle : ne change jamais d'etat
    static void testObstacleUnchanged() {
        Matrice mat = makeMatrice(5, 5, {});
        mat.matrice[2][2] = make_unique<CellObstacle>(1, 2, 2);
        mat.matrice[1][2] = make_unique<CellVivante>(2, 1);
        mat.matrice[3][2] = make_unique<CellVivante>(2, 3);
        mat.matrice[2][1] = make_unique<CellVivante>(1, 2);
        mat.matrice[2][3] = make_unique<CellVivante>(3, 2);
        mat.matrice[1][1] = make_unique<CellVivante>(1, 1);
        runN(mat, 5);
        assertEqual(mat, 2, 2, 1, "Obstacle vivant reste vivant");
        cout << "[OK] Obstacle reste fige apres 5 iterations\n";
    }

    // Grille torique : block a cheval sur les bords
    static void testTorique() {
        Matrice mat = makeMatrice(6, 6, {{0,0},{0,5},{5,0},{5,5}});
        runN(mat, 5);
        assertEqual(mat, 0, 0, 1, "Torique block stable");
        assertEqual(mat, 0, 5, 1, "Torique block stable");
        assertEqual(mat, 5, 0, 1, "Torique block stable");
        assertEqual(mat, 5, 5, 1, "Torique block stable");
        cout << "[OK] Grille torique : block stable sur les bords\n";
    }

    // Helper : cree une Matrice depuis un vecteur de cellules vivantes
    static Matrice makeMatrice(int rows, int cols,
                               const vector<pair<int,int>>& alive) {
        string tmpFile = "/tmp/test_jdlv.txt";
        ofstream f(tmpFile);
        vector<vector<int>> grid(rows, vector<int>(cols, 0));
        for (auto [r, c] : alive) grid[r][c] = 1;
        f << rows << " " << cols << "\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                f << grid[i][j];
                if (j < cols - 1) f << " ";
            }
            f << "\n";
        }
        f.close();
        return Matrice(tmpFile);
    }
};
