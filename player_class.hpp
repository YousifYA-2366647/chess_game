#ifndef PLAYER_CLASS_HPP
#define PLAYER_CLASS_HPP
#include <string.h>
#include "Pawn_class.hpp"
#include "Knight_class.hpp"
#include "Bishop_class.hpp"
#include "Queen_class.hpp"
#include "King_class.hpp"

class Player {
public:

    void makeBoard(Board* board) {
        // alle stukken op het bord maken...
        // dit kon veel korter (denk ik)
        std::vector<std::vector<Piece*>> boardPieces;
        boardPieces.resize(8);
        for (int k = 0; k < 8; k++) {
            boardPieces[k].resize(8);
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if(i == 7) {
                    if (j == 0) {
                        // creat_piece zal dus een pointer naar een Piece object maken, afhankelijk van de argumenten die worden meegegeven zal het een van de
                        // derived classes zij (Pawn, Knight, Rook, ...)
                        boardPieces[i][j] = new Rook('B', char('A'+j), i+1);
                    }
                    else if (j == 1) {
                        boardPieces[i][j] = new Knight('B', char('A'+j), i+1);
                    }
                    else if (j == 2) {
                        boardPieces[i][j] = new Bishop('B', char('A'+j), i+1);
                    }
                    else if (j == 3) {
                        boardPieces[i][j] = new Queen('B', char('A'+j), i+1);
                    }
                    else if (j == 4) {
                        boardPieces[i][j] = new King('B', char('A'+j), i+1);
                    }
                    else if (j == 5) {
                        boardPieces[i][j] = new Bishop('B', char('A'+j), i+1);
                    }
                    else if (j == 6) {
                        boardPieces[i][j] = new Knight('B', char('A'+j), i+1);
                    }
                    else if (j == 7) {
                        boardPieces[i][j] = new Rook('B', char('A'+j), i+1);
                    }
                }
                else if(i == 6) {
                    boardPieces[i][j] = new Pawn('B', char('A'+j), i+1);
                }
                else if (i == 1) {
                    boardPieces[i][j] = new Pawn('W', char('A'+j), i+1);
                }
                else if (i == 0) {
                    if (j == 0) {
                        // creat_piece zal dus een pointer naar een Piece object maken, afhankelijk van de argumenten die worden meegegeven zal het een van de
                        // derived classes zij (Pawn, Knight, Rook, ...)
                        boardPieces[i][j] = new Rook('W', char('A'+j), i+1);
                    }
                    else if (j == 1) {
                        boardPieces[i][j] = new Knight('W', char('A'+j), i+1);
                    }
                    else if (j == 2) {
                        boardPieces[i][j] = new Bishop('W', char('A'+j), i+1);
                    }
                    else if (j == 3) {
                        boardPieces[i][j] = new Queen('W', char('A'+j), i+1);
                    }
                    else if (j == 4) {
                        boardPieces[i][j] = new King('W', char('A'+j), i+1);
                        board->setKingPos(char('A'+j), i+1);
                    }
                    else if (j == 5) {
                        boardPieces[i][j] = new Bishop('W', char('A'+j), i+1);
                    }
                    else if (j == 6) {
                        boardPieces[i][j] = new Knight('W', char('A'+j), i+1);
                    }
                    else if (j == 7) {
                        boardPieces[i][j] = new Rook('W', char('A'+j), i+1);
                    }
                }
                else {
                    boardPieces[i][j] = new Piece('E', char('A'+j), i+1, Piece::EMPTY);
                }
            }
        }
        // update het bord
        board->setBoard(boardPieces);
    };

    bool validPiece(std::vector<std::vector<Piece*>> board, Piece::Type piece_type, char piece_letter_pos, int piece_cipher_pos, char current_player) {
        // heeft de speler een van zijn eigen stukken gekozen?
        if (board[piece_cipher_pos-1][piece_letter_pos-'A']->getType() == piece_type && 
        board[piece_cipher_pos-1][piece_letter_pos-'A']->getColor() == current_player) {
            return true;
        }
        std::cout << "invalid choice, no piece was found at this location.\n";
        return false;
    }

    void getPiece(Board* board, char* curPlayer, bool* stillPlaying) {
        std::vector<std::vector<Piece*>> boardPieces = board->getBoard();
        while (stillPlaying) {
            if (*curPlayer == 'W') {
                std::cout << "white's turn\n";
            }
            else {
                std::cout << "black's turn";
            }
            board->printBoard(boardPieces);

            std::string choice;
            Piece::Type pieceType;
            char pieceLetterPos;
            int pieceCipherPos;
            Piece::Type promotionChoice;

            std::cout << "select piece to move:\n> ";
            std::cin >> choice;

            if (choice == "length") {
                *stillPlaying = false;
                return;
            }
            
            while (choice.length() != 3 && choice.length() != 2) {
                std::cout << "invalid choice.\n";
                std::cout << "select piece to move:\n> ";
                std::cin >> choice;
                if (choice.length() == 3 || choice.length() == 2) {
                    break;
                }
            }
            while (true) {
                if (choice.length() == 2) {
                    pieceType = Piece::PAWN;
                    pieceLetterPos = toupper(choice[0]);
                    pieceCipherPos = choice[1]-'0';
                }

                else if (choice.length() == 3 && toupper(choice[0]) == choice[0]) {
                    switch (choice[0]) {
                        case 'Q':
                            pieceType = Piece::QUEEN;
                            break;
                        case 'R':
                            pieceType = Piece::ROOK;
                            break;
                        case 'B':
                            pieceType = Piece::BISHOP;
                            break;
                        case 'N':
                            pieceType = Piece::KNIGHT;
                            break;
                        case 'K':
                            pieceType = Piece::KING;
                            break;
                    }
                    pieceLetterPos = toupper(choice[1]);
                    pieceCipherPos = choice[2]-'0';
                }

                else if (choice.length() == 3 && toupper(choice[2]) == choice[2]) {
                    pieceType = Piece::PAWN;
                    pieceLetterPos = toupper(choice[0]);
                    pieceCipherPos = choice[1]-'0';
                    switch (choice[0]) {
                        case 'Q':
                            promotionChoice = Piece::QUEEN;
                            break;
                        case 'R':
                            promotionChoice = Piece::ROOK;
                            break;
                        case 'B':
                            promotionChoice = Piece::BISHOP;
                            break;
                        case 'N':
                            promotionChoice = Piece::KNIGHT;
                            break;
                    }
                }

                if (!validPiece(boardPieces, pieceType, pieceLetterPos, pieceCipherPos, *curPlayer) || 
                        ('A' > pieceLetterPos || 'H' < pieceLetterPos) || 
                        (0 > pieceCipherPos || 8 < pieceCipherPos)) {
                    std::cout << "select piece to move:\n> ";
                    std::cin >> choice;
                    if (choice.length() == 2) {
                        pieceType = Piece::PAWN;
                        pieceLetterPos = toupper(choice[0]);
                        if ('A' > pieceLetterPos || 'H' < pieceLetterPos) {
                            std::cout << "invalid move.\n";
                            continue;
                        }
                        pieceCipherPos = choice[1] - '0';
                        if (0 > pieceCipherPos || 8 < pieceCipherPos) {
                            std::cout << "invalid move.\n";
                            continue;
                        }
                    }

                    else if (choice.length() == 3 && toupper(choice[0]) == choice[0]) {
                        switch (choice[0]) {
                            case 'Q':
                                pieceType = Piece::QUEEN;
                                break;
                            case 'R':
                                pieceType = Piece::ROOK;
                                break;
                            case 'B':
                                pieceType = Piece::BISHOP;
                                break;
                            case 'N':
                                pieceType = Piece::KNIGHT;
                                break;
                            case 'K':
                                pieceType = Piece::KING;
                                break;
                        }
                        pieceLetterPos = toupper(choice[1]);
                        pieceCipherPos = choice[2]-'0';
                    }

                    else if (choice.length() == 3 && toupper(choice[2]) == choice[2]) {
                        pieceType = Piece::PAWN;
                        pieceLetterPos = toupper(choice[0]);
                        pieceCipherPos = choice[1]-'0';
                        switch (choice[0]) {
                            case 'Q':
                                promotionChoice = Piece::QUEEN;
                                break;
                            case 'R':
                                promotionChoice = Piece::ROOK;
                                break;
                            case 'B':
                                promotionChoice = Piece::BISHOP;
                                break;
                            case 'N':
                                promotionChoice = Piece::KNIGHT;
                                break;
                        }
                    }
                }

                else {
                    std::string action;
                    std::cout << "select position to move to:\n> ";
                    std::cin >> action;

                    char targetLetterPos = char((action[0]-'a')+'A');
                    int targetCipherPos = action[1] - '0';

                    char pieceColor = boardPieces[pieceCipherPos-1][pieceLetterPos-'A']->getColor();
                    boardPieces[pieceCipherPos-1][pieceLetterPos-'A']->move(board, targetLetterPos, targetCipherPos);
                    boardPieces = board->getBoard();

                    if (('A' > targetLetterPos || 'H' < targetLetterPos) || (0 > targetCipherPos || 8 < targetCipherPos) ||
                    boardPieces[targetCipherPos-1][targetLetterPos-'A']->getType() != pieceType ||
                    boardPieces[targetCipherPos-1][targetLetterPos-'A']->getColor() == 'E' ||
                    boardPieces[targetCipherPos-1][targetLetterPos-'A']->getColor() != pieceColor) {
                        std::cout << "select piece to move:\n> ";
                        std::cin >> choice;
                        if (choice == "quit") {
                            *stillPlaying = false;
                            return;
                        }

                        while (choice.length() != 3 && choice.length() != 2) {
                            std::cout << "invalid choice.\n";
                            std::cout << "select piece to move:\n> ";
                            std::cin >> choice;
                            if (choice.length() == 3 || choice.length() == 2) {
                                break;
                            }
                        }
                        continue;
                    }
                    else {
                        break;
                    }
                }
            }
            if (*curPlayer == 'W') {
                *curPlayer = 'B';
            }
            else {
                *curPlayer = 'W';
            }
            std::cout << "\033[H\033[2J";
        }
    }
};

#endif