#ifndef QUEEN_CLASS_HPP
#define QUEEN_CLASS_HPP
#include "rule_class.hpp"

class Queen: public Piece {
public:
    Queen(char color, char letter_pos, int cipher_pos): Piece(color, letter_pos, cipher_pos, Piece::QUEEN) {}

    bool attacking(std::vector<std::vector<Piece*>> board, char targetLetterPos, int targetCipherPos) {
        return (m_ruleSet->isValid(this, board, targetLetterPos, targetCipherPos) &&
        board[targetCipherPos-1][targetLetterPos-'A']->getColor() != 'E' && 
        board[targetCipherPos-1][targetLetterPos-'A']->getColor() != getColor());
    }

    void move(Board* board, char targetLetterPos, int targetCipherPos) override {
        std::vector<std::vector<Piece*>> board_pieces = board->getBoard();
        bool attack_imminent = attacking(board_pieces, targetLetterPos, targetCipherPos);
        bool isValidMove = m_ruleSet->isValid(this, board_pieces, targetLetterPos, targetCipherPos);
        if (!isValidMove && !attack_imminent) {
            std::cout << "invalid move.\n";
            return;
        }
        if (isValidMove && attack_imminent) {
            m_ruleSet->capturePiece(board, targetLetterPos, targetCipherPos);
        }

        board_pieces[targetCipherPos-1][targetLetterPos-'A'] = new Queen(getColor(), targetLetterPos, targetCipherPos);

        board_pieces[getCipherPos()-1][getLetterPos()-'A'] = new Piece('E', getLetterPos(), getCipherPos(), Piece::EMPTY);

        board->setBoard(board_pieces);
    }
private:
    Rules* m_ruleSet;
};

#endif