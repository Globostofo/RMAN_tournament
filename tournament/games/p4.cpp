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
#include <random>

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
            TempRow.resize(TempRow.size()+1);
            TempRow[j] = p; // le problème <--
        }
        TabP4.resize(TabP4.size()+1);
        TabP4[i] = TempRow;
    }
    return TabP4;
}


//affiche le tableau de jeux en couleur
void displayTabP4(const vector<vector<cellP4>> & TabP4){
    cout << "0 1 2 3 4 5 6 " << endl << "--------------" << endl;
    for(unsigned i=0; i<6; i++){
        for(unsigned j=0; j<7; j++){
            if(TabP4[i][j].color == "Empty") cout << "  ";
            else if(TabP4[i][j].color == "Yellow") cout << "\033[43m  \033[00m";
            else cout << "\033[41m  \033[00m";
        }
        cout << endl;
    }
    cout << "--------------"<< endl << "0 1 2 3 4 5 6 "  << endl;
}




//fusion des deux put ? doit renvoyer la position du dernier jeton (ou le jeton tout court) ?

//----------------------------- à finir --------------------------------------

int testIfGoodNumber(){
    while(true){
        string columnStr = ask4UInput("Choisissez le numéro de la colonne choisie (de 0 à 6)\n");
        if(columnStr == "0" || columnStr == "1" || columnStr == "2" || columnStr == "3" || columnStr == "4" || columnStr == "5" || columnStr == "6"){
            return stoi(columnStr);
        }
        else cout << "le numéro entré n'a pas été reconnu ! Réessayez.";
    }
}

cellP4 putRedCoin(vector<vector<cellP4>> & TabP4, const string & t2){
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

cellP4 putYellowCoin(vector<vector<cellP4>> & TabP4, const string & t1){
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
// ---------------------------------------------------

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
    while(not(y == 0 || x == 0)){
        y--;
        x--;
    }
    unsigned counter = 0;
    while(not(y == 5 || x == 6)){
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
    while(not(y == 0 || x == 6)){
        y--;
        x++;
    }
    unsigned counter = 0;
    while(not(y == 5 || x == 0)){
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
unsigned p4(const string & t1, const string & t2) { //nom des équipes
    unsigned winner; // 0 si t1 gagne, 1 si t2 gagne
    vector<vector<cellP4>> TabP4 = initP4();
    // votre jeu
    cout << "L'équipe " << t1 << " est jaune."<< endl;
    cout << "L'équipe " << t2 << " est rouge."<< endl;
    cellP4 cell;
    unsigned cpt = 0;
    while(true){
        displayTabP4(TabP4);
        cell = putYellowCoin(TabP4, t1);
        if (isVictory(TabP4, cell)){
            winner = 0;
            displayTabP4(TabP4);
            cout << "L'équipe jaune " << t1 << " a gagné!" << endl;
            break;
        }
        cpt++;
        displayTabP4(TabP4);
        cell = putRedCoin(TabP4, t2);
        if (isVictory(TabP4, cell)){
            winner = 1;
            displayTabP4(TabP4);
            cout << "L'équipe rouge " << t2 << " a gagné!" << endl;
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
    return winner;
}










/*

int main() {
    cout << "Hello World!\n";
    return 0;
}*/
