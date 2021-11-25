#include <vector>
#include <iostream>
#include <algorithm>
#include "../global.hpp"

using namespace std;
using namespace global_const;
using namespace global_func;

struct piece {
    /// Structure de base d'une piece de l'echiquier
    char type;      // Peut prendre pour valeur : 'P', 'C', 'F', 'T', 'D', 'R', ' ' (si la case est vide)
    char color;     // Peut prendre pour valeur : 'w' (blanc), 'b' (noir), ' ' (vide)
};

void displayChessboard(const vector<piece> & chessboard, const bool & reversed=false) {
    /// Procedure d'affichage de l'echiquier contenu dans le vecteur de pieces chessboard
    /// Le booleen reversed permet d'afficher le plateau dans l'autre sens pour avoir le point de vu de l'equipe noire

    auto dispCell = [](const vector<piece> & chessboard, const short & index, bool & posColor) {
        /// Lambda d'affichage d'une cellule avec sa couleur de fond et de piece
        piece p = chessboard[index];
        string cell = "1m" + string (1, p.type) + " \033[0m";
        if (posColor) {
            cell = "43;" + cell;        // Jaune --> cases blanches
        } else {
            cell = "41;" + cell;        // Rouge --> cases noires
        }
        if (p.color == 'w') {
            cell = "37;" + cell;        // Pieces blanches
        } else if (p.color == 'b') {
            cell = "30;" + cell;        // Pieces noires
        }
        cell = "\033[" + cell;
        cout << cell;
        posColor = !posColor;
    };

    bool posColor = true;
    string colName;
    if (!reversed) {        // Affichage cote blanc
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
    } else {                // Affichage cote noir
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
    /// Fonction de creation de l'echiquier de debut de partie
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

    board = pushPiecesLine(board, 'w');     // On ajoute sur la ligne 1 les 8 pieces blanches
    board = pushPawnsLine(board, 'w');      // On ajoute sur la ligne 2 les 8 pions blancs
    for (short i=0; i<(4*8); i++) {
        board.push_back(piece{' ', ' '});   // On ajoute 4 lignes vides
    }
    board = pushPawnsLine(board, 'b');      // On ajoute sur la ligne 7 les 8 pions noirs
    board = pushPiecesLine(board, 'b');     // On ajoute sur la ligne 8 les 8 pieces noires

    return board;
}

piece movePiece(vector<piece> & chessboard, const short & depI, const short & arrI, vector<bool> & castle, const bool & unCastle=true) {
    /// Fonction qui permet de deplacer une piece sur l'echiquier de la case d'indixe <depI> jusqu'à la case <arrI>

    piece captured = chessboard[arrI];      // On enregistre la piece qui se fait manger si on doit annuler le coup
    chessboard[arrI] = chessboard[depI];    // On deplace la piece
    chessboard[depI] = piece {' ', ' '};    // On remplace son ancien emplacement par une case vide
    if ((arrI<=7 || arrI>=56) && chessboard[arrI].type=='P') chessboard[arrI].type = 'D';       // REGLE : promotion du pion en dame
    if (unCastle) {                         // REGLE : si on bouge une piece du roque, on ne peut plus roquer avec
        short offset = 0;
        if (chessboard[arrI].color == 'b') offset = 56;
        if (depI == 0+offset) castle[0] = false;
        if (depI == 7+offset) castle[1] = false;
        if (chessboard[arrI].type == 'R') {
            castle[0] = false;
            castle[1] = false;
        }
    }
    return captured;
}

vector<short> getPiecesIndex(const vector<piece> & chessboard, const char & type, const char & color) {
    /// Fonction de parcours de l'echiquier qui renvoie la liste des indices des objets de type <type> et de couleur <color>
    vector<short> indexes;
    for (short i=0; i<(short)chessboard.size(); ++i) {
        if (chessboard[i].type == type && chessboard[i].color == color)
            indexes.push_back(i);
    }
    return indexes;
}

vector<short> getPossibilitiesByDirection(const vector<piece> & chessboard, const short & index, const char & color, const vector<short> & directions) {
    /// Fonction qui permet de recuperer toutes les positions possibles selon une ou plusieurs direction(s)
    /// Ex : pour le fou, on regarde toutes les cases dans chaque diagonale jusqu'a ce qu'on arrive au bord de l'echiquier ou qu'on arrive sur une autre piece

    vector<short> possibilities;
    short curr_loc;
    for (const short & direction : directions) {
        curr_loc = index + direction;

        if (direction==-9 || direction==-7 || direction==7 || direction==9) {           // Si la direction est une diagonale
            if (index%8==0 && (direction==-9 || direction==7)) continue;                    // Si la piece se trouve sur la colonne 'a', on ne regarde pas les diagonales qui vont vers la gauche
            if (index%8==7 && (direction==-7 || direction==9)) continue;                    // Si la piece se trouve sur la colonne 'h', on ne regarde pas les diagonales qui vont vers la droite
            while (0<=curr_loc && curr_loc<=63 && chessboard[curr_loc].color!=color) {      // Tant qu'on ne sors pas de l'echiquier et qu'on a une case libre ou de couleur opposee
                possibilities.push_back(curr_loc);                                              // On enregistre l'indice dans les mouvements possibles
                if (chessboard[curr_loc].color!=' ' || curr_loc%8==0 || curr_loc%8==7) break;   // Si la piece est de couleur opposee ou qu'on se situe sur la colonne 'a' ou 'h', on s'arrete
                curr_loc += direction;                                                          // On deplace le curseur sur la prochaine case a regarder
            }
        }

        else if (direction==-8 || direction==8)                                         // Si la direction est verticale
            while (0<=curr_loc && curr_loc<=63 && chessboard[curr_loc].color!=color) {      // Tant qu'on ne sors pas de l'echiquier et qu'on a une case vide ou de couleur opposee
                possibilities.push_back(curr_loc);                                              // On enregistre l'indice dans les mouvements possibles
                if (chessboard[curr_loc].color!=' ') break;                                     // Si la piece est de couleur opposee, on s'arrete
                curr_loc += direction;                                                          // On deplace le curseur sur la prochaine case a regarder
            }

        else if (direction==-1 || direction==1) {                                       // Si la direction est horizontale
            if (index%8==0 && direction==-1) continue;                                      // Si la piece se trouve sur la colonne 'a', on ne regarde pas à gauche
            if (index%8==7 && direction==1)  continue;                                      // Si la piece se trouve sur la colonne 'h', on ne regarde pas à droite
            while (chessboard[curr_loc].color!=color) {                                     // Tant qu'on a une case libre ou de couleur opposee
                possibilities.push_back(curr_loc);                                              // On enregistre l'indice dans les mouvements possibles
                if (chessboard[curr_loc].color!=' ' || curr_loc%8==0 || curr_loc%8==7) break;   // Si la piece est de couleur opposee ou qu'on se situe sur la colonne 'a' ou 'h', on s'arrete
                curr_loc += direction;                                                          // On deplace le curseur sur la prochaine case a regarder
            }
        }
    }

    return possibilities;
}

vector<short> getPawnMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    if (c == 'w') {                                                 // Si le pion est blanc
        if (chessboard[index+8].type == ' ') {                          // Si la case du dessus est vide
            possibilities.push_back(index+8);                               // On enregistre l'indice dans les mouvements possibles
            if (8<=index && index<=15 && chessboard[index+16].type==' ')    // Si le pion se situe sur la ligne 2 et que les 2 cases du dessus sont vides
                possibilities.push_back(index+16);                              // On enregistre aussi celle qui est 2 cases au dessus
        }
        if (index%8!=0 && chessboard[index+7].color=='b')               // Si le pion n'est pas sur la colonne 'a' et que la case en haut a gauche contient une piece noire
            possibilities.push_back(index+7);                               // On enregistre la case en haut a gauche
        if (index%8!=7 && chessboard[index+9].color=='b')               // Si le pion n'est pas sur la colonne 'h' et que la case en haut a droite contient une piece noire
            possibilities.push_back(index+9);                               // On enregistre la case en haut a droite
    }

    else if (c == 'b') {                                            // Sinon si le pion est noir
        if (chessboard[index-8].type == ' ') {                          // Si la case du dessous est vide
            possibilities.push_back(index-8);                               // On enregistre l'indice dans les mouvements possibles
            if (48<=index && index<=55 && chessboard[index-16].type==' ')   // Si le pion se situe sur la ligne 7 et que les 2 cases du dessous sont vides
                possibilities.push_back(index-16);                              // On enregistre aussi celle qui est 2 cases au dessous
        }
        if (index%8!=0 && chessboard[index-9].color=='w')               // Si le pion n'est pas sur la colonne 'a' et que la case en bas a gauche contient une piece blanche
            possibilities.push_back(index-9);                               // On enregistre la case en bas a gauche
        if (index%8!=7 && chessboard[index-7].color=='w')               // Si le pion n'est pas sur la colonne 'h' et que la case en bas a droite contient une piece blanche
            possibilities.push_back(index-7);                               // On enregistre la case en bas a droite
    }

    return possibilities;
}

