#include <vector>
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

bool Guessing_game(const string & t1, const string & t2){
    unsigned p1Choice = 0;
    unsigned p2Choice = 0;
    unsigned max = 0;
    unsigned start;
    bool winner;
    srand(time(nullptr));
    cout << "definissez un maximum (unsigned) : ";
    cin >> max;
    unsigned guess = rand() % max + 1;
    if (rand() % 2 == 0){
            cout << endl << "equipe " + t1 + ", commencez" << endl;
            start = 0;
        }
        else{
            cout << endl << "equipe " + t2 + ", commencez" << endl;
            start = 1;
        }
    while(true){
        if (start == 0){
            cout << endl << "equipe " + t1 +  " choisissez un nombre entre 1 et " << max << endl;
            cin >> p1Choice;
            if (p1Choice > max){
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
            if (p2Choice > max){
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
        start = (start + 1) % 2;
    }
    return winner;
}