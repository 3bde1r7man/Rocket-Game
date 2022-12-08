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
	void run();
};

class Board {
private:
	vector<vector<char>> board ;
public:
	Board(int size);
	virtual ~Board() {};
	bool updateBoard(int x, char symbol);
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

class SmartPlayer : public Player {
public:
	void getMove(int& x);
};



