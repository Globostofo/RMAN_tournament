#include <iostream>
#include <vector>
#include "../global.hpp"
#include "../structs.h"

using namespace std;
using namespace global_func;

unsigned dames(const string & t1, const string & t2) {

    vector<string> teams = {t1, t2};
    unsigned turn = rand()%2;
    cout << "L'equipe " << teams[turn] << " prends les blancs" << endl;
    pressEnter();

    // Création des pions
    vector<pion> pions;
    for (unsigned i=0; i<10; i++) {

    }

    return 1;
}
