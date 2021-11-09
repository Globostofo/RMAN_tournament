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


// x et y inutile ?

struct caseP4 {
    /// Structure de base d'une case banal
    /// (la couleur peut être jaune/rouge/vide)
    unsigned x;
    unsigned y;
    string couleur;
};

vector<vector<caseP4>> initP4(){
    vector<vector<caseP4>> TableauDeP4;
    for(unsigned i = 0; i < 6; i++){
        vector<caseP4> LigneTemp;
        for(unsigned j = 0; j < 7; j++){
            caseP4 p;
            p.couleur = "vide";
            p.x = j;
            p.y = i;
            LigneTemp[j] = p;
        }
        TableauDeP4[i] = LigneTemp;
    }
}





void putRedCoin(){
    //cout << "Choisissez le numéro de la colonne choisie (de 0 à 6)" << endl;

    while(true){
        string columnStr = ask4UInput("Choisissez le numéro de la colonne choisie (de 0 à 6)");
        int columNb = stoi(columnStr,nullptr,10);
        if (columNb<7 && columNb>=0 && TableauDeP4[0][columNb].couleur == "vide")break;
        cout << "Le numéro entré n'est pas valide, réessayez !" << endl;
    }

    for(unsigned i = 0; i<6; i++){
        if(TableauDeP4[i][columNb].couleur == "vide"){
            TableauDeP4[i][columNb].couleur = "Red";
        }
    }


}





//vector<caseP4> initP4 ???














/*

int main() {
    cout << "Hello World!\n";
    return 0;
}*/
