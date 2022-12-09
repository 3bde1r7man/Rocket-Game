#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

class RocketGame
{
public:
	void runHuman();
	void runPC();
};

class Board {
protected:
	
public:
	vector<vector<char>> board;
	Board() {};
	Board(int size);
	virtual ~Board() {};
	int updateBoard(int x, char symbol);
	bool isWinner(char symbol);
	void displayBoard();
};

class Player {
protected:
	string name;
	char symbol;
public:
	Player(char symbol);
	Player(int order, char symbol);
	virtual ~Player() {};
	string getName();
	char get_symbol();
	virtual void getMove(int& x);

};

class SmartPlayer : public Board {
public:
	//SmartPlayer();
	void getMove(int& x);
	int minimax(Board& b, int depth, bool isMax);
	int GoodorBad(Board& b,char symbol);
	int BestMove(Board& b);
};



