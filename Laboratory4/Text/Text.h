/* LAB �4, Second semestr
Creator: Maria Korol, K-11 */

#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "List.h"

using namespace std;
using std::fstream;
using std::string;


/*
���� ������ ���������� ��������� ����� ����� ���� ���� ������ � 2-�� ��������� ��������
(���������� ����� �����, ��������� ����� ��������, ������� ����, �������, ���, �����, ���������
��� ����������� ��������� (� ��������), ��� ������ �� ������ � ������� ��������� ������ (��������,
� �������� �� ������� �����), �������� ������� ��������, ��������� ��� ��������� �������� �����).
��� ���, ��� �� �������� ����� ��������� ��������� ��� -1. ������ ���, ��� ������ ���������
(�������� ������), �� ������� �� ��� ��� �� ��� ������ (����, ��������� �����, ������� ����,
��������� ��� ����������� ���������, ������� ��������) �� �������� ��������� ��� ������� ��
�����, �� �� ��������.
� ��������� ��������� ������� �����, � �������� ���������� ��������� ������� ������ �\�
�������� ������� ��������.
*/

string trim(string& s);
void checkStagesAndMissingShots(const int stages, const int missingShots, RacingContainer *container); //footer data validity check 

class Lexer {
public:
	Lexer();
	void init(const string &source); //find first char different fron delim 
	bool get(); //getting words one by one from string
	bool eof()const; 
	string getWord()const; //return current word
	bool isNumber(string word_);
	bool isDouble(string word_);
	bool isWord(string word_);
	~Lexer() = default;
private:
	string s;
	string word;
	static const char delim = ';';
	std::basic_string<char>::size_type pos = 0;
};

class Builder {
public:
	Builder() = default;
	void textParsingAndAddingToContainer(RacingContainer *container_, const string& s, int &records,
		int &missShots, bool &footerWasFound, const int dataStrings); /* Lexographic string parsing with Lexer's methods;
																	  ** calculating stages quantity, records and total number 
																	  ** of missing shots */
	void addToContainer(RacingContainer *cont, const char * filename_, int &dataStrings); // dataStrings -- number of lines with data
	~Builder() = default;
};

