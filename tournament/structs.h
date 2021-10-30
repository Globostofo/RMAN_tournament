using namespace std;

struct player {
    /// Structure de base d'un participant du tournoi
    unsigned id;
    string first_name;
    string last_name;

    friend ostream& operator<<(ostream& os, const player & arg) {
        os << "["
           << arg.id
           << "] "
           << arg.first_name
           << " "
           << arg.last_name;
        return os;
    }

};

/*string strPlayer(const player & p) {
    /// Renvoie une chaine de caractere contenant l'ensemble des informations sur un joueur pour l'afficher
    return "[" +
           to_string(p.id) +
           "] " +
           p.first_name +
           " " +
           p.last_name;
}

vector<player> sortPlayersById(const vector<player> & players) {
    /// Algorithme de tri par insertion pour ranger les joueurs par ID (croissant)
    vector<player> sorted;
    player temp;
    unsigned j;
    for (unsigned i=0; i<players.size(); i++) {
        j = i;
        sorted.push_back(players[i]);
        while (j > 0 && sorted[j].id < sorted[j-1].id) {
            temp = sorted[j-1];
            sorted[j-1] = sorted[j];
            sorted[j] = temp;
            j--;
        }
    }
    return sorted;
}*/

struct team {
    /// Strucutre de base d'une equipe
    unsigned id;
    string name;
    unsigned points=0;
    vector<player> players;

    /*friend ostream& operator<<(ostream& os, const player & arg) {
        os << "[" << arg.id << "] " << arg.first_name << " " << arg.last_name;
    }*/

    //bool operator==
};

/*string strTeam(const team & t) {
    /// Renvoie une chaine de caractere contenant l'ensemble des informations sur une equipe pour l'afficher
    string output = "[" +
                    to_string(t.id) +
                    "] " +
                    t.name +
                    " (" +
                    to_string(t.points) +
                    " pts) :";
    for (unsigned i=0; i<t.players.size(); i++) {
        output += "\n  - " + strPlayer(t.players[i]);
    }
    return output;
}

vector<team> sortTeamsByPoints(const vector<team> & teams) {
    /// Algorithme de tri par insertion pour ranger les equipes par nombre de points (decroissant) puis par ID en cas d'egalite (croissant)
    vector<team> sorted;
    team temp;
    unsigned j;
    for (unsigned i=0; i<teams.size(); i++) {
        j = i;
        sorted.push_back(teams[i]);
        while (j > 0 && (sorted[j].points > sorted[j-1].points || (sorted[j].points == sorted[j-1].points && sorted[j].id < sorted[j-1].id))) {
            temp = sorted[j-1];
            sorted[j-1] = sorted[j];
            sorted[j] = temp;
            j--;
        }
    }
    return sorted;
}*/
