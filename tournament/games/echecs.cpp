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
    for (unsigned i=0; i<(4*8); i++) {
        board.push_back(piece{' ', ' '});
    }
    board = pushPawnsLine(board, 'b');
    board = pushPiecesLine(board, 'b');

    return board;
}

vector<unsigned> getPiecesIndexes(const vector<piece> & chessboard, const char & type, const char & color) {
    vector<unsigned> indexes;
    for (unsigned i=0; i<chessboard.size(); ++i) {
        if (chessboard[i].type == type && chessboard[i].color == color)
            indexes.push_back(i);
    }
    return indexes;
}

vector<unsigned> getPawnsIndexesWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & color) {
    // Cherche le(s) pion(s) de couleur <color> qui peut(peuvent) aller sur la case d'indice <index>
    vector<unsigned> possibilities;

    if (color=='w') {                                                                                           // Si la piece recherchee doit etre blanche
        if (chessboard[index].type==' ') {                                                                          // Si la case d'indice <index> est vide
            if (chessboard[index-8].type=='P' && chessboard[index-8].color=='w') possibilities.push_back(index-8);      // Si la case du dessous contient un pion blanc
            else if (24 <= index && index <= 31 && chessboard[index-16].type=='P' && chessboard[index-16].color=='w')   // Sinon si la case encore en dessous est sur la ligne 2 et qu'elle contient un pion blanc
                possibilities.push_back(index-16);
        } else if (chessboard[index].color=='b') {                                                                  // Si la case d'indice <index> contient une piece noire
            if (chessboard[index-9].type=='P' && chessboard[index-9].color=='w') possibilities.push_back(index-9);      // Si la case en dessous a gauche est un pion blanc
            if (chessboard[index-7].type=='P' && chessboard[index-7].color=='w') possibilities.push_back(index-7);      // Si la case en dessous a droite est un pion blanc
        }

    } else if (color=='b') {                                                                                    // Sinon si la piece recherchee doit etre noire
        if (chessboard[index].type==' ') {                                                                         // Si la case d'indice <index> est vide
            if (chessboard[index+8].type=='P' && chessboard[index+8].color=='b') possibilities.push_back(index+8);      // Si la case du dessus contient un pion noir
            else if (32 <= index && index <= 47 && chessboard[index+16].type=='P' && chessboard[index+16].color=='b')   // Sinon si la case encore au dessus est sur la ligne 7 et qu'elle contient un pion noir
                possibilities.push_back(index+16);
        } else if (chessboard[index].color=='w') {                                                                  // Si la case d'indice <index> contient une piece blanche
            if (chessboard[index+7].type=='P' && chessboard[index+7].color=='b') possibilities.push_back(index+7);      // Si la case au dessus a gauche est un pion noir
            if (chessboard[index+9].type=='P' && chessboard[index+9].color=='b') possibilities.push_back(index+9);      // Si la case au dessus a droite est un pion noir
        }
    }

    return possibilities;
}

vector<unsigned> getKnightsIndexesWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & color) {
    // Cherche le(s) cavalier(s) de couleur <color> qui peut(peuvent) aller sur la case d'indice <index>
    vector<unsigned> possibilities;

    vector<short> toCheck;
    if (index%8 != 0) {
        if ((int) index-17 >= 0) toCheck.push_back(-17);
        if (index+15 <= 63) toCheck.push_back(15);
    }
    if (index%8 > 1) {
        if ((int) index-10 >= 0) toCheck.push_back(-10);
        if (index+6 <= 63) toCheck.push_back(6);
    }
    if (index%8 != 7) {
        if ((int) index-15 >= 0) toCheck.push_back(-15);
        if (index+17 <= 63) toCheck.push_back(17);
    }
    if (index%8 < 6) {
        if ((int) index-6 >= 0) toCheck.push_back(-6);
        if (index+10 <= 63) toCheck.push_back(10);
    }

    for (const short & value : toCheck) {                                                                         // Pour chaque case <c> qui rend accessible la case d'indice <index> a un cavalier de couleur <color>
        if (chessboard[index+value].type=='C' && chessboard[index+value].color==color)                              // Si <c> contient un cavalier de couleur <color>
            possibilities.push_back(index+value);
    }

    return possibilities;
}

