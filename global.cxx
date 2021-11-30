/**
 *
 * @file    global.cxx
 *
 * @author  R. Clement
 *
 * @date    25/11/2021
 *
 * @brief   Definition des fichier input/output, des constantes globales et des fonctions globales
 *
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "global.h"

using namespace std;

// Definition des fichiers d'entree et sortie
ifstream global_files::ifs;
ofstream global_files::ofs;


// Definition des constantes globales
const string global_const::WAIT_MSG = "Appuyez sur <ENTREE> pour continuer";
const string global_const::INPUT_ERR_MSG = "La saisie n'est pas ecrite sous la forme attendue";

const unsigned short global_const::MIN_TEAMS = 8;
const unsigned short global_const::MAX_TEAMS = 15;

const vector<string> global_const::GAMES_NAME = {"memory",
                                                 "morpion",
                                                 "puissance 4",
                                                 "echecs",
                                                 "pierre feuille ciseaux",
                                                 "juste prix"};
const unsigned short global_const::NB_GAMES = GAMES_NAME.size();


string global_func::ask4UInput(const string & invite, const bool & putInOutput) {
    /// Fonction utilisee pour demander une entree a l'utilisateur
    if (putInOutput) global_files::ofs << invite;
    string answer;
    while (true) {
        getline(global_files::ifs, answer);
        if (global_files::ifs.eof()) {
            cout << "fin du fichier : aucune donnee recuperee" << endl;
            return "";
        }
        if (answer.size() < 2 || answer[0] != '/' || answer[1] != '/')
            break;
    }
    if (putInOutput) global_files::ofs << answer << endl;
    return answer;
}

void global_func::pressEnter() {
    ask4UInput(global_const::WAIT_MSG + "\n");
}

string global_func::leftAlign(const string & txt, const unsigned & nb_char) {
    string output = txt;
    while (output.size() < nb_char) {
        output += " ";
    }
    return output;
}

string global_func::rightAlign(const string & txt, const unsigned & nb_char) {
    string output = txt;
    while (output.size() < nb_char) {
        output = " " + output;
    }
    return output;
}

string global_func::centerAlign(const string & txt, const unsigned & nb_char) {
    string output = txt;
    bool side=true;
    while (output.size() < nb_char) {
        if (side)
            output += " ";
        else
            output = " " + output;
        side = !side;
    }
    return output;
}

void global_func::cuteLilBoard(const vector<vector<string>> & content, const vector<char> & align, const bool & header) {
    // Taille des colonnes (en caractere)
    vector<unsigned> colSize;
    for (unsigned i=0; i<content.size(); i++) {
        colSize.push_back(0);
        for (unsigned j=0; j<content[i].size(); j++) {
            //global_files::ofs << content[i][j] << endl;
            if (content[i][j].size() > colSize[i]) {
                colSize[i] = content[i][j].size();
            }
        }
    }
    // Largeur du tableau (en caractere)
    unsigned boardWidth=1;
    for (unsigned i=0; i<content.size(); i++) {
        boardWidth += colSize[i] + 3;
    }
    // Barre horizontale
    string hBar;
    for (unsigned i=0; i<boardWidth; i++) {
        hBar += "-";
    }

    // Ecriture du tableau
    if (header) {
        // Si on affiche on a une entête, alors on centre la première ligne
        global_files::ofs << hBar << "\n|";
        for (unsigned i=0; i<content.size(); i++) {
            global_files::ofs << " " << centerAlign(content[i][0], colSize[i]) << " |";
        }
        global_files::ofs << endl << hBar;
    }
    for (unsigned i=header; i<content[0].size(); i++) {
        // Pour chaque ligne (1ère inclue si on n'a pas de header, exlue si on en a un)
        if (!header)
            global_files::ofs << endl << hBar;
        global_files::ofs << "\n|";
        for (unsigned j=0; j<content.size(); j++) {
            if (align.size() != 0) {
                if (align[j] == 'l')
                    global_files::ofs << " " << leftAlign(content[j][i], colSize[j]) << " |";
                else if (align[j] == 'r')
                    global_files::ofs << " " << rightAlign(content[j][i], colSize[j]) << " |";
                else if (align[j] == 'c')
                    global_files::ofs << " " << centerAlign(content[j][i], colSize[j]) << " |";
            } else {
                global_files::ofs << " " << centerAlign(content[j][i], colSize[j]) << " |";
            }
        }
    }
    global_files::ofs << endl << hBar << endl;
}
