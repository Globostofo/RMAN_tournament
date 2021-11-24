#include <vector>
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

bool Guessing_game(const string & t1, const string & t2){                   //le juste prix
    unsigned p1Choice = 0;
    unsigned p2Choice = 0;                                                  // initialisation des variables
    unsigned max = 0;
    unsigned start;
    bool winner;
    srand(1);                                                   // initialisation du random
    cout << "definissez un maximum (unsigned) : ";
    cin >> max;                                                             //choix du maximum
    unsigned guess = rand() % max + 1;                                      //génération du nombre à trouver
    if (rand() % 2 == 0){                                                   //choix aléatoire du joueur qui commence
            cout << endl << "equipe " + t1 + ", commencez" << endl;
            start = 0;
        }
        else{
            cout << endl << "equipe " + t2 + ", commencez" << endl;
            start = 1;
        }
    while(true){                                                             //boucle du jeu
        if (start == 0){
            cout << endl << "equipe " + t1 +  " choisissez un nombre entre 1 et " << max << endl;
            cin >> p1Choice;
            if (p1Choice > max){                                             //conditions indiquant la victoire ou un indice sur le nombre à trouver pour le joueur 1
                cout << "un nombre entre 1 et " << max << ", Tour suivant" << endl;
            }
            else if (p1Choice > guess){
                cout << "c'est moins" << endl;
            }
            else if (p1Choice < guess){
                cout << "c'est plus" << endl;
            }
            else{
                cout << "Bravo ! La victoire reviens a l'equipe " + t1 + " !" << endl;
                winner = 0;
                break;
            }
        }
        else if (start == 1){               
            cout << endl << "equipe " + t2 + " choisissez un nombre entre 1 et " << max << endl;
            cin >> p2Choice;
            if (p2Choice > max){                                             //conditions indiquant la victoire ou un indice sur le nombre à trouver pour le joueur 2
                cout << "un nombre entre 1 et " << max << ", Tour suivant" << endl;
            }
            else if (p2Choice > guess){
                cout << "c'est moins" << endl;
            }
            else if (p2Choice < guess){
                cout << "c'est plus" << endl;
            }
            else{
                cout << "Bravo ! La victoire reviens a l'equipe " + t2 + " !" << endl;
                winner = 1;
                break;
            }
        }
        start = (start + 1) % 2;                                             //permet de changer de joueur à chaque tour
    }
    return winner;                                                           //renvoie l'équipe ayant deviné le nombre
}