#include <vector>
#include <iostream>
#include <algorithm>
#include "../global.hpp"

using namespace std;
using namespace global_const;
using namespace global_func;

struct piece {
    char type;
    char color;
};

void displayChessboard(const vector<piece> & chessboard, const bool & reversed=false) {

    auto dispCell = [](const vector<piece> & chessboard, const short & index, bool & posColor) {
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
        for (short line=8; line>=1; line--) {
            cout << line << " ";
            for (short col=1; col<=8; col++) {
                dispCell(chessboard, 8*(line-1)+col-1, posColor);
            }
            cout << " " << line << endl;
            posColor = !posColor;
        }
    } else {
        colName = "  h g f e d c b a";
        cout << colName << endl;
        for (short line=1; line<=8; line++) {
            cout << line << " ";
            for (short col=8; col>=1; col--) {
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
        board.push_back(piece{'T', c});
        board.push_back(piece{'C', c});
        board.push_back(piece{'F', c});
        board.push_back(piece{'D', c});
        board.push_back(piece{'R', c});
        board.push_back(piece{'F', c});
        board.push_back(piece{'C', c});
        board.push_back(piece{'T', c});
        return board;
    };

    auto pushPawnsLine = [](vector<piece> & board, const char & c) {
        for (char i=0; i<8; i++) {
            board.push_back(piece{'P', c});
        }
        return board;
    };

    board = pushPiecesLine(board, 'w');
    board = pushPawnsLine(board, 'w');
    for (short i=0; i<(4*8); i++) {
        board.push_back(piece{' ', ' '});
    }
    board = pushPawnsLine(board, 'b');
    board = pushPiecesLine(board, 'b');

    return board;
}

vector<short> getPiecesIndexes(const vector<piece> & chessboard, const char & type, const char & color) {
    vector<short> indexes;
    for (short i=0; i<(short)chessboard.size(); ++i) {
        if (chessboard[i].type == type && chessboard[i].color == color)
            indexes.push_back(i);
    }
    return indexes;
}

vector<short> getKingRange(const short & index) {
    vector<short> inRange;
    if (index%8 > 0) {
        if (index-9 >= 0) inRange.push_back(-9);
        inRange.push_back(-1);
        if (index+7 <= 63) inRange.push_back(7);
    }
    if (index-8>=0) inRange.push_back(-8);
    if (index+8<=63) inRange.push_back(8);
    if (index%8 < 7) {
        if (index-7 >= 0) inRange.push_back(-7);
        inRange.push_back(1);
        if (index+9 <= 63) inRange.push_back(9);
    }
    return inRange;
}

vector<short> getPossibilitiesByDirection(const vector<piece> & chessboard, const short & index, const char & color, const vector<short> & directions) {
    vector<short> possibilities;
    short curr_loc;
    for (const short & direction : directions) {
        curr_loc = index + direction;
        while (chessboard[curr_loc].color!=color && curr_loc>=0 && curr_loc<=63) {
            possibilities.push_back(curr_loc);
            if (chessboard[curr_loc].color!=' ' || curr_loc%8==0 || curr_loc%8==7) break;
            curr_loc += direction;
        }
    }
    return possibilities;
}

vector<short> getPawnMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;
    if (c == 'w') {
        if (chessboard[index+8].type == ' ') {
            possibilities.push_back(index+8);
            if (8<=index && index<=15 && chessboard[index+16].type==' ')
                possibilities.push_back(index+16);
        }
        if (index%8!=0 && chessboard[index+7].color=='b') possibilities.push_back(index+7);
        if (index%8!=7 && chessboard[index+9].color=='b') possibilities.push_back(index+9);
    }

    else if (c == 'b') {
        if (chessboard[index-8].type == ' ') {
            possibilities.push_back(index-8);
            if (48<=index && index<=55 && chessboard[index-16].type==' ')
                possibilities.push_back(index-16);
        }
        if (index%8!=0 && chessboard[index-9].color=='w') possibilities.push_back(index-9);
        if (index%8!=7 && chessboard[index-7].color=='w') possibilities.push_back(index-7);
    }

    return possibilities;
}

vector<short> getKnightMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    vector<short> toCheck;
    if (index%8 > 0) {
        if (index-17 >= 0) toCheck.push_back(-17);
        if (index+15 <= 63) toCheck.push_back(15);
    }
    if (index%8 > 1) {
        if (index-10 >= 0) toCheck.push_back(-10);
        if (index+6 <= 63) toCheck.push_back(6);
    }
    if (index%8 < 7) {
        if (index-15 >= 0) toCheck.push_back(-15);
        if (index+17 <= 63) toCheck.push_back(17);
    }
    if (index%8 < 6) {
        if (index-6 >= 0) toCheck.push_back(-6);
        if (index+10 <= 63) toCheck.push_back(10);
    }

    for (const short & value : toCheck) {
        if (chessboard[index+value].color != c)
            possibilities.push_back(index+value);
    }

    return possibilities;
}

