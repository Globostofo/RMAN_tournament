#include <fstream>

using namespace std;

namespace global_const {
    const string NAMESPATH = "./students.txt";

    const string waitMsg = "Appuyez sur <entree> pour continuer";

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
}