vector<short> getKnightMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    // On commence par verifier toutes les casess qui ne sont pas hors de l'echiquier pour le cavalier
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

    // Puis pour chaque case, on verifie si la case est vide ou de couleur opposee
    for (const short & value : toCheck) {
        if (chessboard[index+value].color != c)
            possibilities.push_back(index+value);
    }

    return possibilities;
}

vector<short> getBishopMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    // Pour chaque diagonale, on appelle la fonction qui recupere toutes les possibilites selon la direction
    for (const short & p : getPossibilitiesByDirection(chessboard, index, c, {-9, -7, 7, 9}))
        possibilities.push_back(p);

    return possibilities;
}

vector<short> getRookMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    // Pour chaque direction verticales et horizontales, on appelle la fonction qui recupere toutes les possibilites selon la direction
    for (const short & p : getPossibilitiesByDirection(chessboard, index, c, {-8, -1, 1, 8}))
        possibilities.push_back(p);

    return possibilities;
}

vector<short> getQueenMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    // Pour chaque direction diagonales, verticales et horizontales, on appelle la fonction qui recupere toutes les possibilites selon la direction
    for (const short & p : getPossibilitiesByDirection(chessboard, index, c, {-9, -8, -7, -1, 1, 7, 8, 9}))
        possibilities.push_back(p);

    return possibilities;
}

