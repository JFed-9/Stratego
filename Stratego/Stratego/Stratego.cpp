// Stratego.cpp : Defines the entry point for the console application.
//
/*
                      j
  -----------------------------------------
  |0,0|0,1|0,2|0,3|0,4|0,5|0,6|0,7|0,8|0,9|
  |---------------------------------------|
  |1,0|   |   |   |   |   |   |   |   |   |
  |---------------------------------------|
  |2,0|   |   |   |   |   |   |   |   |   |
  |---------------------------------------|
  |3,0|   |   |   |   |   |   |   |   |   |
  |---------------------------------------|
  |4,0|   | ~ | ~ |   |   | ~ | ~ |   |   |
i |---------------------------------------|
  |5,0|   | ~ | ~ |   |   | ~ | ~ |   |   |
  |---------------------------------------|
  |6,0|   |   |   |   |   |   |   |   |   |
  |---------------------------------------|
  |7,0|   |   |   |   |   |   |   |   |   |
  |---------------------------------------|
  |8,0|   |   |   |   |   |   |   |   |   |
  |---------------------------------------|
  |9,0|   |   |   |   |   |   |   |   |   |
  |---------------------------------------|
*/
#include "stdafx.h"
#include "Master.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct piece
{
	int value; //1 2 3 4 5 6 7 8 9  0     10     -1   12     13
			   //                  Bomb   Spy   flag Water Ground
	int owner; //Which player owns the piece
	bool revealed;
	piece();
	piece(int val, int own, bool rev);
	int attack(piece& other);
	bool canMove(int x, int y);
	int tryMove(int a, int b, int x, int y);
};

int win = 0; 
piece board[10][10];
const string numbers = "0123456789";
const string pieces[13] = { "Flag","Bomb","1","2","3","4","5","6","7","8","9","Spy" };
const int frequency[13] = { 1,     6,   1,  1,  2,  3,  4,  4,  4,  5,  8,   1 };
consolewindow console;
bool inputting;
string recentattack;

char interpret(int value);
void displayboard(int player);
int evaluateInput(string str, int player);

int main()
{
	system("mode 1000");
	system("title Stratego");
	console.setColor("white");
	inputting = true;
	recentattack = "";
	//Reset the board
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			board[i][j] = piece(13, 0, true);
	for (int i : {4, 5})
		for (int j : {2, 3, 6, 7})
			board[i][j] = piece(12, 0, true);
	//Dummy variables
	string str, dummy;
	int num;
	double num2;
	char ch;


	//Input each player
	for (int player = 1; player <= 2; player++)
	{
		cout << "Input player " << player << "'s setup\n";
		system("pause");
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < frequency[i]; j++)
			{
				system("cls");
				cout << "The form for entering pieces will be as follows:\n[X Coordinate],[Y Coordinate]\n";
				displayboard(player);
				cout << "Enter your placement for your " + pieces[i] << " :";
				cin >> str;
				getline(cin, dummy);
				//Evaluate and save
				/*
				*              RULES
				*1. Cannot  be  on  another  piece
				*2. Must   be   in  players  field
				*3. Must be 2 digits, each between
				*   0 and 9
				*4. Must not have any other issues
				*   with  input  such  as trailing
				*   data
				*/
			validate:
				int errorlevel = evaluateInput(str,player);
				if (errorlevel == 0)
					goto save;
				switch (errorlevel)
				{
				case 1:
					cout << "Error, location already filled\n";
					break;
				case 2:
					cout << "Error, location not in bounds\n";
					break;
				case 3:
					cout << "Error, input was not correctly identified\n";
					break;
				}
				cout << "Please enter a new input: ";
				cin >> str;
				goto validate;
			save:
				board[str[0] - '0'][str[2] - '0'] = piece(i - 1, player, false);
			}
		}
		system("cls");
		displayboard(player);
		system("pause");
		system("cls");
	}
	inputting = false;
	//Begin game
	int player = 1;
	while (win == 0)
	{
		system("cls");
		cout << "Player " << player << "'s turn\n";
		system("pause");
		system("cls");
		console.setColor("yellow", "red");
		cout << recentattack;
		console.setColor();
		recentattack = "";
		displayboard(player);
		cout << "Enter the coordinates of the piece you wish to move: ";
	input:
		cin >> str;
		getline(cin, dummy);
		if (str.length() != 3 || str[1] != ',' || numbers.find(str[0]) == string::npos || numbers.find(str[2]) == string::npos)
		{
			cout << "Error, please enter coordinates again: ";
			goto input;
		}
		int x = str[0] - '0';
		int y = str[2] - '0';
		if (board[x][y].owner != player)
		{
			cout << "This location is not occupied by your unit.\nPlease enter a new location: ";
			goto input;
		}
		if (!(board[x][y].canMove(x,y)))
		{
			cout << "This piece cannot move anywhere, select a different piece: ";
			goto input;
		}
		cout << "Enter the destination coordinates: ";
	inputdest:
		cin >> str;
		if (str.length() != 3 || str[1] != ',' || numbers.find(str[0]) == string::npos || numbers.find(str[2]) == string::npos)
		{
			cout << "Error, please enter coordinates again: ";
			goto input;
		}
		if (board[x][y].tryMove(x, y, str[0] - '0', str[2] - '0') == -1)
		{
			cout << "Cannot move there, new location: ";
			goto inputdest;
		}
		player = (player == 1) ? 2 : 1;
	}
	system("cls");
	cout << "Game Over!!\n\nPlayer " << win << " wins!";
	system("pause");
	return 0;
}

