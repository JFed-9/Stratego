#include "stdafx.h"
#include "Windows.h"
#include "Master.h"
#include "time.h"
#include "iostream"
#include "iomanip"
#include "cstdlib"
#include <string>
#include <stdexcept>
using namespace std;

//Set Color
int consolewindow::getColor() {
	return reference;
}
void consolewindow::setColor() {
	reference = 7;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), reference);
};
void consolewindow::setColor(string color) {
	color = tolowercase(color);
	if (color == "black")
		reference = 0;
	else if (color == "darkblue")
		reference = 1;
	else if (color == "darkgreen")
		reference = 2;
	else if (color == "aqua")
		reference = 3;
	else if (color == "darkred" || color == "maroon")
		reference = 4;
	else if (color == "purple")
		reference = 5;
	else if (color == "gold" || color == "brown")
		reference = 6;
	else if (color == "std" || color == "silver")
		reference = 7;
	else if (color == "gray" || color == "grey")
		reference = 8;
	else if (color == "blue")
		reference = 9;
	else if (color == "neongreen" || color == "green")
		reference = 10;
	else if (color == "lightblue")
		reference = 11;
	else if (color == "red" || color == "brightred")
		reference = 12;
	else if (color == "pink")
		reference = 13;
	else if (color == "yellow")
		reference = 14;
	else if (color == "white" || color == "brightwhite")
		reference = 15;
	else
		reference = 7;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), reference);
};
void consolewindow::setColor(string colorb, string colorf) {
	colorb = tolowercase(colorb);
	colorf = tolowercase(colorf);
	if (colorb == "black")
		reference = 0;
	else if (colorb == "darkblue")
		reference = 1;
	else if (colorb == "darkgreen")
		reference = 2;
	else if (colorb == "aqua")
		reference = 3;
	else if (colorb == "darkred" || colorb == "maroon")
		reference = 4;
	else if (colorb == "purple")
		reference = 5;
	else if (colorb == "gold" || colorb == "brown")
		reference = 6;
	else if (colorb == "std" || colorb == "silver")
		reference = 7;
	else if (colorb == "gray" || colorb == "grey")
		reference = 8;
	else if (colorb == "blue")
		reference = 9;
	else if (colorb == "neongreen" || colorb == "green")
		reference = 10;
	else if (colorb == "lightblue")
		reference = 11;
	else if (colorb == "red" || colorb == "brightred")
		reference = 12;
	else if (colorb == "pink")
		reference = 13;
	else if (colorb == "yellow")
		reference = 14;
	else if (colorb == "white" || colorb == "brightwhite")
		reference = 15;
	else
		reference = 0;
	reference *= 16;
	if (colorf == "black")
		reference += 0;
	else if (colorf == "darkblue")
		reference += 1;
	else if (colorf == "darkgreen")
		reference += 2;
	else if (colorf == "aqua")
		reference += 3;
	else if (colorf == "darkred" || colorf == "maroon")
		reference += 4;
	else if (colorf == "purple")
		reference += 5;
	else if (colorf == "gold" || colorf == "brown")
		reference += 6;
	else if (colorf == "std" || colorf == "silver")
		reference += 7;
	else if (colorf == "gray" || colorf == "grey")
		reference += 8;
	else if (colorf == "blue")
		reference += 9;
	else if (colorf == "neongreen" || colorf == "green")
		reference += 10;
	else if (colorf == "lightblue")
		reference += 11;
	else if (colorf == "red" || colorf == "brightred")
		reference += 12;
	else if (colorf == "pink")
		reference += 13;
	else if (colorf == "yellow")
		reference += 14;
	else if (colorf == "white" || colorf == "brightwhite")
		reference += 15;
	else
		reference += 7;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), reference);
};
void consolewindow::setColor(int ref) {
	reference = ref;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), reference);
};
void consolewindow::safeInput(int &x) {
	string consume;
	while (!(cin >> x))
	{
		cout << "Not an number, please try again: ";
		cin >> x;
		cin.clear();
		cin.sync();
		cin.ignore();
		getline(cin, consume);
	}
	getline(cin, consume);
	return;
};
void consolewindow::safeInput(double &x) {
	string consume;
	while (!(cin >> x))
	{
		cout << "Not an number, please try again: ";
		cin >> x;
		cin.clear();
		cin.sync();
		cin.ignore();
		getline(cin, consume);
	}
	getline(cin, consume);
	return;
};
void consolewindow::safeInput(char &x) {
	string consume = "";
	cin >> x;
	getline(cin, consume);
	while (consume != "")
	{
		cout << "Excess characters received, please enter only one character: ";
		cin >> x;
		getline(cin, consume);
	}
};
string consolewindow::commas(double num)
{
	string decimals;
	string final_decimal = "";
	int i, j;
	bool all_zeros;
	string numWithCommas = to_string(static_cast<long long>(num));
	int insertPosition = numWithCommas.length() - 3;
	while (insertPosition > 0) {
		numWithCommas.insert(insertPosition, ",");
		insertPosition -= 3;
	}
	double decimal = num - floor(num);
	if (decimal != 0)
	{
		decimals = to_string(static_cast<long double>(decimal));
		for (i = 1; i <= decimals.length() - 1; i++)
		{
			all_zeros = true;
			for (j = i; j <= decimals.length() - 1; j++)
				if (decimals[j] != '0')
					all_zeros = false;
			if (!all_zeros)
				final_decimal += decimals[i];
		}
	}
	return numWithCommas + final_decimal;
}
string consolewindow::commas(int num)
{
	string numWithCommas = to_string(static_cast<long long>(num));
	int insertPosition = numWithCommas.length() - 3;
	while (insertPosition > 0) {
		numWithCommas.insert(insertPosition, ",");
		insertPosition -= 3;
	}
	return numWithCommas;
}
void consolewindow::toClipboard(string copy)
{
	OpenClipboard(GetDesktopWindow());
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, copy.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), copy.c_str(), copy.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}
consolewindow::consolewindow() {
	reference = 7;
	srand(time(NULL));
}
int consolewindow::random(int begin, int end)
{
	return rand() % (end - begin + 1) + begin;
}
string consolewindow::tolowercase(std::string str1)
{
	int i;
	string new_str1 = "";
	for (i = 0; i < str1.length(); i++)
		new_str1 += tolower(str1[i]);
	return new_str1;
}
//int location is how the array sees the location, starting with space 0
std::string consolewindow::changechar(std::string str1, int location, char ch)
{
	string beginning = "", end = "";
	int i;
	for (i = 0; i < location; i++)
		beginning += str1[i];
	for (i = location + 1; i < str1.length(); i++)
		end += str1[i];
	return beginning + ch + end;
}

//Encryption
string consolewindow::encrypt(string message, string key)
{
	int change = 0;
	for (int i = 0; i < message.length(); i++)
	{
		for (int j = 0; j < key.length(); j++)
		{
			change += (int)key[j] * j;
		}
		change /= key.length();
		message[i] = (char)(message[i] + change);
	}
	toClipboard(message);
	return message;
}
string consolewindow::decrypt(string message, string key)
{
	int change = 0;
	for (int i = 0; i < message.length(); i++)
	{
		for (int j = 0; j < key.length(); j++)
		{
			change += (int)key[j] * j;
		}
		change /= key.length();
		message[i] = (char)(message[i] - change);;
	}
	return message;
}