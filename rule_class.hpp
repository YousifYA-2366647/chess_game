#ifndef RULE_CLASS_HPP
#define RULE_CLASS_HPP
#include <tuple>
#include "board_class.hpp"

class Rules {
public:
    ~Rules() {
        return;
    }
    bool blocked(std::vector<std::vector<Piece*>>& board, char pieceLetterPos, int pieceCipherPos, char targetLetterPos, int targetCipherPos) {
        if (targetLetterPos > pieceLetterPos) {
            if (targetCipherPos > pieceCipherPos) {
                for (int i = pieceCipherPos, j = pieceLetterPos-'A'+1; i < targetCipherPos && j <= targetLetterPos-'A'; i++, j++) {
                    if (board[i][j]->getColor() != 'E') {
                        return true;
                    }
                }
            }
            else if (pieceCipherPos == targetCipherPos) {
                for (int j = pieceLetterPos-'A'+1; j < targetLetterPos-'A'+1; j++) {
                    if (board[pieceCipherPos-1][j]->getColor() != 'E') {
                        return true;
                    }
                }
            }
            else {
                for (int i = pieceCipherPos-2, j = pieceLetterPos-'A'+1; i > targetCipherPos && j <= targetLetterPos-'A';i--, j++) {
                    if (board[i][j]->getColor() != 'E') {
                        return true;
                    }
                }
            }
        }
        else if (pieceLetterPos == targetLetterPos) {
            if (targetCipherPos > pieceCipherPos) {
                for (int i = pieceCipherPos; i < targetCipherPos; i++) {
                    if (board[i][pieceLetterPos-'A']->getColor() != 'E') {
                        return true;
                    }
                }
            }
            else if (targetCipherPos < pieceCipherPos) {
                for (int i = pieceCipherPos-2; i > targetCipherPos; i--) {
                    if (board[i][pieceLetterPos-'A']->getColor() != 'E') {
                        return true;
                    }
                }
            }
        }
        else {
            if (targetCipherPos > pieceCipherPos) {
                for (int i = pieceCipherPos, j = pieceLetterPos-'A'-1; i < targetCipherPos && j > targetLetterPos-'A'; i++, j--) {
                    if (board[i][j]->getColor() != 'E') {
                        return true;
                    }
                }
            }
            else if (pieceCipherPos == targetCipherPos) {
                for (int j = pieceLetterPos-'A'-1; j > targetLetterPos-'A'; j--) {
                    if (board[pieceCipherPos-1][j]->getColor() != 'E') {
                        return true;
                    }
                }
            }
            else {
                for (int i = pieceCipherPos-2, j = pieceLetterPos-'A'-1; i > targetCipherPos && j > targetLetterPos-'A'; i--, j--) {
                    if (board[i][j]->getColor() != 'E') {
                        return true;
                    }
                }
            }
        }
        return false;
    };
    
