/*
 * game.h
 *
 *  Created on: 24 dic. 2018
 *      Author: admin
 */

#ifndef GAME_H_
#define GAME_H_

#include "pieces.h"

namespace Chess{
	class ChessGame{
	private:
		Piece* board[8][8];
		std::vector<Piece*> whites;
		std::vector<Piece*> blacks;
		void setBoard(const char* charBoard);

	public:
		ChessGame();
		ChessGame(const char* charBoard);
		Piece* getPieceAt(Position pos);
		const std::string step(Position *origin, Position *destiny);
	};

};//namespace Chess

#endif /* GAME_H_ */
