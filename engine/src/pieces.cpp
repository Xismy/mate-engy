#include "game.h"
#include <iostream>
#include <cstring>

using namespace Chess;

/***Piece***/
template<class T>
Piece *Chess::Piece::createPiece(Team team, Position pos, ChessGame* game) {
	T *piece = new T(team, pos, game);
	return piece;
}

Piece *Chess::Piece::createPiece(char piece, Team team, Position pos, ChessGame* game) {
	switch(tolower(piece)){
		case 'k':
			return createPiece<King>(team, pos, game);
		case 'q':
			return createPiece<Queen>(team, pos, game);
		case 'b':
			return createPiece<Bishop>(team, pos, game);
		case 'n':
			return createPiece<Knight>(team, pos, game);
		case 'r':
			return createPiece<Rook>(team, pos, game);
		case 'p':
			return createPiece<Pawn>(team, pos, game);
		default:
			return nullptr;
	}
}

Team Chess::Piece::getTeam() {
	return this->team;
}

Type Chess::Piece::getType() {
	return this->type;
}

Chess::Piece::Piece(Team team, Position pos, ChessGame* game){
	this->team = team;
	this->position = pos;
	this->type = PAWN;
	this->game = game;
}


/**
 * @brief Used as an auxiliary method for listing movements with Bishops, Rooks and Queens. This
 * three pieces performs movements along one axis (vertical, horizontal or diagonal). The
 * brqStep allows to know if a cell can be occupied by the piece and add the position to the
 * targets vector when it does. If the cell is empty returns true, indicating that a farther
 * movement in the same direction is feasible.
 *
 * @param row Row in the board of the checked target cell.
 * @param column Column in the board of the checked target cell.
 * @param targets Targets list where the movement should be added if it is possible.
 * @return true when a farther movement could be possible.
 */
bool Chess::Piece::brqStep(int row, int column, std::vector<Position> *targets){
	Position pos(row, column);
	Piece* piece;

	if(!(piece = game->getPieceAt(position)) || piece->getTeam()!=this->team)
		targets->push_back(pos);

	return piece != nullptr;
}

Chess::Piece::~Piece() {
}

std::vector<Position> *Chess::Piece::listMovements() {
	return nullptr;
}


/***Pawn***/
Position *Chess::Pawn::enPassant = nullptr;

Chess::Pawn::Pawn(Team team, Position pos, ChessGame* game) : Piece(team, pos, game){
	this->type = PAWN;
}

std::vector<Position> *Chess::Pawn::listMovements() {
	std::vector<Position> *targets = new std::vector<Position>();
	Position aux = this->position + (this->team==WHITE?Move{1,0}:Move{-1,0});
	Piece *piece = this->game->getPieceAt(aux);

	if(!piece)
		targets->push_back(aux);

	if(		(this->position.row==1 && this->team==WHITE) ||
			(this->position.row==6 && this->team==BLACK)){

		aux = this->position + (this->team==WHITE?Move{2,0}:Move{-2,0});
		piece = this->game->getPieceAt(aux);

		if(!piece)
			targets->push_back(aux);

	}

	aux = this->position + (this->team==WHITE?Move{1,1}:Move{-1,-1});
	piece = this->game->getPieceAt(aux);
	if((piece && piece->getTeam()!=this->team) || Pawn::isEnPassant(aux))
		targets->push_back(aux);

	aux = this->position + (this->team==WHITE?Move{1,-1}:Move{1,1});
	piece = this->game->getPieceAt(aux);
	if((piece && piece->getTeam()!=this->team) || Pawn::isEnPassant(aux))
		targets->push_back(aux);

	return targets;
}

bool Chess::Pawn::isEnPassant(Position pos){
	return enPassant && *enPassant==pos;
}

Chess::Pawn::~Pawn() {
}

Chess::Rook::Rook(Team team, Position pos, ChessGame* game) : Piece(team, pos, game){
	this->type = ROOK;
}

