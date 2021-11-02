#include <algorithm>    // std::sort
#include "global.hpp"
#include "structs.h"
// Importation des jeux
#include "games/morpion.cpp"
#include "games/memory.cpp"
#include "games/p4.cpp"
#include "games/dames.cpp"
#include "games/echecs.cpp"

using namespace global_const;
using namespace global_func;

void dispBoard(const vector<team> & teams) {
    cout << "Classement actuel des équipes :" << endl;
    for (unsigned i=0; i<teams.size(); i++) {
        cout << i+1 << ". " << teams[i].name << endl;
    }
}

vector<player> createPlayers(const string & namesPath) {
    /// Fonction de création des joueurs suivant le moule de la structure
    vector<string> nameList = readFile(namesPath);
    vector<player> players;
    players.resize(nameList.size() / 2);
    for (unsigned i=0; i<nameList.size()/2; i++) {
        player p;
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
    sort(excluded.begin(), excluded.end());
    players.resize(nbP);
    if (nbPe != 0) {
        if (nbPe == 1) {
            cout << "\nLe joueur suivant est exclu :" << endl;
        } else {
            cout << "\nLes joueurs suivants sont exclus :" << endl;
        }
        for (unsigned i=0; i<nbPe; i++) {
            cout << "  - " << excluded[i] << endl;
        }
    }
    pressEnter();

    // Demande des noms des equipes
    vector<team> teams;
    for (unsigned i=0; i<nbT; i++) {
        vector<player> teamsPlayers;
        for (unsigned j=0; j<nbPbT; j++) {
            teamsPlayers.push_back(players[i*nbPbT + j]);
        }
        team t;
        t.name = ask4UInput("Nom de l'equipe n°" + to_string(i+1) + " : ");
        t.points = 0;
        sort(teamsPlayers.begin(), teamsPlayers.end());
        t.players = teamsPlayers;
        teams.push_back(t);
        cout << t.name << " :" << endl;

        for (const player & p : teamsPlayers) {
            cout << "  - " << p << endl;
        }
        pressEnter();
    }

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

vector<team> round(vector<team> & teams, const string & game) {
    vector<vector<team>> board = matchmaking(teams);

    for (unsigned i=0; i<board.size(); i++) {
        unsigned winner=0;
        if (board[i].size() == 2) {
            team t1 = board[i][0];
            team t2 = board[i][1];
            cout << "Rencontre n°" << i+1 << " : " << t1.name << " vs " << t2.name << endl;
            pressEnter();

            if (game == "memory") {
                //winner = memory(t1.name, t2.name);
            }
            else if (game == "morpion") {
                //winner = morpion(t1.name, t2.name);
            }
            else if (game == "puissance 4") {
                //winner = p4(t1.name, t2.name);
            }
            else if (game == "dames") {
                winner = dames(t1.name, t2.name);
            }
            else if (game == "echecs") {
                //winner = echecs(t1.name, t2.name);
            }
            cout << "L'equipe " << board[i][winner].name << " gagne 1 point" << endl;
        } else {
            team t = board[i][0];
            cout << "L'equipe " << t.name << " est exemptee, elle gagne 1 point" << endl;
            winner = 0;
        }
        cout << board[i][winner].points << endl;
        board[i][winner].points++;
        cout << board[i][winner].points << endl;
        pressEnter();
    }

    for (unsigned i=0; i<teams.size(); i++) {
        cout << teams[i].points << endl;
    }
    sort(teams.begin(), teams.end());
    dispBoard(teams);
    pressEnter();

    return teams;
}

void tournament() {
    // Creation des objets joueurs
    vector<player> players = createPlayers(NAMESPATH);
    // Creation des equipes
    vector<team> teams = createTeams(players);

    cout << "Le tournoi va commencer !\nIl se déroulera en " << NBGAMES << " manches." << endl;
    pressEnter();

    vector<string> games = randomSort(GAMESNAME);
    for (unsigned i=0; i<NBGAMES; i++) {
        cout << "Manche n°" << i+1 << " : " << games[i] << endl;
        pressEnter();
        teams = round(teams, games[i]);
    }
}
