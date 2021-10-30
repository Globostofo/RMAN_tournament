#include <iostream>		// std::cout, std::cin
#include <algorithm>	// std::min, std::sort
#include <vector>		// std::vector
#include "global.hpp"	// voir /readme.md
#include "structs.h"	// voir /readme.md

using namespace global_const;
using namespace global_func;


vector<player> createPlayers(const string & namesPath) {
    /// Fonction de création des joueurs suivant le moule de la structure
    vector<string> nameList = readFile(namesPath);
    vector<player> players;
    players.resize(nameList.size() / 2);
    for (unsigned i=0; i<nameList.size()/2; i++) {
        player p;
        p.id = i+1;
        p.first_name = nameList[2*i + 1];
        p.last_name = nameList[2*i];
        players[i] = p;
    }
    return players;
}

vector<team> createTeams(vector<player> & players) {
    /** La creation des equipes est une fonctions qui doit etre appelee au debut d'un tournoi pour la creation et la repartition des equipes.
        Cette fonction :
            - Melange la liste des joueurs (passee en parametre) en permuttant chaque joueur a une place au hasard
            - Affiche le nombre d'equipes realisables entre deux bornes (constants.hpp) ainsi que le nombre de joueurs par equipe et le nombre de joueurs exclus
            - Laisse a l'utilisateur le choix du nombre d'equipes (demande tant que la reponse n'est pas entre les 2 bornes)
            - Choisis au hasard, retire et affiche les joueurs qui sont exclus si le nombre de joueurs n'est pas un multiple du nombre d'equipes
            - Repartie chaque joueur dans les equipes (en triant la liste des equipes par ordre d'ID)
            - Affiche la liste des equipes ainsi que leur joueurs
    */

    unsigned nbP = players.size();

    // Melange des joueurs dans leur liste
    players = randomSort(players);

    // Affichage des possibilites d'equipes
    cout << "Il y a " << nbP << " joueurs dans la liste :" << endl;
    for (unsigned i=MINTEAMS; i<=MAXTEAMS; i++) {
        cout << "  - "
             << i
             << " eq. -> "
             << nbP / i
             << " j/eq. ("
             << nbP % i
             << " j. exclus)"
             << endl;
    }

    // Demande du nombre d'equipes
    unsigned nbT;
    unsigned nbPbT;
    unsigned nbPe;
    while (true) {
        nbT = stoi(ask4UInput("Nombre d'equipes : "));
        if (MINTEAMS <= nbT && nbT <= MAXTEAMS) {
            nbPbT = nbP / nbT;
            nbPe = nbP % nbT;
            break;
        } else {
            cout << "Erreur dans la saisie de la reponse" << endl;
        }
    }

    // Retrait des joueurs supplementaires
    nbP = nbP - nbPe;
    vector<player> excluded;
    for (unsigned i=nbP; i<nbP+nbPe; i++) {
        excluded.push_back(players[i]);
    }
    //excluded = sort(excluded.begin(), excluded.end());
    players.resize(nbP);
    if (nbPe != 0) {
        if (nbPe == 1) {
            cout << "\nLe joueur suivant est exclu :" << endl;
        } else {
            cout << "\nLes joueurs suivants sont exclus :" << endl;
        }
        for (unsigned i=0; i<nbPe; i++) {
            //cout << "  - " << excluded[i] << endl;
        }
    }
    pressEnter();

    // Demande des noms des equipes
    vector<team> teams;
    vector<player> teamsPlayers;
    for (unsigned i=0; i<nbT; i++) {
        teamsPlayers.resize(0);
        for (unsigned j=0; j<nbPbT; j++) {
            teamsPlayers.push_back(players[i * nbPbT + j]);
        }
        team t;
        t.id = i+1;
        t.name = ask4UInput("Nom de l'equipe n°" + to_string(i+1) + " : ");
        t.points = 0;
        //t.players = sort(teamsPlayers.begin(), teamsPlayers.end());
        teams.push_back(t);
        //cout << t << endl;
        pressEnter();
    }

    // Assignation et affiche les joueurs dans leur equipe


    return teams;
}

vector<vector<team>> matchmaking(const vector<team> & teams) {
    /// Fonction de répartition des équipes pour les matchs dans la liste triée des équipes
    vector<vector<team>> board;
    for (unsigned i=0; i<teams.size()/2; i++) {
        vector<team> match {teams[2*i], teams[2*i + 1]};
        board.push_back(match);
    }
    if (teams.size() % 2 == 1) {
        vector<team> match = {teams.back()};
        board.push_back(match);
    }
    return board;
}

vector<team> new_game(const vector<team> & teams, const vector<string> & games, const unsigned & nbRound) {
    vector<vector<team>> board = matchmaking(teams);

    cout << "Manche n°" << nbRound+1 << " : " << games[nbRound] << endl;
    pressEnter();

    return teams;
}

void tournament() {
    // Creation des objets joueurs
    vector<player> players = createPlayers(NAMESPATH);
    // Creation des equipes
    vector<team> teams = createTeams(players);

    // Constantes du tournoi
    const unsigned nbP = players.size();
    const unsigned nbT = teams.size();
    const unsigned nbR = min(NBGAMES, nbT-1);
    const vector<string> games = randomSort(GAMESNAME);

    cout << nbP << endl << nbT << endl << nbR << endl;

    cout << "Le tournoi va commencer !\nIl se déroulera en " << nbR << " manches." << endl;
    pressEnter();

    for (unsigned i=0; i<nbR; i++) {
        teams = new_game(teams, games, i);
    }
}
