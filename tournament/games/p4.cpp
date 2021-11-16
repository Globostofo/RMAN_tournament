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

Romain : Dames
Maxime : Morpion
Antoine : Echecs
Nicolas : Puissance 4
Luke : Memory

*/

#include "../global.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace global_const;
using namespace global_func;
using namespace std;


// x et y inutile ? Laisser Empty ou mettre juste un espace à la place ?

struct cellP4 {
    // Structure de base d'une case banal
    // (la couleur peut être Yellow/Red/Empty)
    unsigned x;
    unsigned y;
    string color;
};

// return un vecteur ou faire un void ?

vector<vector<cellP4>> initP4(){
    vector<vector<cellP4>> TabP4;
    for(unsigned i = 0; i < 6; i++){
        vector<cellP4> TempRow;
        for(unsigned j = 0; j < 7; j++){
            cellP4 p;
            p.color = "Empty";
            p.x = j;
            p.y = i;
            TempRow[j] = p;
        }
        TabP4[i] = TempRow;
    }
}



//fusion des deux put ? doit renvoyer la position du dernier jeton (ou le jeton tout court) ?

cellP4 putRedCoin(vector<vector<cellP4>> & TabP4){
    while(true){
        string columnStr = ask4UInput("Choisissez le numéro de la colonne choisie (de 0 à 6)");
        int columnNb = stoi(columnStr,nullptr,10);
        if (columnNb<7 && columnNb>=0 && TabP4[0][columnNb].color == "Empty"){
            for(unsigned i = 0; i<6; i++){
                if(TabP4[i][columnNb].color == "Empty"){
                    TabP4[i][columnNb].color = "Red";
                    return TabP4[i][columnNb];
                }
            }
        }
        cout << "Le numéro entré n'est pas valide, réessayez !" << endl;
    }
}


cellP4 putYellowCoin(vector<vector<cellP4>> & TabP4){
    while(true){
        string columnStr = ask4UInput("Choisissez le numéro de la colonne choisie (de 0 à 6)");
        int columnNb = stoi(columnStr,nullptr,10);
        if (columnNb<7 && columnNb>=0 && TabP4[0][columnNb].color == "Empty"){
            for(unsigned i = 0; i<6; i++){
                if(TabP4[i][columnNb].color == "Empty"){
                    TabP4[i][columnNb].color = "Yellow";
                    return TabP4[i][columnNb];
                }
            }
        }
        cout << "Le numéro entré n'est pas valide, réessayez !" << endl;
    }
}


bool isVictoryRow(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    unsigned counter = 0;
    for(unsigned i = 0; i<7; i++){
        if(counter == 4) return true;
        if(TabP4[cell.y][i].color == cell.color) counter++;
        else counter = 0;
    }
    return false;
}

bool isVictoryColumn(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    unsigned counter = 0;
    for(unsigned i = 0; i<6; i++){
        if(counter == 4) return true;
        if(TabP4[i][cell.x].color == cell.color) counter++;
        else counter = 0;
    }
    return false;
}

// mettre cell en const ?

bool isVictoryDiagonalDecrease(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    unsigned x = cell.x;
    unsigned y = cell.y;
    while(y != 0 || x != 0){
        y--;
        x--;
    }
    unsigned counter = 0;
    while(y != 5 || x != 6){
        if(counter == 4) return true;
        if(TabP4[y][x].color == cell.color) counter++;
        else counter = 0;
        x++;
        y++;
    }
    return false;
}

bool isVictoryDiagonalIncrease(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    unsigned x = cell.x;
    unsigned y = cell.y;
    while(y != 0 || x != 6){
        y--;
        x++;
    }
    unsigned counter = 0;
    while(y != 5 || x != 0){
        if(counter == 4) return true;
        if(TabP4[y][x].color == cell.color) counter++;
        else counter = 0;
        y++;
        x--;
    }
    return false;
}



bool isVictoryDiagonals(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    if(isVictoryDiagonalDecrease(TabP4, cell) || isVictoryDiagonalIncrease(TabP4, cell)) return true;
    else return false;
}

bool isVictory(const vector<vector<cellP4>> & TabP4, const cellP4 & cell){
    if(isVictoryRow(TabP4, cell) || isVictoryColumn(TabP4, cell) || isVictoryDiagonals(TabP4, cell)) return true;
    else return false;
}


//modif init ?
unsigned nomDuJeu(const string & t1, const string & t2) { //nom des équipes

    unsigned winner; // 0 si t1 gagne, 1 si t2 gagne
    initP4();
    // votre jeu 
    bool varTrue = true;
    while(varTrue){
        cellP4 cell = putRedCoin(TabP4);
    }

    return winner;
}










/*

int main() {
    cout << "Hello World!\n";
    return 0;
}*/

