#include <vector>
#include <iostream>
using namespace std;

bool rock_paper_scissors(const string & t1, const string & t2){
    string p1Choice = "";
    string p2Choice = "";
    unsigned max;
    cout << "combien de points pour gagner ? ";
    cin >> max;
    bool winner;
    unsigned p1Points = 0;
    unsigned p2Points = 0;
    while (p1Points < max && p2Points < max){
        cout << endl << t1 + " choisissez entre pierre, feuille et ciseaux : ";
        cin >> p1Choice;
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << t2 + " choisissez entre pierre, feuille et ciseaux : ";
        cin >> p2Choice;
        cout << p1Choice + " contre " + p2Choice << endl;
        if ((p1Choice == "feuille" && p2Choice == "pierre") || (p1Choice == "pierre" && p2Choice == "ciseaux") || (p1Choice == "ciseaux" && p2Choice == "feuille")){
            cout << "l'equipe " + t1 + " gagne cette manche" << endl;
            p1Points++;
            cout << 'p1Points' + " a " + 'p2Points' << endl;
        }
        else if((p2Choice == "feuille" && p1Choice == "pierre") || (p2Choice == "pierre" && p1Choice == "ciseaux") || (p2Choice == "ciseaux" && p1Choice == "feuille")){
            cout << "l'equipe " + t2 + " gagne cette manche" << endl;
            p2Points++;
            cout << 'p1Points' << " a " << 'p2Points' << endl;
        }
        else if(p1Choice == p2Choice){
            cout << "egalite" << endl;
        }
        else{
            cout << "entrer pierre, feuille ou ciseaux" << endl;
        }
    }
    if(p1Points == 3){
        cout << "La victoire reviens a l'equipe " + t1;
        winner = 0;
    }
    else{
        cout << "La victoire reviens a l'equipe " + t2;
        winner = 1;
    }
    return winner;
}