#include "stdafx.h"
#include <iostream>
class consolewindow
{
public:
	//Set Color
	int getColor();
	void setColor();
	void setColor(std::string color);
	void setColor(std::string colorb, std::string colorf);
	void setColor(int reference);
	void safeInput(int &x);
	void safeInput(double &x);
	void safeInput(char &x);
	std::string commas(double num);
	std::string commas(int num);
	void toClipboard(std::string copy);
	consolewindow();
	int random(int begin, int end);
	std::string tolowercase(std::string str1);
	std::string changechar(std::string srt1, int location, char ch);
	std::string encrypt(std::string message, std::string key);
	std::string decrypt(std::string message, std::string key);
protected:
	int reference;
};