void displayboard(int player) {
	if (player == 3)
	{
		cout << "    0   1   2   3   4   5   6   7   8   9  " << endl
			<< "  -----------------------------------------" << endl
			<< "0 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "1 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "2 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "3 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "4 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "5 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "6 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "7 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "8 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl
			<< "9 | X | X | X | X | X | X | X | X | X | X |" << endl
			<< "  |---------------------------------------|" << endl;
	}
	if (player == 1 || player == 2)
	{
		cout << "    0   1   2   3   4   5   6   7   8   9  " << endl;
		if (player == 2 && inputting)
			console.setColor("Green");
		else
			console.setColor();
		cout << "  -----------------------------------------" << endl;
		for (int i = 0; i < 10; i++)
		{
			//0 | X | X | X | X | X | X | X | X | X | X |
			if (player == 2 && i < 4 || player == 1 && i > 5 && inputting)
				console.setColor("Green");
			else
				console.setColor();
			cout << i << " | ";
			for (int j = 0; j < 10; j++)
			{
				piece temp = board[i][j];
				if (!inputting)
				{
					if (temp.owner == player)
						console.setColor("green");
					else if (temp.owner != 0)
						console.setColor("red");
					else
						console.setColor();
				}
				if (temp.revealed || temp.owner == player || temp.value == 12 || temp.value == 13)
				{
					if (temp.value == 12)
					{
						console.setColor("blue");
						cout << interpret(temp.value);
						console.setColor();
					}
					else
						cout << interpret(temp.value);
				}
				else
					cout << "X";
				if (temp.revealed)
					board[i][j].revealed = false;
				if (!inputting) { console.setColor(); }
				if (j == 9)
					cout << " |";
				else
					cout << " | ";
			}
			cout << endl << "  |---------------------------------------|" << endl;
			console.setColor();
		}
	}
}
char interpret(int value)
{
	//1 2 3 4 5 6 7 8 9  0     10     -1   12     13
	//                  Bomb   Spy   flag Water Ground
	if (value > 0 && value < 10)
		return value + '0';
	switch (value)
	{
	case 0:
		return '@';
	case 10:
		return 'S';
	case -1:
		return 'X';
	case 12:
		return '~';
	case 13:
		return ' ';
	}
	return ' ';
}
int evaluateInput(string str,int player)
{
	if (str.length() != 3 || numbers.find(str[0]) == string::npos || numbers.find(str[2]) == string::npos || str[1] != ',')
		return 3;
	int x = str[0] - '0';
	int y = str[2] - '0';
	if (board[x][y].value != 13)
		return 1;
	if (x < 0 || x > 9 || y < 0 || y > 9)
		return 2;
	if ((player == 1 && x < 6) || (player == 2 && x > 4))
		return 2;
	return 0;
}
piece::piece(int val, int own, bool rev) : value(val), owner(own), revealed(rev) { };
piece::piece() : value(13), owner(0), revealed(true) { };
int piece::attack(piece &other)
{
	other.revealed = true;
	revealed = true;
	if (other.value == value)
	{
		return 4; //Tie
	}
	else if (other.value > 1 && other.value < 10)
	{
		return (value < other.value) ? 1 : 0; //Return 1 if win, 0 if lose
	}
	else if (other.value == 1)
	{
		if (value == 10)
			return 1;
		else
			return 0;
	}
	else {
		if (other.value == 0)
			if (value == 8)
				return 1; //win
			else
				return 0; //lose
		if (other.value == 10)
			return 10; //win
		if (other.value == 11)
			return 2; //game
	}
	return 3; //error
}
bool piece::canMove(int x, int y)
{
	if (value == 0 || value == -1)
		return false;
	//Check for wall
	if (x == 0)
	{
		if (y == 0)
		{
			//---
			//|OX
			//|XX
			if (board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner&&board[x][y + 1].owner == owner)
				return false;
		}
		if (y == 9)
		{
			//---
			//XO|
			//XX|
			if (board[x + 1][y].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x][y - 1].owner == owner)
				return false;
		}
		//---
		//XOX
		//XXX
		if (board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner&&board[x + 1][y + 1].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x + 1][y].owner == owner)
			return false;
	}
	if (x == 9)
	{
		if (y == 0)
		{
			//|XX
			//|OX
			//---
			if (board[x][y + 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner)
				return false;
		}
		if (y == 9)
		{
			//XX|
			//XO|
			//---
			if (board[x - 1][y].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x][y - 1].owner == owner)
				return false;
		}
		//XXX
		//XOX
		//---
		if (board[x - 1][y].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner)
			return false;
	}
	if (y == 0)
	{
		//|XX
		//|OX
		//|XX
		if (board[x][y + 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner)
			return false;
	}
	if (y == 9)
	{
		//XX|
		//XO|
		//XX|
		if (board[x - 1][y].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y - 1].owner == owner)
			return false;
	}
	//XXX
	//XOX
	//XXX
	if (x != 9 && x != 0 && y != 9 && y != 0)
	{
		if (board[x][y - 1].owner == owner && board[x][y + 1].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner)
			return false;
	}

	//Check for water
	if (x == 3)
	{
		if (y == 1 || y == 5)
		{
			//XXX
			//XOX
			//XX~
			if (board[x][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner)
				return false;
		}
		if (y == 2 || y == 6)
		{
			//XXX
			//XOX
			//X~~
			if (board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner)
				return false;
		}
		if (y == 3 || y == 7)
		{
			//XXX
			//XOX
			//~~X
			if (board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner&&board[x + 1][y + 1].owner == owner)
				return false;
		}
		if (y == 4 || y == 8)
		{
			//XXX
			//XOX
			//~XX
			if (board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner)
				return false;
		}
	}
	if (x == 4)
	{
		if (y == 1 || y == 5)
		{
			//XXX
			//XO~
			//XX~
			if (board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x + 1][y].owner == owner)
				return false;
		}
		if (y == 4 || y == 8)
		{
			//XXX
			//~OX
			//~XX
			if (board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y + 1].owner == owner&&board[x + 1][y + 1].owner == owner&&board[x + 1][y].owner == owner)
				return false;
		}
	}
	if (x == 5)
	{
		if (y == 1 || y == 5)
		{
			//XX~
			//XO~
			//XXX
			if (board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x + 1][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x + 1][y].owner == owner)
				return false;
		}
		if (y == 4 || y == 8)
		{
			//~XX
			//~OX
			//XXX
			if (board[x + 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y + 1].owner == owner&&board[x + 1][y + 1].owner == owner&&board[x + 1][y].owner == owner)
				return false;
		}
	}
	if (x == 6)
	{
		if (y == 1 || y == 5)
		{
			//XX~
			//XOX
			//XXX
			if (board[x][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x + 1][y + 1].owner == owner)
				return false;
		}
		if (y == 2 || y == 6)
		{
			//X~~
			//XOX
			//XXX
			if (board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner&&board[x - 1][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner&&board[x + 1][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner)
				return false;
		}
		if (y == 3 || y == 7)
		{
			//~~X
			//XOX
			//XXX
			if (board[x + 1][y - 1].owner == owner&&board[x + 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner&&board[x + 1][y + 1].owner == owner)
				return false;
		}
		if (y == 4 || y == 8)
		{
			//~XX
			//XOX
			//XXX
			if (board[x + 1][y - 1].owner == owner&&board[x - 1][y].owner == owner&&board[x - 1][y + 1].owner == owner&&board[x][y - 1].owner == owner&&board[x][y + 1].owner == owner&&board[x + 1][y].owner == owner&&board[x + 1][y + 1].owner == owner)
				return false;
		}
	}
	return true; //Yay!
}
int piece::tryMove(int a, int b, int x, int y)
{
	if (value != 9)
	{
		if (!(abs(x - a) <= 1 && abs(y - b) <= 1))
		{
			return -1;
		}
	}
	else
	{
		if (y-b != 0)
			if (!(abs((x - a) / (y - b)) == 1 || abs((x - a) / (y - b)) == 0))
			{
				return -1;
			}
		if (!(abs(x - a) <= 1 && abs(y - b) <= 1))
		{
			if (board[x][y].value != 13)
				return -1;
		}
	}
	if (board[x][y].value == 13)
	{
		board[x][y] = board[a][b];
		board[a][b] = piece(13, 0, true);
		return 1;
	}
	if (board[x][y].owner == owner || board[x][y].value == 12)
	{
		return -1;
	}
	if (board[x][y].owner != owner&&board[x][y].owner != 0)
	{
		//Attack
		int attackresult = attack(board[x][y]);
		switch (attackresult)
		{
		case 0:
			//Lose
			cout << "You lost, the other piece was a " << board[x][y].value << endl;
			recentattack = "Your ";
			recentattack += interpret(board[x][y].value);
			recentattack += " killed the opponent's ";
			recentattack += interpret(board[a][b].value);
			recentattack += "\n";
			board[a][b] = piece(13, 0, true);
			break;
		case 1:
			//Win
			cout << "You won! The other piece was a " << board[x][y].value << endl;
			recentattack = "Your ";
			recentattack += interpret(board[x][y].value);
			recentattack += " was killed by the opponent's ";
			recentattack += interpret(board[a][b].value);
			recentattack += "\n";
			board[x][y] = board[a][b];
			board[a][b] = piece(13, 0, true);
			break;
		case 2:
			//Game Over
			win = owner;
			break;
		case 3:
			//Error
			break;
		case 4:
			//Tie
			cout << "There was a tie, you were both the same rank.\nUnfortunately, you both lose your pieces.\n";
			recentattack = "There was a tie, you were both the same rank.\nUnfortunately, you both lose your pieces.\n";
			board[x][y] = piece(13, 0, true);
			board[a][b] = piece(13, 0, true);
			break;
		}

		system("pause");
		return 1;
	}
	if ((x == 4 || x == 5) && (y == 2 || y == 3 || y == 6 || y == 7))
		return -1;
}