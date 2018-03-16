/* LAB №4, Second semestr
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
Файл містить статистику біатлонних гонок кубку світу типу «спрінт» з 2-ма вогневими рубежами
(порядковий номер етапу, стартовий номер учасника, зайняте місце, прізвище, ім’я, країна, загальний
час проходження дистанції (у секундах), час підходу та виходу з кожного вогневого рубежу (відносний,
у секундах від початку гонки), загальна кількість промахів, загальний час подолання штрафних кругів).
Для тих, хто не завершив гонку вказується загальний час -1. Знайти тих, хто стріляв найточніше
(протягом сезону), та вивести по них дані по всіх гонках (етап, стартовий номер, зайняте місце,
загальний час проходження дистанції, кількість промахів) та вказавши найкращий час стрільби та
гонки, де це відбулося.
У заголовку вказується кількість етапів, у нижньому колонтитулі вказується кількість записів т\а
загальна кількість промахів.
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

