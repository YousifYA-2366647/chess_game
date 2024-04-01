#ifndef PIECE_CLASS_HPP
#define PIECE_CLASS_HPP
#include <iostream>
#include <stdlib.h>

class Board;

class Piece  { // THE ONE PIECE, THE ONE PIECE IS REAL
// deze class stelt alle stukken voor, ook de lege stukken (lege plekken) zijn een Piece
public:
    enum Type {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, EMPTY}; // de mogelijkheden voor de Piece objecten
    Piece(char color, char letter_pos ,int cipher_pos, Piece::Type type) {
        m_type = type;
        m_color = color;
        m_letter_coordinate = letter_pos;
        m_cipher_coordinate = cipher_pos;
    } // een constructor die alle private members waardes geeft die worden meegegeven als Piece() wordt opgeroepen

    virtual void move(Board* board, char target_letter_pos, int target_cipher_pos) {
        board = board;
        target_letter_pos = target_letter_pos;
        target_cipher_pos = target_cipher_pos;
        return;
    };
    // dit is de belangrijkste functie van de hele script, dit is wat ervoor zorgt dat een stuk kan bewgen
    // maar dit is specifiek voor elke class, dus ik heb ervoor gekozen om polymorfisme te gebruiken en de functies
    // in elke class opnieuw te defineren

    void printPiece() {
        // dit legt zichzelf uit
        // deze functie werd gerepliceerd voor elk soort stuk
        switch(getType()) {
            case Piece::EMPTY:
                std::cout << " • ";
                break;
            case Piece::PAWN:
                if (getColor() == 'B') {std::cout << " ♙ ";}
                else if (getColor() == 'W') {std::cout << " ♟ ";}
                break;
            case Piece::ROOK:
                if (getColor() == 'B') {std::cout << " ♖ ";}
                else if (getColor() == 'W') {std::cout << " ♜ ";}
                break;
            case Piece::KNIGHT:
                if (getColor() == 'B') {std::cout << " ♘ ";}
                else if (getColor() == 'W') {std::cout << " ♞ ";}
                break;
            case Piece::BISHOP:
                if (getColor() == 'B') {std::cout << " ♗ ";}
                else if (getColor() == 'W') {std::cout << " ♝ ";}
                break;
            case Piece::QUEEN:
                if (getColor() == 'B') {std::cout << " ♕ ";}
                else if (getColor() == 'W') {std::cout << " ♛ ";}
                break;
            case Piece::KING:
                if (getColor() == 'B') {std::cout << " ♔ ";}
                else if (getColor() == 'W') {std::cout << " ♚ ";}
                break;
        }
    }

    // dan nog de nodige getters en setters
    char getLetterPos() {
        return m_letter_coordinate;
    }

    Type getType() {
        return m_type;
    }

    int getCipherPos() {
        return m_cipher_coordinate;
    }

    char getColor() {
        return m_color;
    }

    void setType(Piece::Type type) {
        m_type = type;
    }

    void setLetterPos(char target_letter_pos) {
        m_letter_coordinate = target_letter_pos;
    }

    void setCipherPos(int target_cipher_pos) {
        m_cipher_coordinate = target_cipher_pos;
    }

    void setColor(char target_color) {
        m_color = target_color;
    }

    void setIsAttacking(bool isAttacking) {
        m_isAttacking = isAttacking;
    } 

    bool getKingHasMoved() {
        return m_kingHasMoved;
    }

    void setKingHasMoved(bool targetHasMoved) {
        m_kingHasMoved = targetHasMoved;
    }

private:
    bool m_kingHasMoved = false;
    bool m_isAttacking = false;
    Type m_type; // soort stuk (soldaat, paard, kasteel, ...)
    char m_color; // kleur van het stuk (wit/zwart)
    char m_letter_coordinate; // het letter coordinaat (horizontale as)
    int m_cipher_coordinate; // het cijfer coordinaat (verticale as)
};

#endif