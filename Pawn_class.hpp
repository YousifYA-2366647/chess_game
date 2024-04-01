#ifndef PAWN_CLASS_HPP
#define PAWN_CLASS_HPP
#include "rule_class.hpp"

class Pawn: public Piece {
// de Pawn class is een afgeleide class van Piece, het stelt de soldaten voor
public:
    // de constructor
    Pawn(char color, char letterPos, int cipherPos): Piece(color, letterPos, cipherPos, Piece::PAWN) {}

    bool attacking(std::vector<std::vector<Piece*>> board, char targetLetterPos, int targetCipherPos) {
        // de "attacking" functie-reeks zal kijken of de gekozen stuk iets zal aanvallen, het valt iets aan
        // als de plek waar het wilt gaan staan niet leeg is en niet dezelfde kleur heeft.
        // maar een pion is een speciaal geval omdat hij schuin naar boven/onder aanvalt, wat niet zijn beweeg patroon is
        // en passent moet ik ook nog erin zetten
        if (getColor() == 'W') {
            // in bounds
            return targetCipherPos <= 8 && 
            targetCipherPos >= 1 && 
            targetLetterPos >= 'A' && 
            targetLetterPos <= 'H' && 

            // beweging is schuin naar boven
            targetCipherPos - getCipherPos() == 1 &&
            abs(targetLetterPos - getLetterPos()) == 1 &&

            // plek waar we naar bewegen is niet leeg en niet dezelfde kleur
            board[targetCipherPos-1][targetLetterPos-'A']->getColor() != 'E' &&
            board[targetCipherPos-1][targetLetterPos-'A']->getColor() != getColor();
        }
        else if(getColor() == 'B') {
            // hetzelfde maar voor zwart, zwart mag shuin naar onder aanvallen
            return targetCipherPos <= 8 && 
            targetCipherPos >= 1 && 
            targetLetterPos >= 'A' && 
            targetLetterPos <= 'H' && 

            targetCipherPos - getCipherPos() == -1 &&
            abs(targetLetterPos - getLetterPos()) == 1 &&

            board[targetCipherPos-1][targetLetterPos-'A']->getColor() != 'E' &&
            board[targetCipherPos-1][targetLetterPos-'A']->getColor() != getColor();
        }
        return false;
    }

    void move_first(Board* board, char targetLetterPos, int targetCipherPos) {
        // implementatie van de eerste zet van een pion, hier mag hij twee vakken naar voor bewegen
        // de rest is vrijwel identiek aan de move van Piece
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

        board_pieces[targetCipherPos-1][targetLetterPos-'A'] = new Pawn(getColor(), targetLetterPos, targetCipherPos);

        board_pieces[getCipherPos()-1][getLetterPos()-'A'] = new Piece('E', getLetterPos(), getCipherPos(), Piece::EMPTY);

        board->setBoard(board_pieces);
    }

    void move(Board* board, char targetLetterPos, int targetCipherPos) override {
        // hetzelfde als move_first maar hier mag het enkel een vak naar voor gaan
        std::vector<std::vector<Piece*>> board_pieces = board->getBoard();
        bool attack_imminent =  attacking(board_pieces, targetLetterPos, targetCipherPos);
        bool isValidMove = m_ruleSet->isValid(this, board_pieces, targetLetterPos, targetCipherPos);
        if (!isValidMove && !attack_imminent) {
            std::cout << "invalid move.\n";
            return;
        }
        if (isValidMove && attack_imminent) {
            // als de pion iets aanvalt dan zal de capturePiece methode het verder afhandelen
            m_ruleSet->capturePiece(board, targetLetterPos, targetCipherPos);
        }
        if (!m_has_moved) {
            move_first(board, targetLetterPos, targetCipherPos);
            m_has_moved = true;
            return;
        }
        board_pieces[targetCipherPos-1][targetLetterPos-'A'] = new Pawn(getColor(), targetLetterPos, targetCipherPos);

        board_pieces[getCipherPos()-1][getLetterPos()-'A'] = new Piece('E', getLetterPos(), getCipherPos(), Piece::EMPTY);

        board->setBoard(board_pieces);
        m_has_moved = true;
    }
private:
    bool m_has_moved = false;
    Rules* m_ruleSet;
};

#endif