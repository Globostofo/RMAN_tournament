/**
 *
 * @file    priceisright.cpp
 *
 * @author  A. Lafitte
 *
 * @date    20/11/2021
 *
 * @brief   Mini-jeu du juste-prix
 *
 **/

#include "../../global.h"

using namespace std;
using namespace global_files;
using namespace global_func;

short justeprix(const string & t1, const string & t2){                   //le juste prix
    unsigned p1Choice = 0;
    unsigned p2Choice = 0;                                                  // initialisation des variables
    unsigned max = stoi(ask4UInput("definissez un maximum (unsigned) : ")); //choix du maximum
    unsigned start;
    bool winner;
    unsigned guess = rand() % max + 1;                                      //génération du nombre à trouver
    if (rand() % 2 == 0){                                                   //choix aléatoire du joueur qui commence
            ofs << endl << "equipe " + t1 + ", commencez" << endl;
            start = 0;
        }
        else{
            ofs << endl << "equipe " + t2 + ", commencez" << endl;
            start = 1;
        }
    while(true){                                                             //boucle du jeu
        if (start == 0){
            p1Choice = stoi(ask4UInput("\nequipe " + t1 + " choisissez un nombre entre 1 et " + to_string(max) + "\n"));
            if (p1Choice > max){                                             //conditions indiquant la victoire ou un indice sur le nombre à trouver pour le joueur 1
                ofs << "un nombre entre 1 et " << max << ", Tour suivant" << endl;
            }
            else if (p1Choice > guess){
                ofs << "c'est moins" << endl;
            }
            else if (p1Choice < guess){
                ofs << "c'est plus" << endl;
            }
            else{
                ofs << "Bravo ! La victoire reviens a l'equipe " + t1 + " !" << endl;
                winner = 0;
                break;
            }
        }
        else if (start == 1){               
            p2Choice = stoi(ask4UInput("\nequipe " + t2 + " choisissez un nombre entre 1 et " + to_string(max) + "\n"));
            if (p2Choice > max){                                             //conditions indiquant la victoire ou un indice sur le nombre à trouver pour le joueur 2
                ofs << "un nombre entre 1 et " << max << ", Tour suivant" << endl;
            }
            else if (p2Choice > guess){
                ofs << "c'est moins" << endl;
            }
            else if (p2Choice < guess){
                ofs << "c'est plus" << endl;
            }
            else{
                ofs << "Bravo ! La victoire reviens a l'equipe " + t2 + " !" << endl;
                winner = 1;
                break;
            }
        }
        start = (start + 1) % 2;                                             //permet de changer de joueur à chaque tour
    }
    return winner;                                                           //renvoie l'équipe ayant deviné le nombre
}
