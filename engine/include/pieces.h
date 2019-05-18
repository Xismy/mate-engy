/*
 * pieces.h
 *
 *  Created on: 24 dic. 2018
 *      Author: admin
 */

#ifndef PIECES_H_
#define PIECES_H_

#include <vector>
#include <exception>
#include <sstream>

#define DEBUG 0
#if DEBUG
#define _
#endif

namespace Chess{
	class ChessGame;

	class InvalidPositionException:std::exception{
	private:
		char *msg;
		static int line;
		static std::string file;
	public:
		InvalidPositionException();
		virtual const char *what();
		static void trace(std::string file, int line);
		~InvalidPositionException();
	};

	/**
	 * @brief Piece type.
	 */
	enum Type{
		PAWN,  //!< PAWN
		ROOK,  //!< ROOK
		KNIGHT,//!< KNIGHT
		BISHOP,//!< BISHOP
		QUEEN, //!< QUEEN
		KING   //!< KING
	};

	/**
	 * @brief Piece team.
	 */
	enum Team{
		BLACK,//!< BLACK
		WHITE //!< WHITE
	};

	struct Move{
		int dRow;
		int dColumn;
	};

	/**
	 * Piece position on board expressed in columns [0-7]->[a-h] and rows [0-7]->[1-8].
	 */
	struct Position{
		unsigned int row;
		unsigned int column;

		/**
		 * @brief Position on chess board.
		 * @param row [0-7] maps to [1-8] in algebraic notation.
		 * @param column [0-7] maps to [a-h] in algebraic notation.
		 */
		Position(unsigned int row=0, unsigned int column=0){
			this->row = row;
			this->column = column;

			if(row>7 || column>7)
				throw new InvalidPositionException();
		};

		Position operator+(Move move){
			return {this->row+move.dRow, this->column+move.dColumn};
		}

		bool operator==(Position pos){
			return this->row==pos.row && this->column==pos.column;
		}

	};

	/**
	 * @brief Abstract class representing a chess piece. Contains methods necessary to obtain all possible movements.
	 */
	class Piece{
	protected:
		/**
		 * @brief Piece position.
		 */
		Position position;

		/**
		 * @brief Piece team.
		 */
		Team team;

		/**
		 * Piece type.
		 */
		Type type;

		/**
		 * @brief Game state. Contains an 8x8 array representing each cell of the board and pieces placed on them.
		 */
		ChessGame *game;

		bool brqStep(int row, int column, std::vector<Position> *targets);

	public:
		explicit Piece(Team team, Position pos, ChessGame* game);

		/**
		 * Implements the factory pattern for the Piece class. Allow to instantiate any of the Piece subclasses.
		 * @param team Piece team.
		 * @param pos Piece position.
		 * @param game Game state.
		 * @return Templated subclass of piece.
		 */
		template <class T>
		static Piece *createPiece(Team team, Position pos, ChessGame *game);
		static Piece *createPiece(char piece, Team team, Position pos, ChessGame *game);
		virtual std::vector<Position> *listMovements();
		Team getTeam();
		Type getType();
		virtual ~Piece();
	};

	class Pawn : public Piece{
	private:
		static Position* enPassant;
	public:
		Pawn(Team team, Position pos, ChessGame *game);
		std::vector<Position> *listMovements();
		static bool isEnPassant(Position pos);
		~Pawn();
	};
	/**
	 * @brief
	 */
	class Rook : public Piece{
		/**
		 * @brief
		 * @param team
		 * @param pos
		 * @param game
		 */
	public:
		Rook(Team team, Position pos, ChessGame *game);
		std::vector<Position> *listMovements();
		~Rook();
	};

	class Knight : public Piece{
	public:
		Knight(Team team, Position pos, ChessGame *game);
		std::vector<Position> *listMovements();
		~Knight();
	};

	class Bishop : public Piece{
	public:
		Bishop(Team team, Position pos, ChessGame *game);
		std::vector<Position> *listMovements();
		~Bishop();
	};

	class Queen : public Piece{
	public:
		Queen(Team team, Position pos, ChessGame *game);
		std::vector<Position> *listMovements();
		~Queen();
	};

	class King : public Piece{
	public:
		King(Team team, Position pos, ChessGame *game);
		std::vector<Position> *listMovements();
		~King();
	};

}
;
//namespace Chess


#endif /* PIECES_H_ */
