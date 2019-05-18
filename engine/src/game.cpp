/*
 * game.cpp
 *
 *  Created on: 24 dic. 2018
 *      Author: admin
 */

#include "game.h"

using namespace Chess;
using namespace std;

/**
 * Constructor. Creates a ChessGame with a standard chess game
 * initial positions.
 */
Chess::ChessGame::ChessGame(){
	const char *STANDARD_GAME =
			"rnbqkbnr"
			"pppppppp"
			"00000000"
			"00000000"
			"00000000"
			"00000000"
			"PPPPPPPP"
			"RNBQKBNR";

	this->setBoard(STANDARD_GAME);
}

/**
 * Constructor. Creates a ChessGame object from an 8x8 char array.
 * @param pCharBoard Char array representing game pieces. Each cell is represented by a character,
 * using algebraic notation. Upper case for white pieces, lower case for black ones.
 */
Chess::ChessGame::ChessGame(const char* pCharBoard){
	this->setBoard(pCharBoard);
}

/**
 * Set a ChessGame board from an 8x8 char array.
 * @param pCharBoard Char array representing game pieces. Each cell is represented by a character,
 * using algebraic notation. Upper case for white pieces, lower case for black ones.
 */
void Chess::ChessGame::setBoard(const char* pCharBoard){
	char (*charBoard)[8][8] = (char (*)[8][8])&pCharBoard;
	char piece;

	for(int row=0; row<8; row++){
		for(int column=0; column<8; column++){
			piece = *charBoard[row][column];
			Team team = tolower(piece)==piece? BLACK:WHITE;
			this->board[row][column] = Piece::createPiece(piece, team, Position(row, column), this);
		}
	}
}

/**
 *
 * @param pos
 * @return Pointer to Piece placed at cell indicated by pos. nullptr If the cell is empty.
 */
Piece* Chess::ChessGame::getPieceAt(Position pos) {
	return board[pos.row][pos.column];
}

const std::string Chess::ChessGame::step(Position* origin, Position* destiny) {
	return "hola";
}