vector<short> getKingMoves(const vector<piece> & chessboard, const short & index, const char & c) {
    vector<short> possibilities;

    // On commence par verifier toutes les cases qui ne sont pas hors de l'echiquier pour le roi
    vector<short> toCheck;
    if (index%8 > 0) {
        if (index-9 >= 0) toCheck.push_back(-9);
        toCheck.push_back(-1);
        if (index+7 <= 63) toCheck.push_back(7);
    }
    if (index-8>=0) toCheck.push_back(-8);
    if (index+8<=63) toCheck.push_back(8);
    if (index%8 < 7) {
        if (index-7 >= 0) toCheck.push_back(-7);
        toCheck.push_back(1);
        if (index+9 <= 63) toCheck.push_back(9);
    }

    // Puis pour chaque case, on verifie si la case est vide ou de couleur opposee (on regarde si le roi est en echec plus tard)
    for (const short & value : toCheck) {
        if (chessboard[index+value].color!=c)
            possibilities.push_back(index+value);}

    return possibilities;
}

bool isAttacked(const vector<piece> & chessboard, const short & index, const char & color) {
    /// Fonction qui verifie si la case d'indice <index> est attaquee par une piece de couleur <color>

    for (const short & pawnI   : getPiecesIndex(chessboard, 'P', color))    // Pour chaque pion de couleur <color>
        for (const short & moveI : getPawnMoves  (chessboard, pawnI,   color)) if (moveI == index) return true;
    for (const short & knightI : getPiecesIndex(chessboard, 'C', color))    // Pour chaque cavalier de couleur <color>
        for (const short & moveI : getKnightMoves(chessboard, knightI, color)) if (moveI == index) return true;
    for (const short & bishopI : getPiecesIndex(chessboard, 'F', color))    // Pour chaque fou de couleur <color>
        for (const short & moveI : getBishopMoves(chessboard, bishopI, color)) if (moveI == index) return true;
    for (const short & rookI   : getPiecesIndex(chessboard, 'T', color))    // Pour chaque tour de couleur <color>
        for (const short & moveI : getRookMoves  (chessboard, rookI,   color)) if (moveI == index) return true;
    for (const short & queenI  : getPiecesIndex(chessboard, 'D', color))    // Pour chaque dame de couleur <color>
        for (const short & moveI : getQueenMoves (chessboard, queenI,  color)) if (moveI == index) return true;
    for (const short & moveI : getKingMoves(chessboard, getPiecesIndex(chessboard, 'R', color)[0], color))
        // Si la case d'indice <index> peut etre atteint par le roi de couleur <color>
        if (moveI == index) return true;

    return false;
}

