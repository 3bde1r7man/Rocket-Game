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
	vector<vector<char>> board;
public:
	Board() {};
	Board(int size);
	virtual ~Board() {};
	vector<vector<char>>& getBoard();
	int size();
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
	virtual ~Player() {}
	string getName();
	char get_symbol();
	virtual void getMove(int& x);

};

class SmartPlayer : public Player {
	Board* board;
public:
	SmartPlayer(Board& b);
	virtual ~SmartPlayer() {}
	int minimax(int depth, int alpha, int beta, bool isMax);
	int Good(char symbol);
	bool Bad(char symbol);
};



