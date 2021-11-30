/**
 *
 * @file    global.h
 *
 * @author  R. Clement
 *
 * @date    25/11/2021
 *
 * @brief   Definition des fichier input/output, des constantes globales et des fonctions globales
 *
 **/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace global_files {
    /// Declaration des fichiers de lecture et d'ecriture

    extern ifstream ifs;
    extern ofstream ofs;
} // global_files

namespace global_const {
    /// Declaration des constantes globales

    extern const string WAIT_MSG;
    extern const string INPUT_ERR_MSG;

    extern const unsigned short MIN_TEAMS;
    extern const unsigned short MAX_TEAMS;

    extern const vector<string> GAMES_NAME;
    extern const unsigned short NB_GAMES;
} // global_const

namespace global_func {
    /// Declaration des fonctions globales

    string ask4UInput(const string & invite="", const bool & putInOutput=true);

    void pressEnter();

    template <typename T>
    void randomSort(vector<T> & v) {
        // Algorithme de permutations aléatoire dans une liste
        T temp;
        unsigned index;
        for (unsigned i=0; i<v.size(); i++) {
            index = rand() % v.size();
            temp = v[index];
            v[index] = v[i];
            v[i] = temp;
        }
    }

    string leftAlign(const string & txt, const unsigned & nb_char);

    string rightAlign(const string & txt, const unsigned & nb_char);

    string centerAlign(const string & txt, const unsigned & nb_char);

    void cuteLilBoard(const vector<vector<string>> & content, const vector<char> & align={}, const bool & header=false);
} // global_func

#endif // GLOBAL_H