vector<short> getBishopMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    for (const short & p : getPossibilitiesByDirection(chessboard, index, c, {-9, -7, 7, 9})) {
        possibilities.push_back(p);
    }

    return possibilities;
}

vector<short> getRookMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    for (const short & p : getPossibilitiesByDirection(chessboard, index, c, {-8, -1, 1, 8})) {
        possibilities.push_back(p);
    }

    return possibilities;
}

vector<short> getQueenMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    for (const short & p : getPossibilitiesByDirection(chessboard, index, c, {-9, -8, -7, -1, 1, 7, 8, 9})) {
        possibilities.push_back(p);
    }

    return possibilities;
}

bool isAttacked(const vector<piece> & chessboard, const short & index, const char & color) {
    /// Fonction qui verifie si la case d'indice <index> est attaquee par une piece de couleur <color>
    for (const short & pawnI   : getPiecesIndexes(chessboard, 'P', color))
        for (const short & moveI : getPawnMoves  (chessboard, pawnI,   color)) if (moveI == index) return true;
    for (const short & knightI : getPiecesIndexes(chessboard, 'C', color))
        for (const short & moveI : getKnightMoves(chessboard, knightI, color)) if (moveI == index) return true;
    for (const short & bishopI : getPiecesIndexes(chessboard, 'F', color))
        for (const short & moveI : getBishopMoves(chessboard, bishopI, color)) if (moveI == index) return true;
    for (const short & rookI   : getPiecesIndexes(chessboard, 'T', color))
        for (const short & moveI : getRookMoves  (chessboard, rookI,   color)) if (moveI == index) return true;
    for (const short & queenI  : getPiecesIndexes(chessboard, 'D', color))
        for (const short & moveI : getQueenMoves (chessboard, queenI,  color)) if (moveI == index) return true;
    for (const short & moveI : getKingRange(getPiecesIndexes(chessboard, 'R', color)[0]))
        if (moveI == index) return true;

    return false;
}

vector<short> getKingMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    vector<short> toCheck = getKingRange(index);

    char enemyC = 'w';
    if (c == 'w') enemyC = 'b';

    for (const short & value : toCheck) {
        if (chessboard[index+value].color!=c && !isAttacked(chessboard, index+value, enemyC))
            possibilities.push_back(index+value);}

    return possibilities;
}

vector<short> getPieceMoves(const vector<piece> & chessboard, const short & index) {
    char t = chessboard[index].type;
    char c = chessboard[index].color;

    if      (t == 'P') return getPawnMoves(chessboard, index, c);
    else if (t == 'C') return getKnightMoves(chessboard, index, c);
    else if (t == 'F') return getBishopMoves(chessboard, index, c);
    else if (t == 'T') return getRookMoves(chessboard, index, c);
    else if (t == 'D') return getQueenMoves(chessboard, index, c);
    else if (t == 'R') return getKingMoves(chessboard, index, c);
}

bool isMat(const vector<piece> & chessboard, const char & color, const char & enemyColor) {
    /// Fonction qui verifie si l'equipe <color> a perdu la partie
    short kingIndex = getPiecesIndexes(chessboard, 'R', color)[0];

    if (!isAttacked(chessboard, color, enemyColor))
        // Si le roi n'est pas en echec
        return false;

    if (getPieceMoves(chessboard, kingIndex).size())
        // Si le roi peut bouger
        return false;

    return false;
}

