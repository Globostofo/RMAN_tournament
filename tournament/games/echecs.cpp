#include <vector>
#include <iostream>
#include "../global.hpp"

using namespace std;
using namespace global_func;

struct pos {
    char column;
    unsigned line;
};

struct piece {
    char type;
    char color;
    pos position;
};

char getPieceTypeByCoords(const char & c, const unsigned & l, const vector<piece> & pieces) {
    for(const piece & p : pieces) {
        if (p.position.column == c && p.position.line == l)
            return p.type;
    }
    return ' ';
}

void dispChessboard(const vector<piece> & pieces) {
    vector<vector<string>> content = {{" "}};

    for (unsigned i=0; i<8; i++) {
        content[0].push_back(to_string(8-i));
        content.push_back({string (1,'a'+i)});
    }

    for (char column='a'; column<='h'; column++) {
        for (unsigned line=1; line<=8; line++) {
            char pieceName = getPieceTypeByCoords(column, line, pieces);
            content[column-'a'+1].push_back(string (1,pieceName));
        }
    }

    cuteLilBoard(content);
}

vector<piece> startPieces() {
    vector<piece> pieces;

    vector<char> colorsChar = {'w', 'b'};
    unsigned piL=1, paL=2;
    for (unsigned i=0; i<2; i++) {
        pieces.push_back(piece {'T', colorsChar[i], pos {'a', piL}});
        pieces.push_back(piece {'C', colorsChar[i], pos {'b', piL}});
        pieces.push_back(piece {'F', colorsChar[i], pos {'c', piL}});
        pieces.push_back(piece {'D', colorsChar[i], pos {'d', piL}});
        pieces.push_back(piece {'R', colorsChar[i], pos {'e', piL}});
        pieces.push_back(piece {'F', colorsChar[i], pos {'f', piL}});
        pieces.push_back(piece {'C', colorsChar[i], pos {'g', piL}});
        pieces.push_back(piece {'T', colorsChar[i], pos {'h', piL}});
        for (char j='a'; j<='h'; j++) {
            pieces.push_back(piece {'P', colorsChar[i], pos {j, paL}});
        }
        piL=8, paL=7;
    }

    return pieces;
}

unsigned echecs(const string & t1, const string & t2) {

    vector<string> teams = {t1, t2};
    unsigned turn = rand()%2;
    cout << "L'equipe " << teams[turn] << " joue avec les blancs." << endl
         << "L'equipe " << teams[(turn+1)%2] << " joue avec les noirs." << endl;
    pressEnter();

    // Creation des pieces
    vector<piece> pieces = startPieces();

    dispChessboard(pieces);

    return turn;
}