vector<unsigned> getBishopsIndexesWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & color) {
    // Cherche le fou de couleur <color> qui peut aller sur la case d'indice <index>
    vector<unsigned> possibilities;

    for (int i=index-9; i>=0; i-=9) {                                                                             // Pour chaque case <c> en diagonale bas-gauche de la case d'indice <index>
        if (chessboard[i].type=='F' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index-7; i>=0; i-=7) {                                                                        // Pour chaque case <c> en diagonale bas-droite de la case d'indice <index>
        if (chessboard[i].type=='F' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index+7; i<=63; i+=7) {                                                                       // Pour chaque case <c> en diagonale haut-gauche de la case d'indice <index>
        if (chessboard[i].type=='F' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index+9; i<=63; i+=9) {                                                                            // Pour chaque case <c> en diagonale haut-droite de la case d'indice <index>
        if (chessboard[i].type=='F' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }

    return possibilities;
}

vector<unsigned> getRooksIndexesWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & color) {
    // Cherche la(les) tour(s) de couleur <color> qui peut(peuvent) aller sur la case d'indice <index>
    vector<unsigned> possibilities;

    for (int i=index-8; i>=0; i-=8) {                                                                             // Pour chaque case <c> en dessous de la case d'indice <index>
        if (chessboard[i].type=='T' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (unsigned i=index-1; i>=index-index%8; i--) {                                                             // Pour chaque case <c> a gauche de la case d'indice <index>
        if (chessboard[i].type=='T' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (unsigned i=index+1; i<=index+(7-index%8); i++) {                                                         // Pour chaque case <c> a droite de la case d'indice <index>
        if (chessboard[i].type=='T' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index+8; i<=63; i+=8) {                                                                            // Pour chaque case <c> au dessus de la case d'indice <index>
        if (chessboard[i].type=='T' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }

    return possibilities;
}

vector<unsigned> getQueensIndexesWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & color) {
    // Cherche la(les) dame(s) de couleur <color> qui peut(peuvent) aller sur la case d'indice <index>
    vector<unsigned> possibilities;

    for (int i=index-9; i>=0; i-=9) {                                                                             // Pour chaque case <c> en diagonale bas-gauche de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index-8; i>=0; i-=8) {                                                                             // Pour chaque case <c> en dessous de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index-7; i>=0; i-=7) {                                                                        // Pour chaque case <c> en diagonale bas-droite de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (unsigned i=index-1; i>=index-index%8; i--) {                                                             // Pour chaque case <c> a gauche de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (unsigned i=index+1; i<=index+(7-index%8); i++) {                                                         // Pour chaque case <c> a droite de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index+7; i<=63; i+=7) {                                                                       // Pour chaque case <c> en diagonale haut-gauche de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index+8; i<=63; i+=8) {                                                                            // Pour chaque case <c> au dessus de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient une tour de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }
    for (int i=index+9; i<=63; i+=9) {                                                                            // Pour chaque case <c> en diagonale haut-droite de la case d'indice <index>
        if (chessboard[i].type=='D' && chessboard[i].color==color) possibilities.push_back(i);                      // Si <c> contient un fou de couleur <color>
        else if (chessboard[i].type!=' ') break;                                                                    // Sinon si <c> n'est pas vide
    }

    return possibilities;
}

vector<unsigned> getKingIndexeWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & color) {
    // Cherche si le roi de couleur <color> peut aller sur la case d'indice <index>
    vector<unsigned> possibilities;

    vector<short> toCheck;
    if (index%8 != 0) {
        if ((int) index-9 >= 0) toCheck.push_back(-9);
        toCheck.push_back(-1);
        if (index+7 <= 63) toCheck.push_back(7);
    }
    if ((int) index-8 >= 0) toCheck.push_back(-8);
    if (index+8 <= 63) toCheck.push_back(8);
    if (index%8 != 7) {
        if ((int) index-7 >= 0) toCheck.push_back(-7);
        toCheck.push_back(1);
        if (index+9 <= 63) toCheck.push_back(9);
    }

    for (const short & value : toCheck) {                                                                         // Pour chaque case <c> qui rend accessible la case d'indice <index> au roi de couleur <color>
        if (chessboard[index+value].type=='R' && chessboard[index+value].color==color)                              // Si <c> contient le roi de couleur <color>
            possibilities.push_back(index-value);
    }

    return possibilities;
}

vector<unsigned> getIndexOfTypeWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & type, const char & color) {
    if (type=='P')
        return getPawnsIndexesWhoCanGoThere(chessboard, index, color);
    else if (type=='C')
        return getKnightsIndexesWhoCanGoThere(chessboard, index, color);
    else if (type=='F')
        return getBishopsIndexesWhoCanGoThere(chessboard, index, color);
    else if (type=='T')
        return getRooksIndexesWhoCanGoThere(chessboard, index, color);
    else if (type=='D')
        return getQueensIndexesWhoCanGoThere(chessboard, index, color);
    else if (type=='R')
        return getKingIndexeWhoCanGoThere(chessboard, index, color);
}

vector<unsigned> getIndexWhoCanGoThere(const vector<piece> & chessboard, const unsigned & index, const char & color) {
    vector<unsigned> possibilities;
    for (const unsigned & value : getPawnsIndexesWhoCanGoThere(chessboard, index, color)) possibilities.push_back(value);
    for (const unsigned & value : getKnightsIndexesWhoCanGoThere(chessboard, index, color)) possibilities.push_back(value);
    for (const unsigned & value : getBishopsIndexesWhoCanGoThere(chessboard, index, color)) possibilities.push_back(value);
    for (const unsigned & value : getRooksIndexesWhoCanGoThere(chessboard, index, color)) possibilities.push_back(value);
    for (const unsigned & value : getQueensIndexesWhoCanGoThere(chessboard, index, color)) possibilities.push_back(value);
    for (const unsigned & value : getKingIndexeWhoCanGoThere(chessboard, index, color)) possibilities.push_back(value);
    return possibilities;
}

bool isInCheck(const vector<piece> & chessboard, const char & color) {
    /// Fonction qui verifie si le roi <color> est en echec
    unsigned kingIndex = getPiecesIndexes(chessboard, 'R', color)[0];
    char enemyColor = 'w';
    if (color == 'w') enemyColor = 'b';
    int temp = getIndexWhoCanGoThere(chessboard, kingIndex, enemyColor).size();
    cout << temp << endl;
    return temp;
}

bool isMat(const vector<piece> & chessboard, const char & color) {
    /// Fonction qui verifie si l'equipe <color> a perdu la partie
    return false;
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

    while (true) {
        // Affichage des instructions
        dispChessboard(chessboard, turn);
        cout << endl << "Trait aux " << colors[turn] << endl
             << "Equipe " << teams[turn] << ", a vous de jouer !" << endl;

        // Gestion de l'entree utilisateur
        bool correctInput = false;
        string answer;
        while (!correctInput) {

            // Demande d'un coup a l'utilisateur
            answer = ask4UInput("Le coup s'écrit sous la forme <init><colonne><ligne> (ex: Pe4) :\n");
            char color;
            if (!turn) color = 'w';
            else color = 'b';

            if (answer.size() == 3) {           // Sous la forme <init><col><ligne>
                char type = answer[0];
                unsigned arrIndex = 8*(answer[2]-'0'-1) + answer[1]-'a';
                vector<unsigned> depIndex = getIndexOfTypeWhoCanGoThere(chessboard, arrIndex, type, color);

                if (depIndex.size() == 0) {         // Pas de possibilite
                    cout << "Erreur dans la saisie, aucune piece ne peut atteindre la case selectionnee" << endl;
                }

                else if (depIndex.size() == 1) {    // Une possibilite

                    // On place temporairement la piece a la nouvelle place pour verifier si le coup met en echec
                    chessboard[arrIndex] = chessboard[depIndex[0]];
                    chessboard[depIndex[0]] = piece {' ', ' '};

                    if (!isInCheck(chessboard, color))
                        // On valide le coup
                        correctInput = !correctInput;
                    else {
                        // On annule le coup
                        chessboard[depIndex[0]] = chessboard[arrIndex];
                        chessboard[arrIndex] = piece {' ', ' '};
                        cout << "Vous etes en echec" << endl;
                    }
                }

                else {                              // Trop de possibilites (demande de precision)
                    cout << "Plusieurs pieces peuvent atteindre cette case, veuillez etre plus precis en utilisant la forme <init><depart><arrivee> (ex: <init><col_d><lin_d><col_a><lin_a>)" << endl;
                }
                cout << endl;
            }

            else if (answer.size() == 5) {      // Sous la forme <init><col_d><lin_d><col_a><lin_a>
                char type = answer[0];
                unsigned depIndex = 8*(answer[2]-'0'-1) + answer[1]-'a';
                unsigned arrIndex = 8*(answer[4]-'0'-1) + answer[3]-'a';

                for (const unsigned & index : getIndexOfTypeWhoCanGoThere(chessboard, arrIndex, type, color))
                    if (index == depIndex) {

                        // On place temporairement la piece a la nouvelle place pour verifier su le coup met en echec
                        chessboard[arrIndex] = chessboard[depIndex];
                        chessboard[depIndex] = piece {' ', ' '};

                        if (!isInCheck(chessboard, color))
                            // On valide le coup
                            correctInput = ! correctInput;
                        else {
                            // On annule le coup
                            chessboard[depIndex] = chessboard[arrIndex];
                            chessboard[arrIndex] = piece {' ', ' '};
                            cout << "Vous etes en echec" << endl;
                        }

                        break;
                    }
            }

            else {
                cout << inputErrMsg << endl;
            }
        }

        turn = !turn;
    }

    return turn;
}