vector<short> getPieceMoves(vector<piece> & chessboard, const short & index, vector<bool> & castle) {
    /// Fonction qui renvoie tous les mouvements possible de la piece d'indice <index>

    vector<short> moves;

    char t = chessboard[index].type;
    char c = chessboard[index].color;
    char enemyC = 'w';
    if (c == 'w') enemyC = 'b';

    // Selon le type de la piece, on appelle une fonction differente
    if      (t == 'P') moves = getPawnMoves  (chessboard, index, c);
    else if (t == 'C') moves = getKnightMoves(chessboard, index, c);
    else if (t == 'F') moves = getBishopMoves(chessboard, index, c);
    else if (t == 'T') moves = getRookMoves  (chessboard, index, c);
    else if (t == 'D') moves = getQueenMoves (chessboard, index, c);
    else if (t == 'R') moves = getKingMoves  (chessboard, index, c);

    vector<short> possibilities;
    if (t != 'R') {
        // Si la piece n'est pas un roi, on verifie si le roi n'est pas en echec apres avoir bouge la piece
        short kingI = getPiecesIndex(chessboard, 'R', c)[0];
        for (const short i : moves) {                                   // Pour chaque mouvement de la piece
            piece captured = movePiece(chessboard, index, i, castle);       // On place temporairement la piece
            if (!isAttacked(chessboard, kingI, enemyC))                     // Si le roi n'est pas en echec
                possibilities.push_back(i);                                     // On garde le coup
            movePiece(chessboard, i, index, castle);                        // On remet le coup a sa place
            chessboard[i] = captured;                                       // Sans oublier de remettre la piece qui a ete potentiellement mangee
        }
    } else {
        // Sinon, la piece est un roi
        // REGLE : le roque
        short offset = 0;
        if (c == 'b') offset=56;
        if (index==offset+4 && !isAttacked(chessboard, index, enemyC)) {    // Si le roi est a sa place et qu'il n'est pas en echec
            bool castle1 = true;
            if (!castle[0] || chessboard[offset].type!='T' || chessboard[offset].color!=c)  // Si la tour est a sa place (grand roque) et que les pieces n'ont jamais bougees
                castle1 = false;
            if (castle1)
                for (const short i : {3, 2, 1})    // Si les cases entre les pieces sont vides et ne sont pas attaquees
                    if (chessboard[offset+i].color != ' ' || isAttacked(chessboard, offset+i, enemyC))
                        castle1 = false;
            if (castle1) possibilities.push_back(offset+2); // Si toutes les conditions sont remplies, le grand roque est possible

            bool castle8 = true;
            if (!castle[1] || chessboard[offset+7].type!='T' || chessboard[offset+7].color!=c)  // Si la tour est a sa place (petit roque) et que les pieces n'ont jamais bougees
                castle8 = false;
            if (castle8)
                for (const short i : {5, 6})    // Si les cases entre les pieces sont vides et ne sont pas attaquees
                    if (chessboard[offset+i].color != ' ' || isAttacked(chessboard, offset+i, enemyC))
                        castle8 = false;
            if (castle8) possibilities.push_back(offset+6); // Si toutes les conditions sont remplies, le petit roque est possible
        }

        // On verifie si le roi est en echec apres l'avoir bouge
        for (const short i : moves) {                                       // Pour chaque mouvement du roi
            piece captured = movePiece(chessboard, index, i, castle, false);    // On le deplace temporairement
            if (!isAttacked(chessboard, i, enemyC))                             // Si le roi n'est pas en echec
                possibilities.push_back(i);                                         // On garde le coup
            movePiece(chessboard, i, index, castle, false);                     // On remet le coup a sa place
            chessboard[i] = captured;                                           // Sans oublier de remettre la piece qui a ete potentiellement mangee
        }
    }

    return possibilities;
}

bool isMat(vector<piece> & chessboard, const char & color, const char & enemyColor, vector<bool> & castle) {
    /// Fonction qui verifie si l'equipe <color> a perdu la partie
    short kingI = getPiecesIndex(chessboard, 'R', color)[0];

    if (!isAttacked(chessboard, kingI, enemyColor))
        // Si le roi n'est pas en echec
        return false;

    for (const char & t : {'P', 'C', 'F', 'T', 'D', 'R'})
        for (const short & i : getPiecesIndex(chessboard, t, color))
            // Pour chaque piece de la couleur attaquee
            if (getPieceMoves(chessboard, i, castle).size() != 0)
                // Si une piece peut bouger (donc sortir de l'echec)
                return false;

    // Aucune piece ne peut bouger
    return true;
}

