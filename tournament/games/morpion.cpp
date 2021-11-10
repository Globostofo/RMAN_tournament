/*

PROJET : Votre équipe est chargée d’organiser un tournoi de petits jeux selon le système suisse.
Fichier d’entrée la liste (nom / prénom) des 120 étudiants de la promoSaisir la graine.
Saisir le nombre d’équipes (entre 10 et 20)Pour chaque équipe :
    •Saisir son nom•Saisir les noms / prénoms des participants
    •Faire un système suisse de compétition
        •Un round par petit jeu
        •Exemple de petits jeux (pendu, agedu capitaine, tic tac toe, pierre feuille ciseau, ...)
        •A la fin d’un round affiche le classement
    •Affiche le classement final
    •Prévoir (au moins) 3 jeu d’essais en entrée et 3 fichiers oracle correspondant

Luke : Memory
Maxime : Morpion
Nicolas : Puissance 4
Romain : Dames
Antoine : Echecs



#include <iostream>

int main() {
  std::cout << "Hello World!\n";
}*/

#include <stdio.h>
#include <iostream>
#include "../global.hpp"

using namespace std;
using namespace global_const;
using namespace global_func;

#define ROW 3
#define COLUMN 3

typedef enum {VOID, ROUND, CROSS} valGrid;
typedef enum {FALSE, TRUE} Bool;
static valGrid grid[ROW][COLUMN];                                                                    //valeur qui peuvent être rentrées dans la grille de jeu (rien, rond ou croix)
static int nextPlayer = ROUND;

void initGrid() {
    int i;
    int j;
    for (i = 0 ; i < ROW ; ++i) {
        for (j = 0 ; j < COLUMN ; ++j) {
            grid [i] [j] = VOID;
        }
    }eve 1 pour etre compatible avec le tableau ayant des indices de 0 a ROW-1
}

void showGrid() {
    int i;
    int j;
    for (i=0; i<ROW; ++i) {
        for (j = 0 ; j < COLUMN ; ++j) {
            switch (grid [i] [j]) {
            case VOID:
                cout << "_ ";
                break;
            case ROUND:
                cout << "O ";
                break;
            case CROSS:
                cout << "X ";
            }
        }
        cout << endl;
    }
}

void placePawn() {
    int row, column;
    Bool correctEntry = FALSE;
    cout << "Indiquez les numéros de la ligne et de la colonne où vous souhaitez placer votre pion: ";
    do {
        cin >> row >> column;
        cout << endl;

        if ((row > 0) && (row <= ROW) && (column > 0) && (column <= COLUMN)) {
            --row;                                                                                 //enleve 1 pour etre compatible avec le tableau ayant des indices de 0 a ROW-1
            --column;
            if (grid[row][column] != VOID) {
                cout << "Cette case contient déjà un pion. Veuillez réessayer : " << endl;
            }
            else {
                correctEntry = TRUE;
                grid[row][column] = (valGrid)nextPlayer;
            }
            if (nextPlayer == ROUND) {
                nextPlayer = CROSS;
            }
            else {
                nextPlayer = ROUND;
            }
        }
        else
            cout << "Numéro de ligne ou de colonne incorrect. Veuillez réessayer : " << endl;
    }
    while (!correctEntry);
}
