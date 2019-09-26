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
		void setBoard(const char* charBoard, bool crlf = false);

	public:
		ChessGame();
		ChessGame(const char* charBoard, bool crlf = false);
		Piece* getPieceAt(Position pos);
	};

};//namespace Chess

#endif /* GAME_H_ */
