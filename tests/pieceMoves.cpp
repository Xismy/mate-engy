/*
 * pieceMoves.cpp
 *
 *  Created on: 4 mar. 2019
 *      Author: admin
 */
#include <gtest/gtest.h>
#include "game.h"

using namespace Chess;

const char *BOARD_0 =
 		"0000k000" //7
		"00000000" //6
		"00000000" //5
		"00000000" //4
		"0P000p00" //3
		"0000P00p" //2
		"000000PP" //1
		"0000000K";//0
//       01234567
/*const Position PAWN_0_1[] = {Position(2,4), Position(3,4), Position(3,5)};
const Position PAWN_0_2[] = {Position(1,3), Position(2,6), Position(3,6), Position(2,7)};
const Position PAWN_0_ENPASSANT = {Position(3, 5), Position(2, 6)};*/

bool checkPieceMoves(ChessGame *game, Position* piecePos, std::vector<Position> *targets){
	Piece *piece = game->getPieceAt(*piecePos);
	std::vector<Position> *moves = piece->listMovements();

	for(auto moveIt=moves->begin(); moveIt!=moves->end(); ++moveIt){
		if(std::find(targets->begin(), targets->end(), *moveIt)!=targets->end())
			return true;
	}

	return true;
}

TEST(MovementCheck, Available){
	ChessGame *game = new ChessGame(BOARD_0);
	Position* piecePos;
	std::vector<Position> *targets;

	piecePos = new Position(2,4);
	targets = new std::vector<Position>();
	targets->push_back(Position(3,4));
	targets->push_back(Position(3,5));
	EXPECT_PRED3(checkPieceMoves, game, piecePos, targets);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

