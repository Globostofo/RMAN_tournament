/**
 *
 * @file    tictactoe.cpp
 *
 * @author  M. Delin
 *
 * @date    25/11/2021
 *
 * @brief   Mini-jeu du morpion
 *
 **/

#include <cstdlib>
#include <stdio.h>

#include "../../global.h"

using namespace std;
using namespace global_files;
using namespace global_const;
using namespace global_func;

#define ROW 3
#define COLUMN 3

typedef enum {VOID, ROUND, CROSS} valGrid;
valGrid grid[ROW][COLUMN];
int nextPlayer = ROUND;

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
                ofs << " _ ";
                break;
            case ROUND:
                ofs << " O ";
                break;
            case CROSS:
                ofs << " X ";
            }
        }
        ofs << endl << endl;
    }
}

void placePawn() { //Place un pion aux coordonnées indiquées par l'utilisateur, affiche un message d'erreur si le pion ne peut pas être placé (coordonnées incorrectes, pion déjà sur cette case.)
    int row;
    int column;
    bool correctEntry = false;
    do {
        row = stoi(ask4UInput("Equipe " + to_string(nextPlayer) + " veuillez indiquez le numéro de la ligne : "));
        column = stoi(ask4UInput("Et le numéro de la colonne où vous souhaitez placer votre pion : "));
        if ((row > 0) && (row <= ROW) && (column > 0) && (column <= COLUMN)) {
            --row;          // enleve 1 pour etre compatible avec le tableau ayant des indices de 0 à ROW-1
            --column;
            if (grid[row][column] != VOID) {
                ofs << "Cette case contient déjà un pion. Veuillez réessayer : " << endl << endl;
            }
            else {
                correctEntry = true;
                grid[row][column] = (valGrid)nextPlayer;
                if (nextPlayer == ROUND) { // si dernier joueur = rond alors prochain joueur = croix
                    nextPlayer = CROSS;
                }
                else {
                    nextPlayer = ROUND; // sinon reste rond
                }
            }
        }
        else
            ofs << "Numéro de ligne ou de colonne incorrect. Veuillez réessayer : " << endl << endl;
    }
    while (!correctEntry);
}

unsigned endGame() { //Teste si le jeu est terminé (Un gagnant ou match nul. Dans ce cas, octroie 1 point à chaque candidat dans le tournoi.)
    unsigned winnerTemp = 3;
    bool ended = false;
    if (grid[1][1] != VOID) { //   combinaison gagnantes    01 = 11 = 21   //   10 = 11 = 12   //   00 = 11 = 22   //   02 = 11 = 20
        if (((grid[0][1] == grid[1][1]) && (grid[1][1] == grid[2][1])) || ((grid[1][0] == grid[1][1]) && (grid[1][1] == grid[1][2])) || ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2])) || ((grid[0][2] == grid[1][1]) && (grid[1][1] == grid[2][0]))) {
            winnerTemp = grid[1][1];
            ended = true;
        }
    }
    if ((!ended) && (grid[0][0] != VOID)) { //   combinaison gagnantes    00 = 01 = 02   //   00 = 10 = 20
        if (((grid[0][0] == grid[0][1]) && (grid[0][1] == grid[0][2])) || ((grid[0][0] == grid[1][0]) && (grid[1][0] == grid[2][0]))) {
            winnerTemp = grid[0][0];
            ended = true;
        }
    }
    if ((!ended) && (grid[2][2] != VOID)) { //   combinaison gagnantes    20 = 21 = 22   //   02 = 12 = 22
        if (((grid[2][0] == grid[2][1]) && (grid[2][1] == grid[2][2])) || ((grid[0][2] == grid[1][2]) && (grid[1][2] == grid[2][2]))) {
            winnerTemp = grid[2][2];
            ended = true;
        }
    }
    if (ended) {
        if (winnerTemp == ROUND) { // si gagnant = rond
            winnerTemp = 0;
        }
        else {                    // si gagnant = croix
            winnerTemp = 1;
        }
    }
    // si égalité (càd la grille est remplie mais aucune équipe n'a réalisé de combinaison gagnante)
    if ((grid [0] [0] != VOID) && (grid [0] [1] != VOID) && (grid [0] [2] != VOID) && (grid [1] [0] != VOID) && (grid [1] [1] != VOID) && (grid [1] [2] != VOID) && (grid [2] [0] != VOID) && (grid [2] [1] != VOID) && (grid [2] [2] != VOID)) {
        winnerTemp = 2;
    }
    for (unsigned i = 0 ; i < ROW ; ++i) { // tant qu'une case est vide, le jeu continue
        for (unsigned j = 0 ; j < COLUMN; ++j) {
            if (grid [i] [j] == VOID)
                ended = false;
        }
    }
    return winnerTemp;
}

unsigned morpion(const string & t1, const string & t2) {

    vector<string> teams = {t1, t2};
    if (rand()%2 == 1) // Attribue aléatoirement un type de pion à une équipe.
        teams = {t2, t1};
    vector<string> pawnType = {"ronds", "croix"};
    ofs << "L'equipe " << teams[0] << " joue avec les ronds" << endl
        << "L'equipe " << teams[1] << " joue avec les croix." << endl;

    initGrid();

    do { // joue la partie
        placePawn();
        showGrid();
    } while(endGame() == 3);

    return endGame();
}