bool isDraw(const vector<piece> & chessboard, const char & color, const char & enemyColor) {
    /// Fonction qui verifie s'il y a egalite

    auto getRemainingPieces = [](const vector<piece> & chessboard, const char & color) {
        string pieces;
        for (const piece & p : chessboard)
            if (p.color == color) pieces += p.type;
        sort(pieces.begin(), pieces.end());
        return pieces;
    };

    string wPieces = getRemainingPieces(chessboard, 'w');
    string bPieces = getRemainingPieces(chessboard, 'b');
    if ((wPieces=="R" && (bPieces=="R" || bPieces=="CR" || bPieces=="FR")) ||
        (bPieces=="R" && (wPieces=="CR" || wPieces=="FR"))) return true;



    return false;
}

short echecs(const string & t1, const string & t2) {

    // Choix aleatoire des couleurs
    vector<string> teams = {t1, t2};
    if (rand()%2 == 0) teams = {t2, t1};
    vector<string> colors = {"blancs", "noirs"};
    bool turn = false;
    cout << "L'equipe " << teams[0] << " joue avec les blancs." << endl
         << "L'equipe " << teams[1] << " joue avec les noirs." << endl;
    pressEnter();

    cout << "Pour un gameplay plus agreable dans la console, vous pouvez modifier les couleurs par defaut du terminal pour les faire correspondre aux couleurs classiques d'un echiquier :" << endl
         << "Pieces blanches : #FFF" << endl
         << "Cases blanches  : #E0C18C" << endl
         << "Pieces noires   : #000" << endl
         << "Cases noires    : #B07242" << endl;
    pressEnter();

    // Creation des pieces
    vector<piece> chessboard = createChessboard();

    // Boucle principale du jeu
    while (true) {
        // Affichage des instructions
        displayChessboard(chessboard, turn);
        cout << endl << "Trait aux " << colors[turn] << endl
             << "Equipe " << teams[turn] << ", a vous de jouer !" << endl;

        // Gestion de l'entree utilisateur
        bool correctInput = false;
        string answer;
        char color='w', enemyColor='b';
        if (turn) color = 'b', enemyColor='w';
        while (!correctInput) {

            // Demande d'un coup a l'utilisateur
            answer = ask4UInput("Le coup s'ecrit sous la forme <col_dep><lin_dep> <col_arr><lin_arr> (ex e2 e4) :\n");

            if (answer.size() == 2) {           // Sous la forme <col><ligne>
                short index = 8*(answer[1]-'0'-1) + answer[0]-'a';
                if (chessboard[index].color!=color) {
                    cout << inputErrMsg << endl << endl;
                    continue;
                }
                vector<short> p = getPieceMoves(chessboard, index);
                cout << p.size() << endl;
                for (const short & i : p)
                    cout << i << endl;
            }

            else if (answer.size() == 5) {      // Sous la forme <col_dep><lin_dep> <col_arr><lin_arr>
                short depIndex = 8*(answer[1]-'0'-1) + answer[0]-'a';
                short arrIndex = 8*(answer[4]-'0'-1) + answer[3]-'a';

                if (chessboard[depIndex].color!=color) {
                    cout << inputErrMsg << endl << endl;
                    continue;
                }

                for (const short & index : getPieceMoves(chessboard, depIndex))
                    if (index == arrIndex) {
                        chessboard[arrIndex] = chessboard[depIndex];
                        chessboard[depIndex] = piece {' ', ' '};
                        correctInput = ! correctInput;
                    }
            }

            else
                cout << inputErrMsg << endl << endl;
        }

        // Verification de mat et de pat
        if (isMat(chessboard, enemyColor, color)) {
            cout << "Echec et mat !" << endl
                 << "L'equipe " << teams[turn] << "gagne la partie et encaisse 2 points" << endl;
            return turn;
        } else if (isDraw(chessboard, enemyColor, color)) {
            cout << "Pat !" << endl
                 << "Les equipes font egalite et encaissent 1 point chaucune" << endl;
        }

        turn = !turn;
    }
}
