//Andrew Gnott
//Feb 25, 2015
//Class for sodoku puzzle

#include<vector>
#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
using namespace std;

#ifndef PUZZLE_H
#define PUZZLE_H

template <typename T> //template class
class Puzzle{
	public: 
	Puzzle(string = "puzzle.txt",int = 9);
	void display(void);
	void play(void);
	int isValid(int, int, T); //row, col, value
	void changeValue(int, int, T); //row, col, value
	int checkWin(void);

	private: 
	vector<vector <T> > board;
	int boardSize;

};

#endif

template <typename T>
Puzzle<T>::Puzzle(string filename, int size){
	vector<T> tempVec;
	T tempValue;
	ifstream infile;

	//assign board size
	boardSize = size;

	//open file
	infile.open(filename.c_str());
	
	//Read in by line, add line to vector board
	for (int iRow = 0; iRow < boardSize; iRow++){
      for (int iCol = 0; iCol < boardSize; iCol++) {
          infile >> tempValue;
					tempVec.push_back(tempValue);
      }
			board.push_back(tempVec);
			tempVec.clear();
	}
}

template <typename T>
void Puzzle<T>::display(void){
	for(int iRow = 0; iRow < boardSize; iRow++){		

		//print column #'s
		if(iRow==0){
			for(int iPrint=0; iPrint < boardSize; iPrint++){
				//Starting space
				if(iPrint==0)cout << "  ";	
			
				//Print vertical lines every 3 #'s
				if((iPrint%3)==0)cout << "| ";		

				//Print column #		
				cout << iPrint+1 << " ";
			}
			cout << "|" << endl;
			
		}
		
		//print horizontal lines
		if((iRow%3==0) || iRow==boardSize){
			for(int iPrint=0; iPrint < boardSize; iPrint++){
				cout << "---";
			}
			cout << endl;
		}

		for(int iCol = 0; iCol < boardSize; iCol++){
			//print row #'s			
			if(iCol == 0)cout << iRow+1 << " ";			
			
			//print vertical lines
			if((iCol%3)==0)cout << "| ";
		
			//print value of board			
			cout << board[iRow][iCol] << " ";
		}
		cout <<"|" << endl;
	}
}

template <typename T>
int Puzzle<T>::isValid(int row, int col, T value){
	//Check value of entry
	if(value >= boardSize){
		cout << "Invalid: Entry too large." << endl;
		cout << "------------------------------" << endl;
		return 0;
	}else if(value <= 0){
		cout << "Invalid: Entry too small." << endl;
		cout << "------------------------------" << endl;
		return 0;
	}else if(row <= 0 || row >= boardSize){
		cout << "Invalid: Out of bounds." << endl;
		cout << "------------------------------" << endl;
		return 0;
	}else if(row <= 0 || row >= boardSize){
		cout << "Invalid: Out of bounds." << endl;
		cout << "------------------------------" << endl;
		return 0;
	}else if(board[row][col] != 0){
		cout << "Invalid: Position full." << endl;
		cout << "------------------------------" << endl;
		return 0;
	}

	//Check in row
	for(int iCol = 0; iCol < boardSize; iCol++){
		if(board[row][iCol] == value){
			cout << "Invalid: Entry in row." << endl;
			cout << "------------------------------" << endl;
			return 0;
		}
	}

	//Check in col
	for(int iRow = 0; iRow < boardSize; iRow++){
		if(board[iRow][col] == value){
			cout << "Invalid: Entry in column." << endl;
			cout << "------------------------------" << endl;
			return 0;
		}
	}

	//Check in cell
	int changeX;
	int changeY; 

	//change starting check position
	if(row < 3 && col < 3){
		changeX = 0;
		changeY = 0;
	}else if(row < 3 && (col >= 3 && col < 6)){
		changeX = 3;
		changeY = 0; 	
	}else if(row < 3 && (col >= 6 && col < 9)){
		changeX = 6;
		changeY = 0;
	}else if((row >= 3 && row < 6) && col < 3){
		changeX = 0;
		changeY = 3;
	}else if((row >= 3 && row < 6) && (col >= 3 && col < 6)){
		changeX = 3;
		changeY = 3; 	
	}else if((row >= 3 && row < 6) && (col >= 6 && col < 9)){
		changeX = 6;
		changeY = 3;
	}else if(row >= 6 && col < 3){
		changeX = 0;
		changeY = 6;
	}else if(row >= 6 && (col >= 3 && col < 6)){
		changeX = 3;
		changeY = 6; 	
	}else if(row >= 6 && (col >= 6 && col < 9)){
		changeX = 6;
		changeY = 6;
	}

	//Check inside the cell
	for(int iRow = 0+changeY; iRow < 3+changeY; iRow++){
		for(int iCol = 0+changeX; iCol < 3+changeX; iCol++){
			if(board[iRow][iCol]==value){
				cout << "Invalid: Entry in cell." << endl;
				cout << "------------------------------" << endl;
				return 0;
			}
		}
	}

	return 1;
}

template <typename T>
void Puzzle<T>::changeValue(int row, int col, T value){
	board[row][col]=value;
	return;
}

template <typename T>
int Puzzle<T>::checkWin(void){
	T sum;
	int goalSum = 0;
	int size = boardSize;

	//sum up board
	for(int iRow = 0; iRow < boardSize; iRow++){
		for(int iCol = 0; iCol < boardSize; iCol++){
			sum+=board[iRow][iCol];
		}
	}

	//find sum of solved board
	while(size > 0){
		goalSum+=(size--);
	}
	goalSum = boardSize*goalSum;

	//determine if winner
	if(sum == goalSum){
		return 1;
	}else{
		return 0;
	}

}
	

template <typename T>
void Puzzle<T>::play(void){
	T entry;
	int rowPos;
	int colPos;

	cout << "------------------------------" << endl;
	cout << "        Sodoku Solving      " << endl;
	cout << "------------------------------" << endl;
	cout << "   Play a game of sodoku.   " << endl;
	cout << "   Follow the instructions  " << endl;
	cout << "   on the screen to play. 	 " << endl;
	cout << "   Enter a -1 to quit.      " << endl;
	cout << "------------------------------" << endl;

	while(entry != -1){
		display();
		cout << "------------------------------" << endl;
		cout << "Which position would you like " << endl;
		cout << "to enter a number at? " << endl;
		cout << "------------------------------" << endl;
		cout << "  Row: ";
		cin >> rowPos;
		cout << "  Column: ";
		cin >> colPos;
		cout << "  Value: ";
		cin >> entry;
		if(entry == -1)return; //quit if -1
		cout << "------------------------------" << endl;
		
		//determine if move is valid
		if(isValid(rowPos-1,colPos-1,entry)){
			changeValue(rowPos-1,colPos-1,entry);	
		}	
	
		//check if user has wone
		if(checkWin()){
			cout << "You've solved the puzzle!" << endl;
			cout << "------------------------------" << endl;
			return;		
		}

	}

}

