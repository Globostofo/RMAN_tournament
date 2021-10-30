#include <vector>
#include <iostream>
using namespace std;

struct pion
{
    vector<int> pos;
    bool couleur;
    bool etat;
    vector<string> pos_suiv;
};

struct tour{
    vector<int> pos;
    bool couleur;
    bool etat;
    vector<string> pos_suiv;
};

struct fou{
    vector<int> pos;
    bool couleur;
    bool etat;
    vector<string> pos_suiv;
};

struct cavalier{
    vector<int> pos;
    bool couleur;
    bool etat;
    vector<string> pos_suiv;
};

struct roi{
    vector<int> pos;
    bool couleur;
    bool etat;
    vector<string> pos_suiv;
};

struct reine{
    vector<int> pos;
    bool couleur;
    bool etat;
    vector<string> pos_suiv;
};