bool isDraw(vector<piece> & chessboard, const char & color, vector<bool> & castle) {
    /// Fonction qui verifie s'il y a egalite (insuffisance materielle ou pat)

    auto getRemainingPieces = [](const vector<piece> & chessboard, const char & color) {
        /// Lambda permettant de recuperer la liste triee par ordre alphabetique des pieces restantes de l'equipe <color>
        string pieces;
        for (const piece & p : chessboard)
            if (p.color == color) pieces += p.type;
        sort(pieces.begin(), pieces.end());
        return pieces;
    };

    // Materiel insuffisant --> match nul s'il ne reste que les (2 rois), (roi + 1 cavalier vs roi) ou (roi + fou vs roi)
    string wPieces = getRemainingPieces(chessboard, 'w');
    string bPieces = getRemainingPieces(chessboard, 'b');
    if (wPieces=="R" && (bPieces=="R" || bPieces=="CR" || bPieces=="FR"))
        return true;
    if (bPieces=="R" && (wPieces=="CR" || wPieces=="FR"))
        return true;

    // Pat --> Le roi n'est pas en echec mais il ne dispose d'aucun coup qu soit dans les regles
    // On ne verifie pas si le roi est en echec ou pas car la fonction est appelee s'il n'y a pas echec et mat
    // Or cela signifie que soit le roi n'est pas en echec, soit un mouvement est possible pour contrer l'echec
    for (const char & t : {'P', 'C', 'F', 'T', 'D', 'R'})
        for (const short & i : getPiecesIndex(chessboard, t, color))
            if (getPieceMoves(chessboard, i, castle).size() != 0)
                return false;

    return false;
}

short echecs(const string & t1, const string & t2) {

    // Choix aleatoire des couleurs
    vector<string> teams = {t1, t2};
    if (rand()%2 == 0) teams = {t2, t1};
    cout << "L'equipe " << teams[0] << " joue avec les blancs." << endl
         << "L'equipe " << teams[1] << " joue avec les noirs." << endl;
    pressEnter();

    // Valeurs du tournoi
    vector<string> colors = {"blancs", "noirs"};
    vector<vector<bool>> castle = {{true, true}, {true, true}};
    bool turn = false;

    cout << "Pour un gameplay plus agreable dans la console, vous pouvez modifier les couleurs par defaut du terminal pour les faire correspondre aux couleurs classiques d'un echiquier :" << endl
         << "Pieces blanches : #FFF" << endl
         << "Cases blanches  : #E0C18C" << endl
         << "Pieces noires   : #000" << endl
         << "Cases noires    : #B07242" << endl;
    pressEnter();

    // Creation des pieces
    //vector<piece> chessboard = createChessboard();
    vector<piece> chessboard;
    for (short i=0; i<=63; i++)
        chessboard.push_back(piece {' ', ' '});
    chessboard[4] = piece {'R', 'w'};
    chessboard[60] = piece {'R', 'b'};

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

            if (answer.size() == 5) {
                short depIndex = 8*(answer[1]-'0'-1) + answer[0]-'a';
                short arrIndex = 8*(answer[4]-'0'-1) + answer[3]-'a';

                if (chessboard[depIndex].color!=color) {
                    // Si on essaye de bouger une case vide ou de couleur opposee
                    cout << inputErrMsg << endl << endl;
                    continue;
                }

                for (const short & index : getPieceMoves(chessboard, depIndex, castle[turn]))
                    // Pour chaque mouvement possible de la piece ciblee
                    if (index == arrIndex) {

                        // On bouge la tour si on roque
                        short offset = 0;
                        if (color == 'b') offset = 56;
                        if (chessboard[depIndex].type=='R' && depIndex==offset+4) {
                            if (arrIndex == offset+2)
                                movePiece(chessboard, offset, offset+3, castle[turn]);
                            else if (arrIndex == offset+6)
                                movePiece(chessboard, offset+7, offset+5, castle[turn]);
                        }

                        // On bouge la piece
                        movePiece(chessboard, depIndex, arrIndex, castle[turn]);
                        correctInput = !correctInput;
                        break;
                    }
            }

            else
                cout << inputErrMsg << endl << endl;
        }

        if (isMat(chessboard, enemyColor, color, castle[turn])) {
            // Verification de mat
            displayChessboard(chessboard, !turn);
            cout << "\nEchec et mat !" << endl
                 << "L'equipe " << teams[turn] << " gagne la partie et encaisse 2 points" << endl;
            return turn;
        } else if (isDraw(chessboard, enemyColor, castle[turn])) {
            // Verification d'egalite
            cout << "Les equipes font egalite et encaissent 1 point chaucune" << endl;
        }

        // On laisse le tour a l'equipe d'en face
        turn = !turn;
    }
}
