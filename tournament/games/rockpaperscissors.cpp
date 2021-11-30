/**
 *
 * @file    rockpaperscissors.cpp
 *
 * @author  A. Lafitte
 *
 * @date    20/11/2021
 *
 * @brief   Mini-jeu du pierre-feuille-ciseaux
 *
 **/

#include "../../global.h"

using namespace std;
using namespace global_files;
using namespace global_func;

short pfc(const string & t1, const string & t2){     //pierre feuille ciseaux
    string p1Choice;
    string p2Choice;
    unsigned p1Points = 0;                                          //declaration des variables
    unsigned p2Points = 0;
    unsigned max = stoi(ask4UInput("Nombre de manches pour gagner : "));//définition du maximum de points
    ofs << endl;

    while ((p1Points < max) && (p2Points < max)){                   //corps du jeu
        p1Choice = ask4UInput(t1 + " choisissez entre pierre, feuille et ciseaux : ");//choix des deux joueurs sur quoi jouer
        p2Choice = ask4UInput(t2 + " choisissez entre pierre, feuille et ciseaux : ");
        ofs << p1Choice + " contre " + p2Choice << endl;

        if ((p1Choice == "feuille" && p2Choice == "pierre") || (p1Choice == "pierre" && p2Choice == "ciseaux") || (p1Choice == "ciseaux" && p2Choice == "feuille")){
            ofs << "l'equipe " + t1 + " gagne la manche" << endl;                               //conditions permettant de déterminer qui gagne un point
            p1Points++;
        }

        else if((p2Choice == "feuille" && p1Choice == "pierre") || (p2Choice == "pierre" && p1Choice == "ciseaux") || (p2Choice == "ciseaux" && p1Choice == "feuille")){
            ofs << "l'equipe " + t2 + " gagne la manche" << endl;
            p2Points++;
        }
        else if(p1Choice == p2Choice)
            ofs << "egalite" << endl;

        else
            ofs << "entrer pierre, feuille ou ciseaux" << endl;

        ofs << to_string(p1Points) << " a " << to_string(p2Points) << endl << endl;
    }

    if(p1Points == max)                                             //renvoie l'équipe gagnante
        return 0;
    else
        return 1;
}
