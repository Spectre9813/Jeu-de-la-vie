# Jeu-de-la-vie

<div align="center">
 
*"Le tout est plus que la somme des parties."*
 
</div>
 
Plus de 65 ans après sa création, on s'intéresse toujours au Jeu de la Vie pour ses règles d'une simplicité trompeuse : à partir de **4 règles**, des motifs paraissant aléatoires peuvent générer une infinité de comportements, avec de nouveaux encore découverts aujourd'hui.
 
---
 
## Vocabulaire
 
- **Grille à deux dimensions** : repère orthonormé représenté en programmation par une **matrice**.
- **Cellule** : une coordonnée sur la grille, pouvant être **vivante** (1) ou **morte** (0).
- **Voisines** : les 8 cellules adjacentes à une cellule donnée (axes orthogonaux et diagonaux).
- **Obstacle** : cellule dont l'état est figé et n'évolue jamais (vivant = 3, mort = 2 dans le fichier).
 
## Règles du jeu (B3/S23)
 
- Une cellule **morte** possédant exactement **3** voisines vivantes **naît**.
- Une cellule **vivante** possédant **2 ou 3** voisines vivantes **survit**, sinon elle **meurt**.
 
---
 
## Architecture du projet
 
Le projet suit les principes **SOLID** et la **programmation orientée objet** :
 
```
├── Cell.h              — classe abstraite (polymorphisme)
├── CellVivante.h       — cellule vivante (hérite de Cell)
├── CellMorte.h         — cellule morte (hérite de Cell)
├── CellObstacle.h      — cellule obstacle figée (hérite de Cell)
├── IRule.h             — interface pour les règles (pattern Strategy)
├── RuleConway.h        — règles B3/S23 (implémente IRule)
├── Matrice.h / .cpp    — grille de cellules, logique de simulation
├── Game.h / .cpp       — orchestration du jeu
├── Ui.h / .cpp         — affichage graphique SFML (découplé de la logique)
├── Console.h / .cpp    — affichage console (découplé de la logique)
├── Config.h            — paramètres globaux
└── main.cpp            — point d'entrée
```
 
---
 
## Format du fichier d'entrée
 
La première ligne contient les dimensions de la grille (`lignes colonnes`), suivie de la matrice d'états :
 
```
6 6
0 0 0 0 0 0
0 0 1 0 0 0
0 0 0 1 0 0
0 1 1 1 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```
 
| Valeur | Signification         |
|--------|-----------------------|
| `0`    | Cellule morte         |
| `1`    | Cellule vivante       |
| `2`    | Obstacle mort (figé)  |
| `3`    | Obstacle vivant (figé)|
 
---
 
## Installation
 
### Prérequis
 
```bash
sudo pacman -S sfml cmake base-devel   # CachyOS / Arch
# ou
sudo apt install libsfml-dev cmake build-essential  # Ubuntu / Debian
```
 
### Compilation
 
```bash
cd "Jeu de la vie Groupe D"
mkdir build && cd build
cmake ..
make
```
 
---
 
## Utilisation
 
```bash
./Jeu_de_la_vie <chemin_fichier> <nb_iterations>
```
 
Exemples :
 
```bash
./Jeu_de_la_vie matrice 1000      # 1000 itérations max
./Jeu_de_la_vie matrice 0         # infini (jusqu'à stabilité ou fermeture)
```
 
> `matrice.txt` doit se trouver dans le même dossier que l'exécutable (`build/`).
 
### Modes d'affichage
 
Dans `Config.h`, choisir le mode souhaité avant de compiler :
 
```cpp
inline bool UI      = true;   // fenêtre graphique SFML
inline bool CONSOLE = false;  // affichage terminal
```
 
### Contrôles (mode graphique)
 
| Touche | Action |
|--------|--------|
| `Échap` | Quitter |
 
---
 
## Fonctionnalités
 
- [x] Simulation du Jeu de la Vie (règles B3/S23)
- [x] Lecture depuis fichier texte
- [x] Mode graphique SFML
- [x] Mode console
- [x] Sauvegarde automatique toutes les `NB_IT_SAVE` itérations
- [x] Détection de stabilité (arrêt automatique si la grille n'évolue plus)
- [x] Grille torique (les bords se rejoignent)
- [x] Cellules obstacles (état figé, vivant ou mort)
- [x] Architecture OOP : hiérarchie `Cell`, pattern Strategy pour les règles
 
---
 
## Paramètres (`Config.h`)
 
| Variable | Valeur par défaut | Description |
|---|---|---|
| `UI` | `true` | Active l'affichage graphique |
| `CONSOLE` | `false` | Active l'affichage console |
| `CELL_SIZE` | `10` | Taille d'une cellule en pixels |
| `NB_IT_SAVE` | `10` | Fréquence de sauvegarde |
| `NB_ITERATIONS` | `0` | Nombre max d'itérations (0 = infini) |
| `TIME` | `50` | Délai entre deux itérations (clock ticks) |
