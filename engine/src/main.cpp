#include "game.h"
#include <string.h>
#include <iostream>

using namespace Chess;
using namespace std;

int main(){
	ChessGame *game = new ChessGame();
	bool checkMate = false;
	string playerMove;
	Position *origin, *destiny;

	do{
		cin >> playerMove;
		try{
			origin  = new Position(playerMove[1]-'a', playerMove[0]-'1');
			destiny = new Position(playerMove[3]-'a', playerMove[2]-'1');
			cout << game->step(origin, destiny);
		}
		catch(InvalidPositionException *ipe){
			cout <<ipe->what();
			delete ipe;
			exit(1);
		}

	}while(!checkMate);
}
