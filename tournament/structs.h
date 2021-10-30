#include <ostream>
#include <vector>

using namespace std;

struct player {
    /// Structure de base d'un participant du tournoi
    unsigned id;
    string first_name;
    string last_name;

    friend ostream& operator<<(ostream& os, const player & p) {
        os << "["
           << p.id
           << "] "
           << p.first_name
           << " "
           << p.last_name;
        return os;
    }
};

struct team {
    /// Strucutre de base d'une equipe
    unsigned id;
    string name;
    unsigned points=0;
    vector<player> players;

    friend ostream& operator<<(ostream& os, const team & t) {
        os << "[" << t.id << "] " << t.name << " (" << t.points << " pts) :";
        for (unsigned i=0; i<t.players.size(); i++) {
            os << "\n  - " << t.players[i];
        }
        return os;
    }
};
