#ifndef KING_CLASS_HPP
#define KING_CLASS_HPP
#include "Rook_class.hpp"

class King: public Piece {
public:
    King(char color, char letter_pos, int cipher_pos): Piece(color, letter_pos, cipher_pos, Piece::KING) {}

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
        if (m_ruleSet->canCastle(this, board_pieces, targetLetterPos, targetCipherPos)) {
            if (targetLetterPos == getLetterPos() - 2 && targetCipherPos == getCipherPos()) {
                if (getColor() == 'W') {
                    if (board_pieces[0][0]->getType() == Piece::ROOK && board_pieces[0][0]->getColor() == 'W' &&
                        board_pieces[0][1]->getType() == Piece::EMPTY && board_pieces[0][2]->getType() == Piece::EMPTY && board_pieces[0][3]->getType() == Piece::EMPTY) {
                            board_pieces[0][2] = new King('W', targetLetterPos, targetCipherPos);
                            board_pieces[0][4] = new Piece('E', 'A'+4, 1, Piece::EMPTY);
                            board_pieces[0][3] = new Rook('W', 'A'+3, 1);
                            board_pieces[0][0] = new Piece('E', 'A', 1, Piece::EMPTY);
                        }
                }
                else if (getColor() == 'B') {
                    if (board_pieces[7][0]->getType() == Piece::ROOK && board_pieces[7][0]->getColor() == 'B' &&
                        board_pieces[7][1]->getType() == Piece::EMPTY && board_pieces[7][2]->getType() == Piece::EMPTY && board_pieces[7][3]->getType() == Piece::EMPTY) {
                            board_pieces[7][2] = new King('B', targetLetterPos, targetCipherPos);
                            board_pieces[7][4] = new Piece('E', 'A'+4, 8, Piece::EMPTY);
                            board_pieces[7][3] = new Rook('B', 'A'+3, 8);
                            board_pieces[7][0] = new Piece('E', 'A', 8, Piece::EMPTY);
                        }
                }
            }
            else if (targetLetterPos == getLetterPos() + 2 && targetCipherPos == getCipherPos()) {
                if (getColor() == 'W') {
                    if (board_pieces[0][7]->getType() == Piece::ROOK && board_pieces[0][7]->getColor() == 'W' &&
                        board_pieces[0][6]->getType() == Piece::EMPTY && board_pieces[0][5]->getType() == Piece::EMPTY) {
                            board_pieces[0][6] = new King('W', targetLetterPos, targetCipherPos);
                            board_pieces[0][4] = new Piece('E', 'A'+4, 1, Piece::EMPTY);
                            board_pieces[0][5] = new Rook('W', 'A'+5, 1);
                            board_pieces[0][7] = new Piece('E', 'H', 1, Piece::EMPTY);
                        }
                }
                else if (getColor() == 'B') {
                    if (board_pieces[7][7]->getType() == Piece::ROOK && board_pieces[7][7]->getColor() == 'B' &&
                        board_pieces[7][6]->getType() == Piece::EMPTY && board_pieces[7][5]->getType() == Piece::EMPTY) {
                            board_pieces[7][6] = new King('B', targetLetterPos, targetCipherPos);
                            board_pieces[7][4] = new Piece('E', 'A'+4, 8, Piece::EMPTY);
                            board_pieces[7][5] = new Rook('B', 'A'+5, 8);
                            board_pieces[7][0] = new Piece('E', 'H', 8, Piece::EMPTY);
                        }
                }
            }
            else {
                board_pieces[targetCipherPos-1][targetLetterPos-'A'] = new King(getColor(), targetLetterPos, targetCipherPos);

                board_pieces[getCipherPos()-1][getLetterPos()-'A'] = new Piece('E', getLetterPos(), getCipherPos(), Piece::EMPTY);
            }
            this->setKingHasMoved(true);
            board->setKingPos(targetLetterPos, targetCipherPos);
            board->setBoard(board_pieces);
            return;
        }

        board_pieces[targetCipherPos-1][targetLetterPos-'A'] = new King(getColor(), targetLetterPos, targetCipherPos);

        board_pieces[getCipherPos()-1][getLetterPos()-'A'] = new Piece('E', getLetterPos(), getCipherPos(), Piece::EMPTY);

        board->setKingPos(targetLetterPos, targetCipherPos);
        board->setBoard(board_pieces);
    }
private:
    Rules* m_ruleSet;
};

#endif