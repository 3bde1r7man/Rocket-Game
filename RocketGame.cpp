#include "RocketGame.h"
//--------------------RocketGame-------------
void RocketGame::run()
{
	int n;
	cout << "Please enter the size of board: ";
	cin >> n;
	Board rocket(n);
	int x;
	Player players[2] = { Player(1, 'v'), Player(2, '>') };
	rocket.displayBoard();
	while (true) {
		for (int i : {0, 1}) {
			players[i].getMove(x);
			while (rocket.updateBoard(x, players[i].get_symbol()) == 2)
			{
				players[i].getMove(x);
			}
			/*rocket.updateBoard(x, players[i].get_symbol());*/
			rocket.displayBoard();
			if (rocket.isWinner(players[i].get_symbol())) {
				cout << players[i].getName() << " wins\n";
				return;
			}
		}
	}
}

//--------------------Board-----------------
Board::Board(int size) {
    board = vector<vector<char>>(size, vector<char>(size, ' '));
	for (int i = 1; i < size - 1; i++)
	{
		board[0][i] = 'v';
		board[i][0] = '>';
	}
}

int Board::updateBoard(int x, char symbol)
{
	if (symbol == 'v') 
	{
		if (board[board.size() - 1][x] == 'v') {
			return 2;
		}
		else {
			for (int i = 0; i < board.size() - 1; i++)
			{
				if (board[i][x] == 'v') {
					if (board[i + 1][x] == ' ') {
						board[i][x] = ' ';
						board[i + 1][x] = 'v';
						return 1;
					}
					else if (board[i + 1][x] == '>' && board[i + 2][x] == ' ' && i != board.size() - 1) {
						board[i][x] = ' ';
						board[i + 2][x] = 'v';
						return 1;
					}
					else {
						return 0;
					}
				}
				else
				{
					continue;
				}
			}
		}
		
	}
	else
	{
		if (board[x][board.size() - 1] == '>') {
			return 2;
		}
		else {
			for (int i = 0; i < board.size() - 1; i++)
			{
				if (board[x][i] == '>') {
					if (board[x][i + 1] == ' ') {
						board[x][i] = ' ';
						board[x][i + 1] = '>';
						return 1;
					}
					else if (board[x][i + 1] == 'v' && board[x][i + 2] == ' ' && i != board.size() - 1) {
						board[x][i] = ' ';
						board[x][i + 2] = '>';
						return 1;
					}
					else {
						return 0;
					}
				}
				else
				{
					continue;
				}
			}
		}
		
	}
	return 0;
}


bool Board::isWinner(char symbol)
{
	int check{ 0 };
	if (symbol == 'v') {
		for (int i = 1; i < board.size() - 2; i++)
		{
			if (board[board.size() - 1][i] == board[board.size() - 1][i + 1] && board[board.size() - 1][i] == 'v') {
				check++;
			}
		}
	}
	else
	{
		for (int i = 1; i < board.size() - 2; i++)
		{
			if (board[i][board.size() - 1] == board[i + 1][board.size() - 1] && board[i][board.size() - 1] == '>') {
				check++;
			}
		}
	}
	if (check == board.size() - 3) {
		return 1;
	}
	return	0;
}

void Board::displayBoard()
{
	cout << "               ";
	for (int i = 0; i < board.size()-2; i++)
	{
		cout << i + 1 << "    ";
	}
	cout << '\n';
	for (int i = 0; i < board.size()+1; i++)
	{
		cout << "-----+";
	}
	cout << '\n';
	for (int i = 0; i < board.size(); i++)
	{
		if (i == 0 || i ==  board.size() - 1) {
			cout << "     ";
		}
		else
		{
			cout << i  << "    ";
		}
		for (int j = 0; j < board.size(); j++)
		{
			cout << "|  " << board[i][j] << "  ";
		}
		cout << "|\n";
	}
	for (int i = 0; i < board.size()+1; i++)
	{
		cout << "-----+";
	}
	cout << '\n';
}

//--------------------Player---------------------
Player::Player(int order, char symbol) {
	cout << "Welcome player " << order << endl;
	cout << "Please enter your name: ";
	cin >> name;
	this->symbol = symbol;
}

Player::Player(char symbol) {
	name = "Computer";
	this->symbol = symbol;
}

string Player::getName()
{
	return name;
}

void Player::getMove(int& x)
{
	cout << "\nPlease enter your move: ";
	cin >> x;
}

char Player::get_symbol() {
	return symbol;
}

//-----------------------SmartPlayer-----------------
void SmartPlayer::getMove(int& x)
{

}
