#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace global_const {
    const string NAMESPATH = "../S101/tournament/students.txt";

    const string waitMsg = "Appuyez sur <ENTREE> pour continuer";

    const unsigned MINTEAMS = 2;
    const unsigned MAXTEAMS = 15;

    const vector<string> GAMESNAME = {"memory",
                                      "morpion",
                                      "puissance 4",
                                      "dames",
                                      "echecs"};
    const unsigned NBGAMES = GAMESNAME.size();
}

namespace global_func {

    void test() {
        cout << "test" << endl;
    }

    vector<string> readFile(const string & path) {
        /// Fonction utilisée pour obtenir la liste des lignes d'un fichier de texte
        vector<string> allLines;
        ifstream ifs (path);
        if (!ifs) return allLines;
        for (string oneLine; getline(ifs, oneLine);)
            allLines.push_back(oneLine);
        return allLines;
    }

    string ask4UInput(const string & invite) {
        /// Fonction utilisee pour demander une entree a l'utilisateur
        cout << invite;
        string answer;
        getline(cin, answer);
        return answer;
    }

    void pressEnter() {
        ask4UInput(global_const::waitMsg + "\n");
    }

    template <typename T>
    vector<T> randomSort(const vector<T> & v) {
        // Algorithme de permutations aléatoire dans une liste
        vector<T> vSorted;
        for (unsigned i=0; i<v.size(); i++)
            vSorted.push_back(v[i]);
        T temp;
        unsigned index;
        for (unsigned i=0; i<vSorted.size(); i++) {
            index = rand() % vSorted.size();
            temp = vSorted[index];
            vSorted[index] = vSorted[i];
            vSorted[i] = temp;
        }
        return vSorted;
    }

    string leftAlign(const string & txt, const unsigned & nb_char) {
        string output = txt;
        while (output.size() < nb_char) {
            output += " ";
        }
        return output;
    }

    string rightAlign(const string & txt, const unsigned & nb_char) {
        string output = txt;
        while (output.size() < nb_char) {
            output = " " + output;
        }
        return output;
    }

    string centerAlign(const string & txt, const unsigned & nb_char) {
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

    void cuteLilBoard(const vector<vector<string>> & content, const vector<char> & align, const bool & header=false) {
        vector<unsigned> colSize;
        for (unsigned i=0; i<content.size(); i++) {
            colSize.push_back(0);
            for (unsigned j=0; j<content[i].size(); j++) {
                cout << content[i][j] << endl;
                if (content[i][j].size() > colSize[i]) {
                    colSize[i] = content[i][j].size();
                }
            }
        }
        unsigned boardWidth=1;
        for (unsigned i=0; i<content.size(); i++) {
            boardWidth += colSize[i] + 3;
        }
        string hBar;
        for (unsigned i=0; i<boardWidth; i++) {
            hBar += "-";
        }

        cout << hBar << "\n|";
        if (header) {
            for (unsigned i=0; i<content.size(); i++) {
                cout << " " << centerAlign(content[i][0], colSize[i]) << " |";
            }
            cout << endl << hBar;
        }
        for (unsigned i=header; i<content[0].size(); i++) {
            cout << "\n|";
            for (unsigned j=0; j<content.size(); j++) {
                if (align[j] == 'l')
                    cout << " " << leftAlign(content[j][i], colSize[j]) << " |";
                else if (align[j] == 'r')
                    cout << " " << rightAlign(content[j][i], colSize[j]) << " |";
                else if (align[j] == 'c')
                    cout << " " << centerAlign(content[j][i], colSize[j]) << " |";
            }
        }
        cout << endl << hBar << endl;
    }
}
