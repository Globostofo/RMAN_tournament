/**
 *
 * @file    tournament.cpp
 *
 * @author  R. Clement
 *
 * @date    27/11/2021
 *
 * @brief   Gestion d'un tournoi, des equipes et des mini-jeux
 *
 **/

#include <algorithm>    // std::sort

// Importation des jeux
#include "./games/tictactoe.cpp"
#include "./games/memory.cpp"
#include "./games/connect4.cpp"
#include "./games/chess.cpp"
#include "./games/rockpaperscissors.cpp"
#include "./games/priceisright.cpp"

using namespace global_const;
using namespace global_func;

struct player {
    /// Structure de base d'un participant du tournoi
    string first_name;
    string last_name;
};

string reprPlayer(const player & p) {
    return p.first_name + " " + p.last_name;
}

bool lessThan(const player & p1, const player & p2) {
    /// Renvoie vrai si <p1> est avant <p2> dans l'ordre lexicographique (on compare les prénoms en cas de noms de famille identitiques)
    return (p1.last_name < p2.last_name) || ((p1.last_name == p2.last_name) && (p1.first_name < p2.first_name));
}

struct team {
    /// Strucutre de base d'une equipe
    string name;
    unsigned points=0;
    vector<player> players;
};

bool greaterThan(const team & t1, const team & t2) {
    /// Renvoie vrai si <t1> a plus de points que <p2> (on compare dans l'ordre lexicographique en cas d'egalite)
    return (t1.points > t2.points) || (t1.points == t2.points && t1.name < t2.name);
}

void dispBoard(const vector<team> & teams) {
    vector<vector<string>> content = {{"Rang"}, {"Equipe"}, {"Pts"}};
    for (unsigned i=0; i<teams.size(); i++) {
        content[0].push_back(to_string(i+1));
        content[1].push_back(teams[i].name);
        content[2].push_back(to_string(teams[i].points));
    }
    ofs << "Classement actuel des équipes :" << endl;
    cuteLilBoard(content, {'r', 'l', 'r'}, true);
}

void dispMatchmaking(const vector<vector<team>> board, const vector<vector<char>> points) {
    vector<vector<string>> content = {{"Match"}, {"Equipe"}, {"Pts"}, {"Pts"}, {"Equipe"}};
    for (unsigned i=0; i<board.size(); ++i) {
        content[0].push_back(to_string(i+1));
        content[1].push_back(board[i][0].name);
        content[2].push_back(string(1,points[i][0]));
        content[3].push_back(string(1,points[i][1]));
        if (board[i].size() != 1)
            content[4].push_back(board[i][1].name);
        else
            content[4].push_back("");
    }
    ofs << "Ordre des rencontres :" << endl;
    cuteLilBoard(content, {'r', 'r', 'c', 'c', 'l'}, true);
}

