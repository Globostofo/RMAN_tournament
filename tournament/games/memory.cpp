#include <iostream>
#include "../global.hpp"

using namespace std;
using namespace global_const;
using namespace global_func;

unsigned globalScore;
unsigned scoreT1;
unsigned scoreT2;
unsigned previousCardId;
bool repeat;
int place;

//définition d'une carte

struct card{
    unsigned id;
    string valeur;
    string pos;
    bool trouvey;
};

vector <card> deck (36);

// Affiche les cartes dans un cadrillage : de dos si la carte n'est pas retournée ou touvée, de face dans
// le cas contraire

void tableCard(){
    char ligne;
    ligne = '@';
    int place;
    place = -1;
    cout << "\t  1  \t  2  \t  3  \t  4  \t  5  \t  6  " << endl;
    for( unsigned i = 0; i < 6 ; ++i){

        for( unsigned l = 0; l < 6 ; ++l){
            cout << "\t ____";
        }
        cout <<endl << ++ligne;
        for( unsigned l = 0; l<6 ; ++l){

            ++place;
            if( deck[place].trouvey ){
                cout << "\t |" << deck[place].valeur << deck[place].valeur << "|";
            }
            if( !(deck[place].trouvey) ){
                cout << "\t |  |";
            }
        }
        cout  << endl ;
        for( unsigned l = 0; l < 6 ; ++l){
            cout << "\t |__|";
        }
        cout  << endl ;
    }
}

//Crée un deck de carte à partir des valeurs du fichier memory.txt
//Il attribut aussi l'id et la pos de chacune des cartes

void createCard(){
    vector<string> val = randomSort(readFile("../S101-main/tournament/memory.txt"));

    for( unsigned i = 0; i < 36 ; ++i){
        string x;
        string y;
        string z ;
        if(i<6){

            z = i+'1';
            y = 'A';

        }
        if(i >= 6 && i < 12 ){
            z = i-6 +'1';
            y = 'B';

        }
        if(i >= 12 && i < 18 ){
            z = i-12 +'1';
            y = 'C';
        }
        if(i >= 18 && i < 24 ){
            z = i-18 +'1';
            y = 'D';
        }
        if(i >= 24 && i < 30 ){
         z = i-24 +'1';
            y = 'E';
        }
        if(i >= 30){
            z = i-30 +'1';
            y = 'F';
        }
        x = y + z;
        deck[i] = card {i, val[i], x , false};

    }
}



unsigned turnCard (const string & pos){
    unsigned thisCardId;
    place = -1;
    thisCardId = deck.size();
    for(unsigned i = 0; i < deck.size() ; ++i ){

        // Trouve la carte demandée par l'équipe en jeu grâce à la position de celle-ci

        if( deck[i].pos == pos){
            if( deck[i].trouvey){
                cout << endl << "Cette carte est déjà retournée. On passe à l'équipe suivante." << endl;
                previousCardId = 42;
                deck[previousCardId].trouvey = false;
                repeat = 0;
                tableCard();

                return 2;

            }else{
                deck[i].trouvey = true;
                thisCardId = i;
            }
        }
    }
    tableCard();

    if(previousCardId == 42){

        //première carte jouée durant cette partie de tour

        previousCardId = thisCardId;
        return 0;
    }else{ 

        // seconde carte jouée durant cette partie de tour

        if(!(deck[previousCardId].valeur == deck[thisCardId].valeur)){

            // Renvoie 0 car la carte retournée ne va pas de paire avec la précédente

            cout << "Dommage!" << endl ;
            deck[previousCardId].trouvey = false;
            deck[thisCardId].trouvey = false;
            previousCardId = 42;
            return 0;
        }else{

            // Renvoie 1 car la carte retournée va de paire avec la précédente

            cout << "Bravo!" << endl ;
            previousCardId = 42;
            return 1;
        }

    }
}

// SelectCard demande à l'équipe sélectionée en argument une carte à retourner dans toutes les circonstances
// et compte les points gagnés en un tour.

void selectCard( const unsigned & team){
    previousCardId = 42;
    if(team == 1){
        repeat = turnCard (ask4UInput("Entrez les coordonees de la premiere carte à tourner :"));
        repeat = turnCard (ask4UInput("Entrez les coordonees de la seconde carte à tourner :"));

        //si l'équipe en question a retourné deux cartes identique, elle gagenra autant de point
        // que la boucle se répète

        while (repeat) {
            if(globalScore<18){
                repeat = turnCard (ask4UInput("Entrez les coordonees de la premiere carte à tourner :"));
                repeat = turnCard (ask4UInput("Entrez les coordonees de la seconde carte à tourner :"));
                ++scoreT1;
                globalScore = scoreT1 + scoreT2;
            }else{
                repeat = false;
            }
        }
    }
    if(team == 2){
        repeat = turnCard (ask4UInput("Entrez les coordonees de la premiere carte à tourner :"));
        repeat = turnCard (ask4UInput("Entrez les coordonees de la seconde carte à tourner :"));
        while (repeat) {
            if(globalScore<18){
                repeat = turnCard (ask4UInput("Entrez les coordonees de la premiere carte à tourner :"));
                repeat = turnCard (ask4UInput("Entrez les coordonees de la seconde carte à tourner :"));
                ++scoreT2;
                globalScore = scoreT1 + scoreT2;
            }else{
                repeat = false;
            }
        }
    }
}

//fonction main du jeu : renvoie 0 dans le cas d'une victoire de l'équipe n°1
//                       renvoie 1 dans le cas d'une victoire de l'équipe n°2
//                       renvoie 2 dans le cas d'une égalité.

unsigned memory(const string & t1 , const string & t2) {

    scoreT1 = 0;
    scoreT2 = 0;
    globalScore = 0;

    createCard();

    cout << endl << "Que la partie commence !" << endl << endl;
    pressEnter();

    // Boucle contenant un tour. Sortie une fois le nombre de paires max retournées (18)
    while ( globalScore < 18) {
        tableCard();
        cout << endl << "Equipe " << t1 << " à votre tour!" << endl;
        selectCard(1);
        pressEnter();
        tableCard();

      // Sortie si le score total max atteint avant le tour de la seconde équipe.
        if(globalScore == 18){
            break;
        }

        cout << endl << endl << "Equipe " << t2 << " à votre tour!"<< endl;

        selectCard(2);

        pressEnter();

    }

    // Renvoie en fonction des résultats.

    if( scoreT1 > scoreT2){
        return 0;
    }else if( scoreT1 < scoreT2){
        return 1;
    }else {
        return 2;
    }
}
