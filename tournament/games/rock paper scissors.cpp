#include <vector>
#include <iostream>
using namespace std;

//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

bool rock_paper_scissors(const string & t1, const string & t2){
    string p1Choice = "";
    string p2Choice = "";
    bool winner;
    unsigned p1Points = 0;
    unsigned p2Points = 0;
    while (p1Points < 3 && p2Points < 3){
        cout << t1 << " choisissez entre pierre, papier et ciseaux";
        cin >> p1Choice;
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << t2 + " choisissez entre pierre, papier et ciseaux";
        cin >> p2Choice;
        if ((p1Choice == "feuille" && p2Choice == "pierre") || (p1Choice == "pierre" && p2Choice == "ciseaux") || (p1Choice == "ciseaux" && p2Choice == "feuille")){
            cout << "l'équipe" + t1 + " gagne cette manche";
            p1Points++;
        }
        else if((p2Choice == "feuille" && p1Choice == "pierre") || (p2Choice == "pierre" && p1Choice == "ciseaux") || (p2Choice == "ciseaux" && p1Choice == "feuille")){
            cout << "l'équipe " + t2 + " gagne cette manche";
            p2Points++;
        }
        else if(p1Choice == p2Choice){
            cout << 'égalité';
        }
        else{
            cout << "entrer pierre, feuille ou ciseaux";
        }
    }
    if(p1Points == 3){
        cout << "La victoire reviens à l'équipe " + t1;
        winner = 0;
    }
    else{
        cout << "La victoire reviens à l'équipe " + t2;
        winner = 1;
    }
    return winner;
}

int main() {
    string t1;
    string t2;
    cout << "Entrer le nom de l'equipe 1 : ";
    getline(cin, t1);
    cout << endl << "Entrer le nom de l'équipe 2 : ";
    getline(cin, t2);
    return rock_paper_scissors(t1, t2);
}