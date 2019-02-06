//Start of connect 4

#include <iostream>
#include "board.h"

int main(){

	Board board;

	std::cout << "p" << std::endl;
	

	// Read in an integer so you know will go first.  This will be a 1 if your program goes first, a 2 if your program goes second
	int move_first;
	int best;
	std::cin >> move_first;
	board.print();
	if ( move_first == 1 )
	{
		board.isFirst();
		// if you go first, print out your first move
		best = board.getBest();
		board.makeMove(best+1);
		board.print();
		std::cout << best+1; 

	}
	else if ( move_first == 2 )
	{
		board.isSecond();
		// if you go second, print out a ? so the moderator knows your program is ready
		std::cout << "?";
	}

	int opp_move;
	while ( std::cin >> opp_move )
	{
		if ( opp_move <= 0 || opp_move > 7)
			break;

		board.makeMove(opp_move);
		best = board.getBest();
		board.makeMove(best+1);
		board.print();
		std::cout << best+1; 
	}

	return 0;
}