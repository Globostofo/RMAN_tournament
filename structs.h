#include <ostream>
#include <vector>

using namespace std;

struct player {
    /// Structure de base d'un participant du tournoi
    string first_name;
    string last_name;

    friend ostream & operator<<(ostream & os, const player & p) {
        os << p.first_name
           << " "
           << p.last_name;
        return os;
    }

    friend bool operator<(const player & lhs, const player & rhs) {
        return lhs.last_name < rhs.last_name || (lhs.last_name == rhs.last_name && lhs.first_name < rhs.first_name);
    }
};

struct team {
    /// Strucutre de base d'une equipe
    string name;
    unsigned points=0;
    vector<player> players;

    friend bool operator<(const team & lhs, const team & rhs) {
        return lhs.points > rhs.points || (lhs.points == rhs.points && lhs.name < rhs.name);
    }
};

/*struct pion {

};*/