    std::tuple<bool, Piece*> validKing(std::vector<std::vector<Piece*>>& board, char kingLetterPos, int kingCipherPos, char kingTargetLetterPos, int kingTargetCipherPos) {
        Piece* kingPiece = board[kingCipherPos-1][kingLetterPos-'A'];
        if (kingPiece->getType() == Piece::KING) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board[i][j]->getColor() != kingPiece->getColor() && 
                        board[i][j]->getColor() != 'E' &&
                        isAttacking(board[i][j], board, kingTargetLetterPos, kingTargetCipherPos)) {
                        return std::make_tuple(false, board[i][j]);
                    }
                }
            }
        }
        return std::make_tuple(true, board[0][0]);
    };

    bool canCastle(Piece* kingPiece, std::vector<std::vector<Piece*>> board, char targetLetterPos, int targetCipherPos) {
        if (kingPiece->getLetterPos()-targetLetterPos == 2 && kingPiece->getCipherPos() == targetCipherPos) {
            if ((kingPiece->getColor() == 'W' && 
                (board[0][0]->getType() == Piece::ROOK && 
                board[0][0]->getColor() == 'W' &&
                board[0][1]->getType() == Piece::EMPTY && 
                board[0][2]->getType() == Piece::EMPTY && 
                board[0][3]->getType() == Piece::EMPTY)) ||
                (kingPiece->getColor() == 'B' && 
                (board[7][0]->getType() == Piece::ROOK && 
                board[7][0]->getColor() == 'B' &&
                board[7][1]->getType() == Piece::EMPTY && 
                board[7][2]->getType() == Piece::EMPTY && 
                board[7][3]->getType() == Piece::EMPTY))) {
                    return true;
            }
        }
        else if (kingPiece->getLetterPos()-targetLetterPos == -2 && kingPiece->getCipherPos() == targetCipherPos) {
            if ((kingPiece->getColor() == 'W' && 
                (board[0][7]->getType() == Piece::ROOK && 
                board[0][7]->getColor() == 'W' &&
                board[0][6]->getType() == Piece::EMPTY && 
                board[0][5]->getType() == Piece::EMPTY)) ||
                (kingPiece->getColor() == 'B' && 
                (board[7][7]->getType() == Piece::ROOK && 
                board[7][7]->getColor() == 'B' &&
                board[7][6]->getType() == Piece::EMPTY && 
                board[7][5]->getType() == Piece::EMPTY))) {
                    return true;
            }
        }
        return false;
    }

    bool isAttacking(Piece* pieceToMove, std::vector<std::vector<Piece*>> board, char targetLetterPos, int targetCipherPos) {
        if (targetCipherPos < 1 || targetCipherPos > 8 || targetLetterPos < 'A' || targetLetterPos > 'H' ||
        board[targetCipherPos-1][targetLetterPos-'A']->getColor() == pieceToMove->getColor() ||
        (pieceToMove->getCipherPos() == targetCipherPos && pieceToMove->getLetterPos() == targetLetterPos ||
        (pieceToMove->getType() != Piece::KNIGHT && blocked(board, pieceToMove->getLetterPos(), pieceToMove->getCipherPos(), targetLetterPos, targetCipherPos)))) {
            return false;
        }

        switch(pieceToMove->getType()) {
            case Piece::PAWN:
                if ((pieceToMove->getColor() == 'W' && 
                ((pieceToMove->getCipherPos() - targetCipherPos == -1 && 
                abs(pieceToMove->getLetterPos() - targetLetterPos) == 1)))
                ||
                (pieceToMove->getColor() == 'B' && 
                ((pieceToMove->getCipherPos() - targetCipherPos == 1 && 
                abs(pieceToMove->getLetterPos() - targetLetterPos) == 1)))) {
                    return true;
                }
                break;
            default:
                if (isValid(pieceToMove, board, targetLetterPos, targetCipherPos)) {
                    return true;
                }
        }
        return false;
    }

    bool isValid(Piece* pieceToMove, std::vector<std::vector<Piece*>> board, char targetLetterPos, int targetCipherPos) {
        if (targetCipherPos < 1 || targetCipherPos > 8 || targetLetterPos < 'A' || targetLetterPos > 'H' ||
        board[targetCipherPos-1][targetLetterPos-'A']->getColor() == pieceToMove->getColor() ||
        (pieceToMove->getCipherPos() == targetCipherPos && pieceToMove->getLetterPos() == targetLetterPos ||
        (pieceToMove->getType() != Piece::KNIGHT && blocked(board, pieceToMove->getLetterPos(), pieceToMove->getCipherPos(), targetLetterPos, targetCipherPos)))) {
            return false;
        }

        switch(pieceToMove->getType()) {
            case Piece::PAWN:
                if ((pieceToMove->getColor() == 'W' && ((pieceToMove->getCipherPos() - targetCipherPos == -2 || pieceToMove->getCipherPos() - targetCipherPos == -1) ||
                (pieceToMove->getCipherPos() - targetCipherPos == -1 && abs(pieceToMove->getLetterPos() - targetLetterPos) == 1)))
                ||
                (pieceToMove->getColor() == 'B' && ((pieceToMove->getCipherPos() - targetCipherPos == 2 || pieceToMove->getCipherPos() - targetCipherPos == 1) ||
                (pieceToMove->getCipherPos() - targetCipherPos == 1 && abs(pieceToMove->getLetterPos() - targetLetterPos) == 1)))) {
                    return true;
                }
                break;
            case Piece::ROOK:
                if ((pieceToMove->getCipherPos() == targetCipherPos && pieceToMove->getLetterPos() != targetLetterPos) ||
                (pieceToMove->getCipherPos() != targetCipherPos && pieceToMove->getLetterPos() == targetLetterPos)) {
                    return true;
                }
                break;
            case Piece::KNIGHT:
                if ((abs(pieceToMove->getCipherPos()-targetCipherPos) == 2 && abs(pieceToMove->getLetterPos()-targetLetterPos) == 1)
                    ||
                    (abs(pieceToMove->getCipherPos()-targetCipherPos) == 1 && abs(pieceToMove->getLetterPos()-targetLetterPos) == 2)) {
                        return true;
                    }
                break;
            case Piece::BISHOP:
                if (abs(pieceToMove->getCipherPos()-targetCipherPos) == abs(pieceToMove->getLetterPos()-targetLetterPos)) {
                    return true;
                }
                break;
            case Piece::QUEEN:
                if ((abs(pieceToMove->getCipherPos()-targetCipherPos) == abs(pieceToMove->getLetterPos()-targetLetterPos))
                ||
                ((pieceToMove->getCipherPos() == targetCipherPos && pieceToMove->getLetterPos() != targetLetterPos) ||
                (pieceToMove->getCipherPos() != targetCipherPos && pieceToMove->getLetterPos() == targetLetterPos))) {
                    return true;
                }
                break;
            case Piece::KING:
                if ((std::get<0>(validKing(board, pieceToMove->getLetterPos(), pieceToMove->getCipherPos(), targetLetterPos, targetCipherPos)) &&
                    ((abs(pieceToMove->getCipherPos()-targetCipherPos) == 1 && pieceToMove->getLetterPos() == targetLetterPos) || 
                    (abs(pieceToMove->getLetterPos()-targetLetterPos) == 1 && pieceToMove->getCipherPos() == targetCipherPos) ||
                    (abs(pieceToMove->getCipherPos()-targetCipherPos) == 1 && abs(pieceToMove->getLetterPos()-targetLetterPos) == 1))) || 
                    canCastle(pieceToMove, board, targetLetterPos, targetCipherPos)) {
                        return true;
                    }
                break;
        }
        return false;
    };
    
    void capturePiece(Board* board, char targetLetterPos, int targetCipherPos) {
        std::vector<std::vector<Piece*>> boardPieces = board->getBoard();
        boardPieces[targetCipherPos-1][targetLetterPos-'A']->setColor('E');
        boardPieces[targetCipherPos-1][targetLetterPos-'A']->setType(Piece::EMPTY);
        board->setBoard(boardPieces);
    };
    
    void promoting(Board* board, char pieceLetterPos, int pieceCipherPos, char targetLetterPos, int targetCipherPos, Piece::Type typeChoice);
    
    std::tuple<bool, Piece*> mate(Board& board, char kingLetterPos, int kingCipherPos) {
        std::vector<std::vector<Piece*>> boardPieces = board.getBoard();
        return validKing(boardPieces, kingLetterPos, kingCipherPos, kingLetterPos, kingCipherPos);
    };
    
    bool checkmate(Board& board, char kingLetterPos, int kingCipherPos) {
        std::vector<std::vector<Piece*>> boardPieces = board.getBoard();
        for (int i = kingCipherPos-1; i <= kingCipherPos+1; i++) {
            for (int j = kingLetterPos-'A'-1; j <= kingLetterPos-'A'+1; j++) {
                if (i > 0 && i < 8 && j > 0 && j < 8) {
                    if (std::get<0>(validKing(boardPieces, kingLetterPos, kingCipherPos, char('A'+j), i))) {
                        return false;
                    }
                }
            }
        }
        return true;
    };
};

#endif