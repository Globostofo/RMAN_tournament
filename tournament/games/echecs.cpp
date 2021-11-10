#include <vector>
#include <iostream>
#include "../global.hpp"

using namespace std;
using namespace global_func;

struct piece {
    char type;
    char color;
    char column;
    unsigned line;
};

char getPieceTypeByCoords(const char & c, const unsigned & l, const vector<piece> & pieces) {
    for(const piece & p : pieces) {
        if (p.column == c && p.line == l)
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
        pieces.push_back(piece {'T', colorsChar[i], 'a', piL});
        pieces.push_back(piece {'C', colorsChar[i], 'b', piL});
        pieces.push_back(piece {'F', colorsChar[i], 'c', piL});
        pieces.push_back(piece {'D', colorsChar[i], 'd', piL});
        pieces.push_back(piece {'R', colorsChar[i], 'e', piL});
        pieces.push_back(piece {'F', colorsChar[i], 'f', piL});
        pieces.push_back(piece {'C', colorsChar[i], 'g', piL});
        pieces.push_back(piece {'T', colorsChar[i], 'h', piL});
        for (char j='a'; j<='h'; j++) {
            pieces.push_back(piece {'P', colorsChar[i], j, paL});
        }
        piL=8, paL=7;
    }

    return pieces;
}

unsigned echecs(const string & t1, const string & t2) {

    vector<string> teams = {t1, t2};
    unsigned turn = rand()%2;
    cout << "L'equipe " << teams[turn] << " joue les blancs" << endl
         << "L'equipe " << teams[(turn+1)%2] << " joue les noirs" << endl;
    pressEnter();
    
    // Creation des pieces
    vector<piece> pieces = startPieces();
    
    dispChessboard(pieces);

    return turn;
}

int main() {
    echecs("equpe1", "equipe2");
    return 1;
}