vector<player> createPlayers() {
    /// Fonction de création des joueurs suivant le moule de la structure

    string first_name, last_name;
    vector<player> players;

    while (true) {
        last_name = ask4UInput("Nom : ");
        if (last_name.size() == 0) break;
        first_name = ask4UInput("Prenom : ");
        player p {first_name, last_name};
        players.push_back(p);
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

    unsigned nbP = players.size();      // nombre de joueurs

    // Melange des joueurs dans leur liste
    randomSort(players);

    // Affichage des possibilites d'equipes
    ofs << endl << nbP << " joueurs participent au tournoi :" << endl;
    for (unsigned i=MIN_TEAMS; i<=MAX_TEAMS; i++)
        ofs << "  - " << i << " eq. -> " << nbP / i << " j/eq. (" << nbP % i << " j. exclus)" << endl;

    // Demande du nombre d'equipes
    unsigned nbT = stoi(ask4UInput("Nombre d'equipes : "));
    unsigned nbPbT = nbP / nbT;
    unsigned nbPe = nbP % nbT;

    // Retrait des joueurs supplementaires
    nbP = nbP - nbPe;
    vector<player> excluded;
    for (unsigned i=nbP; i<nbP+nbPe; i++)
        excluded.push_back(players[i]);
    players.resize(nbP);
    sort(excluded.begin(), excluded.end(), lessThan);
    if (nbPe != 0) {
        if (nbPe == 1)
            ofs << "\nLe joueur suivant est exclu :" << endl;
        else
            ofs << "\nLes joueurs suivants sont exclus :" << endl;
        for (unsigned i=0; i<nbPe; i++)
            ofs << "  - " << reprPlayer(excluded[i]) << endl;
    }
    pressEnter();

    // Demande des noms des equipes
    vector<team> teams;
    for (unsigned i=0; i<nbT; i++) {
        team t;
        t.name = ask4UInput("Nom de l'equipe n°" + to_string(i+1) + " : ");
        t.points = 0;
        vector<player> teamsPlayers;
        for (unsigned j=0; j<nbPbT; j++)
            teamsPlayers.push_back(players[i*nbPbT + j]);
        sort(teamsPlayers.begin(), teamsPlayers.end(), lessThan);
        t.players = teamsPlayers;
        teams.push_back(t);
        ofs << t.name << " :" << endl;

        for (const player & p : t.players)
            ofs << "  - " << reprPlayer(p) << endl;
        pressEnter();
    }

    return teams;
}

vector<vector<team>> matchmaking(const vector<team> & teams) {
    /// Fonction de répartition des équipes pour les matchs dans la liste triée des équipes
    vector<vector<team>> board;
    for (unsigned i=0; i<teams.size()/2; i++)
        board.push_back({teams[2*i], teams[2*i + 1]});
    if (teams.size() % 2 == 1)
        board.push_back({teams.back()});
    return board;
}

void round(vector<team> & teams, const string & game) {
    vector<vector<team>> board = matchmaking(teams);
    vector<vector<char>> points;
    for (unsigned short i=0; i<board.size(); ++i)
        points.push_back({' ', ' '});

    for (unsigned i=0; i<board.size(); i++) {
        dispMatchmaking(board, points);
        pressEnter();

        short winner;

        if (board[i].size() == 2) {
            string t1 = board[i][0].name;
            string t2 = board[i][1].name;
            ofs << "Rencontre n°" << i+1 << " : " << t1 << " vs " << t2 << endl;
            pressEnter();

            if (game == "memory")
                winner = memory(t1, t2);

            else if (game == "morpion")
                winner = morpion(t1, t2);

            else if (game == "puissance 4")
                winner = p4(t1, t2);

            else if (game == "echecs")
                winner = echecs(t1, t2);

            else if (game == "pierre feuille ciseaux")
                winner = pfc(t1, t2);

            else if (game == "juste prix")
                winner = justeprix(t1, t2);

            else
                // ne devrait jamais arriver
                winner = 2;

            if (winner != 2)
                ofs << "L'equipe " << board[i][winner].name << " gagne 2 points" << endl;
            else
                ofs << "Les equipent sont a egalite, elles gagnent 1 point chacune" << endl;
        }
        else {
            ofs << "L'equipe " << board[i][0].name << " est exemptee, elle gagne 1 point" << endl;
            winner = 2;
        }

        if (winner != 2) {
            board[i][winner].points += 2;
            points[i][winner] = '2';
            points[i][(winner+1)%2] = '0';
        } else
            for (unsigned short j=0; j<board[i].size(); ++j) {
                board[i][j].points++;
                points[i][j] = '1';
            }
        pressEnter();
    }

    dispMatchmaking(board, points);
    pressEnter();

    teams.resize(0);
    for (const vector<team> & vt : board)
        for (const team & t : vt)
            teams.push_back(t);
    sort(teams.begin(), teams.end(), greaterThan);
    dispBoard(teams);
    pressEnter();
}

void tournament() {
    // Creation des objets joueurs
    vector<player> players = createPlayers();

    // Creation des equipes
    vector<team> teams = createTeams(players);

    ofs << "Le tournoi va commencer !\nIl se déroulera en " << NB_GAMES << " manches." << endl;
    pressEnter();

    sort(teams.begin(), teams.end(), greaterThan);
    dispBoard(teams);
    pressEnter();

    vector<string> games = GAMES_NAME;
    randomSort(games);
    for (unsigned i=0; i<NB_GAMES; i++) {
        ofs << "Manche n°" << i+1 << " : " << games[i] << endl;
        pressEnter();
        round(teams, games[i]);
    }

    ofs << "L'equipe gagnante du tournoi est " << teams[0].name << " !!!" << endl
        << "Felicitation a tous les joueurs de l'equipe :" << endl;
    for (const player & p : teams[0].players)
        ofs << "  - " << reprPlayer(p) << endl;

}
