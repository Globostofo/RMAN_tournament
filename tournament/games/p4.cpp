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

*/

#include "../global.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace global_const;
using namespace global_func;
using namespace std;


// structure d'une case de puissance 4

struct cellP4 {
    // (la couleur peut être Yellow/Red/Empty)
    unsigned x;
    unsigned y;
    string color;
};



// créé un tableau 6x7 de puissance 4 via un vecteur de vecteur de structure

vector<vector<cellP4>> initP4(){
    vector<vector<cellP4>> TabP4;
    for(unsigned i = 0; i < 6; i++){
        vector<cellP4> TempRow;
        for(unsigned j = 0; j < 7; j++){
            cellP4 p;
            p.color = "Empty";
            p.x = j;
            p.y = i;
            TempRow.resize(TempRow.size()+1);
            TempRow[j] = p;
        }
        TabP4.resize(TabP4.size()+1);
        TabP4[i] = TempRow;
    }
    return TabP4;
}



// affiche le tableau de jeux en couleur

void displayTabP4(const vector<vector<cellP4>> & TabP4){
    cout << " 0  1  2  3  4  5  6 " << endl;
    for(unsigned i=0; i<6; i++){
        cout << "----------------------" << endl << "|";
        for(unsigned j=0; j<7; j++){
            if(TabP4[i][j].color == "Empty") cout << "  " << "|";
            else if(TabP4[i][j].color == "Yellow") cout << "\033[43m " << "\033[33mJ\033[00m" << "|";
            else cout << "\033[41m " << "\033[31mR\033[00m" << "|";
        }
        cout << endl;
    }
    cout << "----------------------" << endl << " 0  1  2  3  4  5  6 "  << endl;
}



// demande la saisie d'un chiffre en string, vérifie si il est compris entre 0 et 6, le converse en int et le renvoie

int testIfGoodNumber(){
    while(true){
        string columnStr = ask4UInput("Choisissez le numéro de la colonne choisie (de 0 à 6)\n");
        if(columnStr == "0" || columnStr == "1" || columnStr == "2" || columnStr == "3" || columnStr == "4" || columnStr == "5" || columnStr == "6"){
            return stoi(columnStr);
        }
        else cout << "le numéro entré n'a pas été reconnu ! Réessayez." << endl;
    }
}



// demande à l'équipe rouge la saisie d'un chiffre via la fonction testIfGoodNumber vérifie si la colonne correspondante est vide et change la couleur de la case vide la plus basse

cellP4 putRedCoin(vector<vector<cellP4>> & TabP4, const string & t2){
    while(true){
        cout << "Équipe rouge " << t2 << endl;
        int columnNb = testIfGoodNumber();
        if (columnNb<7 && columnNb>=0 && TabP4[0][columnNb].color == "Empty"){
            for(unsigned i = 5; i>=0; i--){
                if(TabP4[i][columnNb].color == "Empty"){
                    TabP4[i][columnNb].color = "Red";
                    return TabP4[i][columnNb];
                }
            }
        }
        cout << "Le numéro entré n'est pas valide, réessayez !" << endl;
    }
}

// demande à l'équipe jaune la saisie d'un chiffre via la fonction testIfGoodNumber vérifie si la colonne correspondante est vide et change la couleur de la case vide la plus basse



cellP4 putYellowCoin(vector<vector<cellP4>> & TabP4, const string & t1){
    while(true){
        cout << "Équipe jaune " << t1 << endl;
        int columnNb = testIfGoodNumber();
        if (columnNb<7 && columnNb>=0 && TabP4[0][columnNb].color == "Empty"){
            for(unsigned i = 5; i>=0; i--){
                if(TabP4[i][columnNb].color == "Empty"){
                    TabP4[i][columnNb].color = "Yellow";
                    return TabP4[i][columnNb];
                }
            }
        }
        cout << "Le numéro entré n'est pas valide, réessayez !" << endl;
    }
}



// vérifie la ligne de la case passée en élément et renvoie true si 4 cases adjacentes sont de la même couleur que la case passée en élément

bool isVictoryRow(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    unsigned counter = 0;
    for(unsigned i = 0; i<7; i++){
        if(TabP4[cell.y][i].color == cell.color) counter++;
        else counter = 0;
        if(counter == 4) return true;
    }
    return false;
}



