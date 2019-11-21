//board.cpp

#ifndef board_cpp_
#define board_cpp_

#include "board.h"
#include <iostream>
#include <iomanip>

Board::Board(){
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 7; ++j){
			board[i][j] = -1;
		}
	}
	turn = 0;
	emptySpace = 42;
}

void Board::print(){
	std::cout << "***********************************************" << std::endl; 
	std::string boarder = "-----------------------------";
	std::cout << "CURRENT BOARD:" << std::endl;
	for(int i = 5; i >= 0; --i){
		std::cout << boarder << std::endl;
		for(int j = 0; j < 7; ++j){
			
			std::cout << "|";
			std::cout << std::setw(1);
			std::cout << " ";
			if(board[i][j] == -1) std::cout << " ";
			else if(board[i][j] == 0) std::cout << "O";
			else if(board[i][j] == 1) std::cout << "X";
			else std::cout << "*"; //Should not happen
			std::cout << " ";

		}
		std::cout << "|" << std::endl;
	}
	std::cout << boarder << std::endl;
	for(int j = 1; j < 8; ++j){
			
		std::cout << " ";
		std::cout << std::setw(1);
		std::cout << " ";
		std::cout << j;
		std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << boarder << std::endl;
	std::cout << "***********************************************" << std::endl;
}

//When using for getting moves shouldn't be break for else statement but rather be a filler
//alternative is having be a 'placeholder' of win and loss
int Board::checkWin(int row, int col, int rowMod, int colMod){
	int inRow = 1;
	for(int k = -1; k < 2; ++k){
		if(k == 0) continue;
		for(int i = 1; i <= 3; ++i){
			if(row + k * i * rowMod < 0 || row + k * i * rowMod > 5 
			|| col + k * i * colMod < 0 || col + k * i * colMod > 6) break;
				if(board[row + k * i * rowMod][col + k * i * colMod] == turn){					
					++inRow;	
				} 
				else break;
		}
	}
	if(inRow >= 4) return turn;
	else return -1;
}

int Board::gameOver(int row, int col){
	int winner = -1;
	winner = checkWin(row, col, 1, 0);
	if(winner != -1) return winner;
	winner = checkWin(row, col, 0, 1);
	if(winner != -1) return winner;
	winner = checkWin(row, col, 1, 1);
	if(winner != -1) return winner;
	winner = checkWin(row, col, 1, -1);
	if(winner != -1) return winner;
	else return -1;
}

bool Board::checkPlace(int col, int& row, int move){

	while(row < 6 && board[row][col] != -1) ++row;
	if(row == 6) return false;
	board[row][col] = move;
	--emptySpace;
	return true;
}

int Board::makeMove(int col){


	int row = 0;
	bool canPlace = checkPlace(col-1, row, turn);

	if(!canPlace) return -1;

	// std::cout << col << " " <<  row << std::endl;

	if(gameOver(row, col - 1)!= -1) return 1;

	if(turn == 0) ++turn;
	else --turn;



	return 0;

}

void Board::update(int row, int col, int& currAmount, int rowMod, int colMod){

	int yesAmount = 0;
	int noAmount = 0;
	int before = -1;
	int bonus = 0;
	int curr;
	int least = 0;
	int most = 4;
	int failed = 0;
	bool found = false;
	for(int i = -3; i <= 3; i++){

		if(row + rowMod * i < 0 || row + rowMod * i > 5
		 ||col + colMod * i < 0 || col + colMod * i > 6){

			values[3+i] = -2;
			if(!found) {
				least++;
			}
			else most --;
			failed++;
			continue;
		}
		values[3+i] = board[row + rowMod * i][col + colMod * i];
		found = true;
	}


	before = -1;


	for(int i = least; i < most; i++){
		yesAmount = noAmount = bonus = 0;
		for(int j = 0; j < 4; j++){
			curr = values[i+j];

			if(curr == myTurn) ++yesAmount;
			else if(curr == theirTurn) ++noAmount;
			if(before >=0 && before == curr) ++bonus;
			before = curr;

			if(yesAmount > 0 && noAmount > 0) continue;
			//Must make move no matter what
			if(yesAmount == 3 || noAmount == 3){
				currAmount += 999;
				//return;
			}

			currAmount += yesAmount + noAmount + bonus + 1;
			if(noAmount != 0) ++currAmount;

		}
		
	}


}

/*
Problem falls in traps easily
*/

int Board::theirBest(int newRow, int newCol){
	board[newRow][newCol] = myTurn;
	int oldMy = myTurn;
	int oldThier = theirTurn;
	myTurn = oldThier;
	theirTurn = oldMy;
	int bestCol = -1;
	int bestAmount = -1;
	int row; 
	for(int i = 0; i < 7; i++){
		//std::cout << "HI" << std::endl;
		row = 0;
		while(row < 6 && board[row][i] != -1) ++row;
		if(row == 6) continue;
		int currAmount = 0;

		update(row, i, currAmount, 1, 0);
		update(row, i, currAmount, 0 ,1);
		update(row, i, currAmount, 1, 1);
		update(row, i, currAmount, 1, -1);

		//std::cout << i << " " << currAmount << std::endl;

		//if(currAmount > 998) return i;
		scores[i] = currAmount;
		if(currAmount > bestAmount){

			bestCol = i;
			bestAmount = currAmount;
		}
	}
	myTurn = oldMy;
	theirTurn = oldThier;
	board[newRow][newCol] = -1;
	return bestAmount;
}


int Board::getBest(){
	int bestCol = -1;
	int bestAmount = -1;
	int theirAmount = 9999;
	int row; 
	for(int i = 0; i < 7; i++){
		row = 0;
		while(row < 6 && board[row][i] != -1) ++row;
		if(row == 6) continue;
		int currAmount = 0;

		update(row, i, currAmount, 1, 0);
		update(row, i, currAmount, 0 ,1);
		update(row, i, currAmount, 1, 1);
		update(row, i, currAmount, 1, -1);

		//std::cout << i << " " << currAmount << std::endl;

		if(currAmount > 998) return i;
		scores[i] = currAmount;
		// if(currAmount > bestAmount ){
			int theirMax = theirBest(row, i);
			if(theirMax > 998) theirMax *= 3;
			if(2*bestAmount - theirAmount < 2*currAmount - theirMax){
				bestCol = i;
				bestAmount = currAmount;
				theirAmount = theirMax;
			}
			
		//}
	}
	return bestCol;
}


#endif