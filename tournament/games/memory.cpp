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

*/

#include <iostream>

using namespace std;

struct carte{
    unsigned valeur;
    unsigned posX;
    unsigned posY;
    bool trouvey;
};

string createCard(){
    return "";
}
/*
int main() {
    unsigned equipe1;
    cout << "Que la partie commence wouhou !" << endl << endl;
    cout << createCard() << endl << endl << "Equipe n°" << equipe1 << " à votre tour!";
    return 0;
}*/