// vérifie la colonne de la case passée en élément et renvoie true si 4 cases adjacentes sont de la même couleur que la case passée en élément

bool isVictoryColumn(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    unsigned counter = 0;
    for(unsigned i = 0; i<6; i++){
        if(TabP4[i][cell.x].color == cell.color) counter++;
        else counter = 0;
        if(counter == 4) return true;
    }
    return false;
}



// se positionne dans le coin supérieur gauche du tableau où une droite x = -y passe aussi par la case passé en élément,
// parcours la droite et renvoie true si 4 cases consécutives possèdent la même couleur que la case passée en élément

bool isVictoryDiagonalDecrease(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    int x = cell.x;
    int y = cell.y;
    while(not(y == 0 || x == 0)){
        y--;
        x--;
    }
    y--;
    x--;

    unsigned counter = 0;
    while(not(y == 5 || x == 6)){
        x++;
        y++;
        if(TabP4[y][x].color == cell.color) counter++;
        else counter = 0;
        if(counter == 4) return true;
    }
    return false;
}



// se positionne dans le coin inférieur gauche du tableau où une droite x = y passe aussi par la case passé en élément
// parcours la droite et renvoie true si 4 cases consécutives possèdent la même couleur que la case passée en élément

bool isVictoryDiagonalIncrease(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    int x = cell.x;
    int y = cell.y;
    while(not(y == 0 || x == 6)){
        y--;
        x++;
    }
    y--;
    x++;
    unsigned counter = 0;
    while(not(y == 5 || x == 0)){
        y++;
        x--;
        if(TabP4[y][x].color == cell.color) counter++;
        else counter = 0;
        if(counter == 4) return true;
    }
    return false;
}



// appelle les fonctions isVictoryDiagonalDecrease et isVictoryDiagonalIncrease, renvoie true si l'une d'elles ou les deux renvoie true

bool isVictoryDiagonals(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    if(isVictoryDiagonalDecrease(TabP4, cell) || isVictoryDiagonalIncrease(TabP4, cell)) return true;
    else return false;
}



// appelle les fonctions isVictoryRow, isVictoryColumn et isVictoryDiagonals, renvoie true si l'une d'elles ou les deux renvoie true

bool isVictory(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    if(isVictoryRow(TabP4, cell) || isVictoryColumn(TabP4, cell) || isVictoryDiagonals(TabP4, cell)) return true;
    else return false;
}



// lance une partie de puissance 4, la fonction est appellée par le programme tournament

unsigned p4(const string & t1, const string & t2) { // t1 et t2 correspondent au nom des équipes

    unsigned winner; // winner sera renvoyé à la fin du programme, winner sera égal à 0 si t1 gagne, 1 si t2 gagne ou 2 si il y a égalité

    // Choix aleatoire des couleurs
    vector<string> teams = {t1, t2};
    if (rand()%2 == 0) teams = {t2, t1};

    vector<vector<cellP4>> TabP4 = initP4(); // initialise un tableau de puissance 4

    cout << "L'équipe " << teams[0] << " est jaune."<< endl;
    cout << "L'équipe " << teams[1] << " est rouge."<< endl;
    cellP4 cell;
    unsigned cpt = 0;

    // les jaunes et les rouges jouent chaqu'un à leur tour, tant qu'il n'y a pas de victoire
    while(true){
        displayTabP4(TabP4);
        cell = putYellowCoin(TabP4, teams[0]);
        if (isVictory(TabP4, cell)){
            if (teams[0] == t1)winner = 0;
            else winner = 1;
            displayTabP4(TabP4);
            cout << "L'équipe jaune " << teams[0] << " a gagné!" << endl;
            break;
        }
        cpt++;
        displayTabP4(TabP4);
        cell = putRedCoin(TabP4, teams[1]);
        if (isVictory(TabP4, cell)){
            if (teams[1] == t2)winner = 1;
            else winner = 0;
            displayTabP4(TabP4);
            cout << "L'équipe rouge " << teams[1] << " a gagné!" << endl;
            break;
        }
        cpt++;
        if (cpt  == 42){
            winner = 2;
            displayTabP4(TabP4);
            cout << "Aucune équipe n'a gagné, égalité!" << endl;
            break;
        }
    }

    return winner; // renvoie le numéro du gagnant, 0 si t1 gagne, 1 si t2 gagne ou 2 si il y a égalité
}