std::vector<Position> *Chess::Rook::listMovements() {
	std::vector<Position> *targets = new std::vector<Position>();

	int row = this->position.column;
	int column = this->position.column;
	bool pieceReached = false;

	while(row<8 && !pieceReached){
		pieceReached = brqStep(++row, column, targets);
	}

	row = this->position.column;

	while(row>=0 && !pieceReached){
		pieceReached = brqStep(--row, column, targets);
	}

	row = this->position.column;
	column = this->position.column;

	while(column<8 && !pieceReached){
		pieceReached = brqStep(row, ++column, targets);
	}

	column = this->position.column;

	while(column>=0 && !pieceReached){
		pieceReached = brqStep(row, --column, targets);
	}

	return targets;
}

Chess::Rook::~Rook() {
}

Chess::Knight::Knight(Team team, Position pos, ChessGame* game) : Piece(team, pos, game){
	this->type = KNIGHT;
}

std::vector<Position> *Chess::Knight::listMovements() {
	const int DX[] = {-2, -2, -1, -1,  1,  1,  2,  2};
	const int DY[] = {-1,  1, -2,  2, -2,  2, -1,  1};
	std::vector<Position> *targets = new std::vector<Position>();

	int row = this->position.column;
	int col = this->position.column;

	for(int i = 0; i<8; i++){
		int nextRow = row + DY[i];
		int nextCol = col + DX[i];
		Position nextPos;
		Piece *piece;

		if(nextRow>0 && nextRow<8 && nextCol>0 && nextCol<8){
			nextPos = Position(nextRow, nextCol);
			if(!(piece = game->getPieceAt(nextPos)) || piece->getTeam()!=this->team)
				targets->push_back(nextPos);
		}
	}

	return targets;
}

Chess::Knight::~Knight() {
}

Chess::Bishop::Bishop(Team team, Position pos, ChessGame* game) : Piece(team, pos, game){
	this->type = BISHOP;
}

std::vector<Position> *Chess::Bishop::listMovements() {
	std::vector<Position> *targets = new std::vector<Position>();

	int row = this->position.column;
	int column = this->position.column;
	bool pieceReached = false;

	while(row<8 && column<8 && !pieceReached){
		pieceReached = brqStep(++row, ++column, targets);
	}

	row = this->position.column;
	column = this->position.column;

	while(row<8 && column>=0 && !pieceReached){
		pieceReached = brqStep(++row, --column, targets);
	}

	row = this->position.column;
	column = this->position.column;

	while(row>=0 && column<8 && !pieceReached){
		pieceReached = brqStep(--row, ++column, targets);
	}

	row = this->position.column;
	column = this->position.column;

	while(row>=0 && column>=0 && !pieceReached){
		pieceReached = brqStep(--row, --column, targets);
	}

	return targets;
}

Chess::Bishop::~Bishop() {
}

Chess::Queen::Queen(Team team, Position pos, ChessGame* game) : Piece(team, pos, game){
	this->type = QUEEN;
}

std::vector<Position> *Chess::Queen::listMovements() {
	std::vector<Position> *moves = ((Rook*)this)->listMovements();
	std::vector<Position> *moveBishop = ((Bishop*)this)->listMovements();

	moves->insert(moves->end(), moveBishop->begin(), moveBishop->end());
	return moves;
}

Chess::Queen::~Queen() {
}

Chess::King::King(Team team, Position pos, ChessGame* game) : Piece(team, pos, game){
	this->type = KING;
}

std::vector<Position> *Chess::King::listMovements() {
	std::vector<Position> *moves = ((Rook*)this)->listMovements();
	std::vector<Position> *moveBishop = ((Bishop*)this)->listMovements();

	moves->insert(moves->end(), moveBishop->begin(), moveBishop->end());
	return moves;
}

Chess::King::~King() {
}

std::string Chess::InvalidPositionException::file("");
int Chess::InvalidPositionException::line = 0;

Chess::InvalidPositionException::InvalidPositionException(){
	std::string str_msg =
			"ERROR: Invalid Position created.\n"
#if DEBUG
			"	In file "+file+" at line "+std::to_string(line)+"."
#endif
			;
	int size = str_msg.size();
	msg = (char*)malloc(size);
	strncpy(msg,str_msg.c_str(), size);
}

const char* Chess::InvalidPositionException::what(){
	return msg;
}

void Chess::InvalidPositionException::trace(std::string file, int line){
	Chess::InvalidPositionException::file = file;
	Chess::InvalidPositionException::line = line;
}

Chess::InvalidPositionException::~InvalidPositionException(){
	free(msg);
}


