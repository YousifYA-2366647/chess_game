#ifndef CHESS_GAME_CPP
#define CHESS_GAME_CPP
#include <string>
#include "player_class.hpp"


int main() {
    std::cout << "\033[H\033[2J";

    bool stillPlaying = true;

    Board* chessBoard = new Board();
    Rules* ruleSet = new Rules();
    Player* player = new Player();

    player->makeBoard(chessBoard);

    std::vector<std::vector<Piece*>> boardPieces = chessBoard->getBoard();
    char currentPlayer = 'W';
    player->getPiece(chessBoard, &currentPlayer, &stillPlaying);

    delete chessBoard;
    return 0;
}

#endif