//Start of connect 4

#include <iostream>
#include "board.h"

int main(){

	Board board;

	
	

	// Read in an integer so you know will go first.  This will be a 1 if your program goes first, a 2 if your program goes second
	int move_first;
	int best;

	while(true){
		std::cout << "Type 1 for AI first, 2 for player first" << std::endl;
		std::cin >> move_first;
		if(move_first == 1 || move_first == 2){
			break;
		}
		else{
			std::cout << "Invalid move: " << move_first << std::endl;
		}
	}

	





	board.print();
	if ( move_first == 1 )
	{
		board.isFirst();
		// if you go first, print out your first move
		best = board.getBest();
		board.makeMove(best+1);
		board.print();

	}
	else if ( move_first == 2 )
	{
		board.isSecond();
	}

	int opp_move;
	while ( std::cin >> opp_move )
	{

		if(opp_move == -1){
			break;
		}

		if ( opp_move <= 0 || opp_move > 7){
			std::cout << "Invalid move: " << opp_move << std::endl;
			continue;
		}

		int valMove = board.makeMove(opp_move);

		if(valMove == -1){
			std::cout << "Invalid move: " << opp_move << std::endl;
			continue;
		}

		if(valMove == 1){
			std::cout << "Game is over, Player has won!" << std::endl;
			break;
		}

		best = board.getBest();
		valMove = board.makeMove(best+1);
		board.print();

		if(valMove == -1){
			std::cerr << "ERROR THIS SHOULD NOT HAPPEN" << std::endl;
			return 1;
		}
		else if(valMove == 1){
			std::cout << "Game is over, AI has won!" << std::endl;
			break;
		}
	}

	return 0;
}