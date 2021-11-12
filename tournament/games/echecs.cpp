#include <vector>
#include <iostream>
#include "../global.hpp"

using namespace std;
using namespace global_const;
using namespace global_func;

struct piece {
    char type;
    char color;
};

void dispChessboard(const vector<piece> & chessboard, const bool & reversed=false) {

    auto dispCell = [](const vector<piece> & chessboard, const unsigned & index, bool & posColor) {
        piece p = chessboard[index];
        string cell = "1m" + string (1, p.type) + " \033[0m";
        if (posColor) {
            cell = "43;" + cell;
        } else {
            cell = "41;" + cell;
        }
        if (p.color == 'w') {
            cell = "37;" + cell;
        } else if (p.color == 'b') {
            cell = "30;" + cell;
        }
        cell = "\033[" + cell;
        cout << cell;
        posColor = !posColor;
    };

    bool posColor = true;
    string colName;
    if (!reversed) {
        colName = "  a b c d e f g h";
        cout << colName << endl;
        for (unsigned line=8; line>=1; line--) {
            cout << line << " ";
            for (unsigned col=1; col<=8; col++) {
                dispCell(chessboard, 8*(line-1)+col-1, posColor);
            }
            cout << " " << line << endl;
            posColor = !posColor;
        }
    } else {
        colName = "  h g f e d c b a";
        cout << colName << endl;
        for (unsigned line=1; line<=8; line++) {
            cout << line << " ";
            for (unsigned col=8; col>=1; col--) {
                dispCell(chessboard, 8*(line-1)+col-1, posColor);
            }
            cout << " " << line << endl;
            posColor = !posColor;
        }
    }
    cout << colName << endl;
}

vector<piece> createChessboard() {
    vector<piece> board;

    auto pushPiecesLine = [](vector<piece> & board, const char & c) {
        board.push_back(piece {'T', c});
        board.push_back(piece {'C', c});
        board.push_back(piece {'F', c});
        board.push_back(piece {'D', c});
        board.push_back(piece {'R', c});
        board.push_back(piece {'F', c});
        board.push_back(piece {'C', c});
        board.push_back(piece {'T', c});
        return board;
    };

    auto pushPawnsLine = [](vector<piece> & board, const char & c) {
        for (char i=0; i<8; i++) {
            board.push_back(piece {'P', c});
        }
        return board;
    };

    board = pushPiecesLine(board, 'w');
    board = pushPawnsLine(board, 'w');
    for (unsigned i=0; i<(4*8); i++) {
        board.push_back(piece {' ', ' '});
    }
    board = pushPawnsLine(board, 'b');
    board = pushPiecesLine(board, 'b');

    return board;
}

vector<unsigned> getIndexWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & type, const char & color) {
    vector<unsigned> possibilities;
    if (type=='P') {
        if (color=='w') {
            if (chessboard[index-8].type=='P')
                return index-8;
            else if (16 <= index && index <= 23 && chessboard[index-16].type=='P')
                return index-16;
        } else if (color=='b') {
            if (chessboard[index+8].type=='P')
                return index+8;
            else if (48 <= index && index <= 55 && chessboard[index+16].type=='P')
                return index+16;
        }
    }
    else if (type=='C') {
        vector<int> toCheck = {-17, -15, -10, -6, 6, 10, 15, 17};
        for (const int & value : toCheck) {
            if (chessboard[index-value].type=='C') {
                possibilities.push_back(index-value);
            }
        }
    }
    else if (type=='F') {

    }
    else if (type=='T') {

    }
    else if (type=='D') {

    }
    else if (type=='R') {

    }
    return possibilities;
}

unsigned checkEndGame(const vector<piece> & chessboard) {
    return 0;
}

unsigned echecs(const string & t1, const string & t2) {

    vector<string> teams;
    if (rand()%2 == 0) {
        teams = {t1, t2};
    } else {
        teams = {t2, t1};
    }
    vector<string> colors = {"blancs", "noirs"};
    bool turn = false;
    cout << "L'equipe " << teams[0] << " joue avec les blancs." << endl
         << "L'equipe " << teams[1] << " joue avec les noirs." << endl;
    pressEnter();

    cout << "Pour un gameplay plus agreable, vous pouvez modifier les couleurs par defaut du terminal pour les faire correspondre aux couleurs classiques d'un echiquier :" << endl
         << "Pieces blanches : #FFF" << endl
         << "Cases blanches  : #E0C18C" << endl
         << "Pieces noires   : #000" << endl
         << "Cases noires    : #B07242" << endl;
    pressEnter();

    // Creation des pieces
    vector<piece> chessboard = createChessboard();

    while (checkEndGame(chessboard) == 0) {
        dispChessboard(chessboard, turn);
        cout << endl << "Trait aux " << colors[turn] << endl
             << "Equipe " << teams[turn] << ", à vous de jouer !" << endl;

        bool correctInput = false;
        string answer;
        while (!correctInput) {
            answer = ask4UInput("Le coup s'écrit sous la forme <init><colonne><ligne> (ex: Pe4) :\n");
            char color;
            if (!turn) color = 'w';
            else color = 'b';
            if (answer.size() == 3) {
                char type = answer[0];
                unsigned arrIndex = 8*(answer[2]-'0'-1) + answer[1]-'a';
                unsigned depIndex = getIndexWhoCanGoThere(chessboard, arrIndex, type, color);
                if (chessboard[depIndex].type == type) {
                    if (chessboard[depIndex].color == color) {
                        chessboard[arrIndex] = chessboard[depIndex];
                        chessboard[depIndex] = piece {' ', ' '};
                        correctInput = true;
                    } else {
                        cout << "Cette piece n'est pas de la bonne couleur" << endl;
                    }
                } else {
                    cout << "La case de depart ne correspond pas a la piece renseignee" << endl;
                }
                cout << endl;
            } else {
                cout << inputErrMsg << endl;
            }
        }

        turn = !turn;
    }

    return turn;
}
