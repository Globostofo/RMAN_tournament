/**
    PROJET : Votre equipe est chargee d’organiser un tournoi de petits jeux selon le systeme suisse.
    Fichier d’entree la liste (nom / prenom) des 120 etudiants de la promo
        •Saisir la graine.
        •Saisir le nombre d’equipes (entre 10 et 20)Pour chaque equipe :
        •Saisir son nom (D'EQUIPE?)
        •Saisir les noms / prenoms des participants
        •Faire un systeme suisse de competition
        •Un round par petit jeu
        •Exemple de petits jeux (pendu, agedu capitaine, tic tac toe, pierre feuille ciseau, ...)
        •A la fin d’un round affiche le classement
        •Affiche le classement final
        •Prevoir (au moins) 3 jeu d’essais en entree et 3 fichiers oracle correspondant
*/

#include "./tournament/tournament.cpp"

using namespace std;

int main() {
    // Nouvelle graine pour l'aleatoire
    srand(time(NULL));

    // Lancement du tournoi
    tournament();

    return 0;
}
