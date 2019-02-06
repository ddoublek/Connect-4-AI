//board.h

#ifndef board_h_
#define board_h_

#include <vector>

class Board{
public:
	Board();
	void print();
	void makeMove(int col);
	bool getTurn();
	void isFirst(){turn = checkTurn = myTurn = 0, theirTurn = 1;}
	void isSecond(){turn = checkTurn = myTurn = 1, theirTurn = 0;}
	int getBest();

//private:
	int board[6][7];
	//int tempBoard[6][7];
	int values[7] = {-2, -2, -2, -2, -2 , -2, -2};
	int scores[7] = {-1, -1, -1, -1, -1, -1, -1};
	int turn;
	int myTurn;
	int theirTurn;
	int checkTurn;
	int emptySpace;

	int theirBest(int newRow, int newCol);
	bool checkPlace(int col, int& row, int move);
	int gameOver(int row, int col);
	int checkWin(int row, int col, int rowMod, int colMod);
	void update(int row, int col, int& currAmount, int rowMod, int colMod);
};

#endif