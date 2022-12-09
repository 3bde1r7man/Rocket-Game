#include "RocketGame.h"
//--------------------RocketGame-------------
void RocketGame::runHuman()
{
	int n;
	cout << "Please enter the size of board: ";
	cin >> n;
	Board rocket(n);
	int x;
	Player players[2] = { Player(1, '>'), Player(2, 'v') };
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

void RocketGame::runPC()
{
	int n;
	cout << "Please enter the size of board: ";
	cin >> n;
	Board rocket(n);
	int x;
	Player player(1, '>');
	SmartPlayer PC(rocket);
	rocket.displayBoard();
	while (true) {
		player.getMove(x);
		while (rocket.updateBoard(x, player.get_symbol()) == 2)
		{
			player.getMove(x);
		}
		rocket.displayBoard();
		if (rocket.isWinner(player.get_symbol())) {
			cout << player.getName() << " wins\n";
			return;
		}
		else if (rocket.isWinner('v')) {
			cout << "Computer wins\n";
			return;
		}
		x = PC.BestMove();
		while (rocket.updateBoard(x, 'v') == 2)
		{
			x = PC.BestMove();
		}
		rocket.displayBoard();
		if (rocket.isWinner(player.get_symbol())) {
			cout << player.getName() << " wins\n";
			return;
		}
		else if (rocket.isWinner('v')) {
			cout << "Computer wins\n";
			return;
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

vector<vector<char>>& Board::getBoard()
{
	return board;
}

int Board::size()
{
	return board.size();
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
SmartPlayer::SmartPlayer(Board& b): Player('v')
{
	name = "Computer";
	board = &b;
}


int SmartPlayer::GoodorBad(char symbol)
{
	int check{ 0 };
	if (symbol == 'v') {

		for (int i = 1; i < board->size() - 2; i++)
		{
			if (board->getBoard()[board->size() - 1][i] == board->getBoard()[board->size() - 1][i + 1] && board->getBoard()[board->size() - 1][i] == 'v') {
				check++;
			}
		}
		if (check == board->size() - 3) {
			return 20;
		}
		else
		{
			for (int i = 0; i < board->size() - 1; i++)
			{
				for (int j = 0; j < board->size() - 1; j++)
				{
					if (board->getBoard()[i][j] == 'v') {
						if (board->getBoard()[i + 1][j] == '>' && board->getBoard()[i + 2][j] == ' ' && i + 2 <= board->size() - 1 && i + 2 == board->size() - 1) {
							return 10;
						}
						else if (board->getBoard()[i + 1][j] == ' ' && i + 1 == board->size() - 1) {
							return 10;
						}
						else if (j - 1 >= 0 && board->getBoard()[i + 1][j] == ' ' && board->getBoard()[i + 1][j - 1] == '>' && board->getBoard()[i + 1][j + 1] == 'v') {
							return 10;
						}
						else if (j - 2 >= 0 && board->getBoard()[i + 1][j] == ' ' && board->getBoard()[i + 1][j - 2] == '>' && board->getBoard()[i + 1][j - 1] == 'v') {
							return 10;
						}
						
					}
					else {
						continue;
					}

				}
			}
		}
	}
	else
	{
		for (int i = 0; i < board->size() - 2; i++)
		{
			if (board->getBoard()[i][board->size() - 1] == board->getBoard()[i + 1][board->size() - 1] && board->getBoard()[i][board->size() - 1] == '>') {
				check++;
			}
		}
		if (check == board->size() - 3) {
			return -20;
		}
		else
		{
			for (int i = 0; i < board->size() - 1; i++)
			{
				for (int j = 0; j < board->size() - 1; j++)
				{
					if (board->getBoard()[j][i] == '>') {
						if (board->getBoard()[j][i + 1] == 'v' && board->getBoard()[j][i + 2] == ' ' && j + 2 <= board->size() - 1 && i + 2 == board->size() - 1) {
							return -10;
						}
						else if (board->getBoard()[j][i + 1] == ' ' && i + 1 == board->size() - 1) {
							return -10;
						}
						else if (j - 1 >= 0 && board->getBoard()[j][i + 1] == ' ' && board->getBoard()[j - 1][i + 1] == 'v' && board->getBoard()[j + 1][i + 1] == '>') {
							return -10;
						}
						else if (j - 2 >= 0 && board->getBoard()[j][i + 1] == ' ' && board->getBoard()[j - 2][i + 1] == 'v' && board->getBoard()[j - 1][i + 1] == '>') {
							return -10;
						}
						
					}
					else
					{
						continue;
					}

				}
			}
		}
	}

	return	0;
}

int SmartPlayer::BestMove()
{
	int x{ -1 }, bestval{ -1000 };
	vector<vector<char>> cpboard ;
	for (int i = 1; i < board->size() - 1; i++)
	{
		cpboard = board->getBoard();
		if (board->updateBoard(i, 'v') != 1) {
			continue;
		}
		else
		{
			int move = minimax(0, 1);
			board->getBoard() = cpboard;
			if (move > bestval) {
				x = i;
				bestval = move;
			}
		}
		
		/*if (move == 0) {
			int move = 1 + rand() % (board->size() - 2);
			while (board->updateBoard(move, 'v') == 0)
			{
				move = 1 + rand() % (board->size() - 2);
			}
			x = move;
			bestval = 0;
			board->getBoard() = cpboard;
		}*/
		
	}
	return x;
}



int SmartPlayer::minimax(int depth, bool isMax)
{
	vector<vector<char>> cpboard = board->getBoard();

	if (isMax) {
		int best = -1000;
		int score = GoodorBad('v');
		if (score == 10) {
			return score;
		}
		else if (score == -10)
		{
			return score;
		}
		else {
			
			int move = 1 + rand() % (board->size() - 2);
			while (board->updateBoard(move, 'v') == 0)
			{
				move = 1 + rand() % (board->size() - 2);
			}
			int score = GoodorBad('v');
			return score;
		}
		for (int i = 1; i < board->size() - 1; i++)
		{
			board->updateBoard(i, 'v');
			best = max(best, minimax(depth + 1, !isMax));
			board->getBoard() = cpboard;
		}
		return best;
	}
	else
	{
		int best = 1000;
		int score = GoodorBad('>');
		if (score == 10) {
			return score;
		}
		else if (score == -10)
		{
			return score;
		}
		else {
			int move = 1 + rand() % (board->size() - 2);
			while (board->updateBoard(move, '>') == 0)
			{
				move = 1 + rand() % (board->size() - 2);
			}
			int score = GoodorBad('>');
			return score;
		}
		for (int i = 1; i < board->size() - 1; i++)
		{
			board->updateBoard(i, '>');
			best = min(best, minimax(depth + 1, !isMax));
			board->getBoard() = cpboard;
		}
		return best;
	}
	
}
