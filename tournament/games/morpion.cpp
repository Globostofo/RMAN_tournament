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
Romain : Echecs
Antoine : Pierre-Feuille-Ciseaux

*/

#include "../global.hpp"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace global_const;
using namespace global_func;

#define ROW 3
#define COLUMN 3

typedef enum {VOID, ROUND, CROSS} valGrid;
static valGrid grid[ROW][COLUMN];
static int nextPlayer = ROUND;

void initGrid() { //Crée un plateau de morpion vide pour faire la partie.
    for (unsigned i = 0 ; i < ROW ; ++i) {
        for (unsigned j = 0 ; j < COLUMN ; ++j) {
            grid [i] [j] = VOID;
        }
    }
}

void showGrid() { //Affiche la grille du morpion dans le terminal.
    for (unsigned i = 0 ; i < ROW ; ++i) {
        for (unsigned j = 0 ; j < COLUMN ; ++j) {
            switch (grid [i] [j]) {
            case VOID:
                cout << " _ ";
                break;
            case ROUND:
                cout << " O ";
                break;
            case CROSS:
                cout << " X ";
            }
        }
        cout << endl << endl;
    }
}

void placePawn() { //Place un pion aux coordonnées indiquées par l'utilisateur, affiche un message d'erreur si le pion ne peut pas être placé (coordonnées incorrectes, pion déjà sur cette case.)
    int row;
    int column;
    bool correctEntry = false;
    do {
        cout << "Joueur " << nextPlayer <<" veuillez indiquez le numéro de la ligne " << endl;
        cin >> row;
        cout << endl << "et le numéro de la colonne où vous souhaitez placer votre pion : " << endl;
        cin >> column;
        cout << endl;
        if ((row > 0) && (row <= ROW) && (column > 0) && (column <= COLUMN)) {
            --row;
            --column;
            if (grid[row][column] != VOID) {
                cout << "Cette case contient déjà un pion. Veuillez réessayer : " << endl << endl;
            }
            else {
                correctEntry = true;
                grid[row][column] = (valGrid)nextPlayer;
                if (nextPlayer == ROUND) {
                    nextPlayer = CROSS;
                }
                else {
                    nextPlayer = ROUND;
                }
            }
        }
        else
            cout << "Numéro de ligne ou de colonne incorrect. Veuillez réessayer : " << endl << endl;
    }
    while (!correctEntry);
}

unsigned endGame() { //Teste si le jeu est terminé (Un gagnant ou match nul. Dans ce cas, octroie 1 point à chaque candidat dans le tournoi.)
    static unsigned winnerTemp = 3;
    static bool ended = false;
    if (grid[1][1] != VOID) {
        if (((grid[0][1] == grid[1][1]) && (grid[1][1] == grid[2][1])) || ((grid[1][0] == grid[1][1]) && (grid[1][1] == grid[1][2])) || ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2])) || ((grid[0][2] == grid[1][1]) && (grid[1][1] == grid[2][0]))) {
            //   combinaison gagnantes    01 = 11 = 21   //   10 = 11 = 12   //   00 = 11 = 22   //   02 = 11 = 20
            winnerTemp = grid[1][1];
            ended = true;
        }
    }
    if ((!ended) && (grid[0][0] != VOID)) {
        if (((grid[0][0] == grid[0][1]) && (grid[0][1] == grid[0][2])) || ((grid[0][0] == grid[1][0]) && (grid[1][0] == grid[2][0]))) {
            //   combinaison gagnantes    00 = 01 = 02   //   00 = 10 = 20
            winnerTemp = grid[0][0];
            ended = true;
        }
    }
    if ((!ended) && (grid[2][2] != VOID)) {
        if (((grid[2][0] == grid[2][1]) && (grid[2][1] == grid[2][2])) || ((grid[0][2] == grid[1][2]) && (grid[1][2] == grid[2][2]))) {
            //   combinaison gagnantes    20 = 21 = 22   //   02 = 12 = 22
            winnerTemp = grid[2][2];
            ended = true;
        }
    }
    if (ended) {
        if (winnerTemp == ROUND) { // si gagnant = rond
            winnerTemp = 0;
        }
        else {
            winnerTemp = 1;
        }
    }
    if ((grid [0] [0] != VOID) && (grid [0] [1] != VOID) && (grid [0] [2] != VOID) && (grid [1] [0] != VOID) && (grid [1] [1] != VOID) && (grid [1] [2] != VOID) && (grid [2] [0] != VOID) && (grid [2] [1] != VOID) && (grid [2] [2] != VOID)) {
        winnerTemp = 2;
    }
    for (unsigned i = 0 ; i < ROW ; ++i) {
        for (unsigned j = 0 ; j < COLUMN; ++j) {
            if (grid [i] [j] == VOID)
                ended = false;
        }
    }
    return winnerTemp;
}

unsigned morpion(const string & t1, const string & t2) {

    static unsigned winner;

    vector<string> teams;
    if (rand()%2 == 0) { // Attribue aléatoirement un type de pion à une équipe.
        teams = {t1, t2};
    } else {
        teams = {t2, t1};
    }
    vector<string> pawnType = {"ronds", "croix"};
    cout << "L'equipe " << teams[0] << " jouera avec les ronds et l'equipe " << teams[1] << " jouera avec les croix." << endl << endl;

    initGrid();

    do { // joue la partie
        placePawn();
        showGrid();
    } while(endGame() == 3);

    if (endGame() == 0) {
        cout << "Bien joué ! L'équipe " << teams[0] << " gagne 2 point!" << endl;
        winner = 0;
    }

    else if (endGame() == 1) {
        cout << "Bien joué ! L'équipe " << teams[1] << " gagne 2 points!" << endl;
        winner = 1;
    }

    else if (endGame() == 2) {
        cout << "Égalité ! Chaque équipe gagne 1 point." << endl;
        winner = 2;
    }
    return winner;
}
