//Andrew Gnott
//Feb. 25, 2015
//Driver program for sodoku

#include<iostream>
#include"Puzzle.h"
using namespace std;

int main(){
	Puzzle<int> Game1("puzzle.txt",9);

	Game1.play();
}
