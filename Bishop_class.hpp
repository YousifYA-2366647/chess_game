#ifndef BISHOP_CLASS_HPP
#define BISHOP_CLASS_HPP
#include "rule_class.hpp"

class Bishop: public Piece {
public:
    Bishop(char color, char letter_pos, int cipher_pos): Piece(color, letter_pos, cipher_pos, Piece::BISHOP) {}

    bool attacking(std::vector<std::vector<Piece*>> board, char targetLetterPos, int targetCipherPos) {
        return (m_ruleSet->isValid(this, board, targetLetterPos, targetCipherPos) &&
        board[targetCipherPos-1][targetLetterPos-'A']->getColor() != 'E' && 
        board[targetCipherPos-1][targetLetterPos-'A']->getColor() != getColor());
    }

    void move(Board* board, char targetLetterPos, int targetCipherPos) override {
        std::vector<std::vector<Piece*>> boardPieces = board->getBoard();
        bool attack_imminent = attacking(boardPieces, targetLetterPos, targetCipherPos);
        if (!m_ruleSet->isValid(this, boardPieces, targetLetterPos, targetCipherPos) && !attack_imminent) {
            std::cout << "invalid move.\n";
            return;
        }
        if (attack_imminent) {
            m_ruleSet->capturePiece(board, targetLetterPos, targetCipherPos);
        }

        boardPieces[targetCipherPos-1][targetLetterPos-'A'] = new Bishop(getColor(), targetLetterPos, targetCipherPos);

        boardPieces[getCipherPos()-1][getLetterPos()-'A'] = new Piece('E', getLetterPos(), getCipherPos(), Piece::EMPTY);

        board->setBoard(boardPieces);
    }
private:
    Rules* m_ruleSet;
};

#endif