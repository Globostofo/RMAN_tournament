/**
 *
 * @file    main.cpp
 *
 * @author  R. Clement
 *
 * @date    27/11/2021
 *
 * @brief   Lancement d'un tournoi
 *
 **/

#include <iostream>

#include "./tournament/tournament.cpp"

using namespace std;
using namespace global_files;

int main(int argc, char *argv[]) {
    // Verification des arguments du programme
    if (argc != 2) {
        cout << "Erreur dans la saisie des arguments (lisez le readme.md pour plus d'informations)" << endl;
        return 0;
    }

    ifs.open(argv[1]);
    ofs.open(ask4UInput("", false));

    // Saisie de la graine
    srand(stoi(ask4UInput("Graine de l'aleatoire : ")));
    pressEnter();

    // Lancement du tournoi
    tournament();

    // Fermeture des fichiers d'entrees et de sorties
    global_files::ifs.close();
    global_files::ofs.close();

    return 0;
}
