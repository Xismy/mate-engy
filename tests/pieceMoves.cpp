/*
 * pieceMoves.cpp
 *
 *  Created on: 4 mar. 2019
 *      Author: admin
 */
#include "gtest/gtest.h"
#include <algorithm>
#include "game.h"
#include <assert.h>
#include <fstream>

using namespace Chess;

const char *PAWNS =
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



class MovementTest : public testing::Test{
private:
	ChessGame* game;
	std::vector<Position> *moves = nullptr;
	std::ifstream *inputFile = nullptr;
	int currentLine = 0;

public:
	MovementTest(){
		game = new ChessGame(PAWNS);
	}

	~MovementTest(){
		delete game;
		delete moves;
		if(inputFile != nullptr)
			inputFile->close();
		delete inputFile;
	}

	void loadFile(const char* fileName){
		inputFile = new std::ifstream(fileName);
		assert(!inputFile->fail());
	}

	bool loadBoard(){
		char board[72];
		delete game;
		assert(inputFile != nullptr);
		inputFile->read(board, 72);

		if(inputFile->fail())
			return false;

		game = new ChessGame(board, true);
		currentLine += 8;

		return true;
	}

	std::vector<Position> nextPiece(){
		assert(inputFile != nullptr);
		std::string line;
		std::getline(*inputFile, line);
		std::stringstream sline(line);
		std::vector<Position> list;

		++currentLine;

		while(!sline.eof()){
			int row, col;

			sline >> std::ws;
			if(sline.eof()) continue;

			sline >> row;
			sline >> col;
			list.push_back(Position(row, col));
		}

		return list;
	}

	void listPieceMovements(Position piecePos){
		Piece *piece = game->getPieceAt(piecePos);
		delete moves;
		moves = piece->listMovements();
	}

	bool pieceCanMove(Position target){
		assert(moves != nullptr);
		return std::find(moves->begin(), moves->end(), target) != moves->end();
	}

	int nMovements(){
		assert(moves != nullptr);
		return moves->size();
	}

	int getLine(){
		return currentLine;
	}

	void runTests(){
		while(loadBoard()){

			std::vector<Position> list = nextPiece();
			while(list.size() != 0){
				Position pos0 = list.at(0);
				listPieceMovements(pos0);
				std::for_each(list.begin()+1, list.end(), [this, &pos0](Position pos){
					EXPECT_TRUE(pieceCanMove(pos)) << "  Cannot move from " << pos0.str()  << " to " << pos.str() << ": line" << getLine() << ".";
				});

				list = nextPiece();
			}
		}
	}
};

TEST_F(MovementTest, PawnCanMove){
	loadFile("C:\\Users\\usuario\\git\\mate-engy\\Test\\pawns_tests");
	runTests();
}

int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

