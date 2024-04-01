#ifndef BOARD_CLASS_HPP
#define BOARD_CLASS_HPP
#include <vector>
#include "Piece_class.hpp"

// deze code is ver van perfect, er zijn zoveel dingen die niet horen te gebeuren.
// success met dit te proberen debuggen
// dit was origineel 8 verschillende files voor elke class,
// maar er waren problemen met cyclische inclusions en wat nog
// ik snapte niet hoe ik dat kon verkijden omdat ik de methodes van Board nodig had
// in de Piece header file en de methodes van Piece nodig had in Board header file
// ik koos ervoor om mijn problemen te negeren en gewoon het eerst beste oplossing te pakken.

class Board {
// de Board class stelt het bord voor waar de stukken op liggen
public:
    // eerst de constructors en destructors, de constructors zal ook de vector die het bord voorstelt groot genoeg maken
    // zodat er 64 stukken op kunnen passen
    Board() {
        m_board.resize(m_size);
        for (int i = 0; i < m_size; i++) {
            m_board[i].resize(m_size);
        }
    };

    ~Board() {
        std::cout << "Game has ended.\n";
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete m_board[i][j];
            }
        }
    };

    void markSpots(Board* board, char kingLetterPos, int kingCipherpos, char attackingLetterPos, int attackingCipherPos) {
        std::vector<std::vector<Piece*>> boardPieces = board->getBoard();
        if (kingCipherpos > attackingCipherPos) {
            if (kingLetterPos > attackingLetterPos) {
                for (int i = kingCipherpos-1, j = kingLetterPos-'A'; i < attackingCipherPos && j <= attackingLetterPos-'A'; i++, j++) {
                    boardPieces[i][j]->setIsAttacking(true);
                }
            }
            else if (kingLetterPos == attackingLetterPos) {
                for (int i = kingCipherpos-1; i < attackingCipherPos; i++) {
                    boardPieces[i][kingLetterPos]->setIsAttacking(true);
                }
            }
            else {
                for (int i = kingCipherpos-1, j = kingLetterPos-'A'+1; i < attackingCipherPos && j >= attackingLetterPos-'A'; i++, j--);
            }
        }
    }

    // de getter, de setter staat ook van onder als set_board
    std::vector<std::vector<Piece*>> getBoard() {
        return m_board;
    }
    
    void setBoard(std::vector<std::vector<Piece*>> board_pieces) {
        // de setter van Board
        m_board = board_pieces;
    };

    void printBoard(std::vector<std::vector<Piece*>>& board_pieces) {
        // print_board geeft een visueel weergave van het bord
        std::cout << "\n";
        for (int i = 0; i < 8; i++) {
            std::cout << 8-i << "|";
            for (int j = 0; j < 8; j++) {
                    board_pieces[7-i][j]->printPiece();
            }
            std::cout << "\n";
            if (i == 7) {
                std::cout << "  ⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺\n   A  B  C  D  E  F  G  H\n";
            }
        }
    }; 

    char getKingLetterPos() {
        return m_kingLetterPos;
    }

    int getKingCipherPos() {
        return m_kingCipherPos;
    }

    void setKingPos(char kingLetterPos, int kingCipherPos) {
        m_kingLetterPos = kingLetterPos;
        m_kingCipherPos = kingCipherPos;
    }
private:
    int m_size = 8;
    char m_kingLetterPos;
    int m_kingCipherPos;
    std::vector<std::vector<Piece*>> m_board; // het bord is dus een 2D lijst van pointers naar stukken
};

#endif