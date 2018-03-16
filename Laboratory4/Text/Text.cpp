/* LAB ¹4, Second semestr
Creator: Maria Korol, K-11 */

#pragma once
#include "Text.h"

using namespace std;
using std::fstream;


void checkStagesAndMissingShots(const int stages, const int missingShots, RacingContainer *container)
{
	int maxStage = 0;
	int missShots = 0;
	RacingContainer::iterator i = (*container).front();
	for (; i != (*container).rear(); ++i) {
		if (i.operator*().getStage() > maxStage) maxStage = i.operator*().getStage();
		missShots += i.operator*().getMissingShots();
	}
	if (maxStage != stages) throw (-1.0);
	if (missingShots != missShots) throw (0.0);
}

string trim(string & s)
{
	for (int i = 0; i != s.length(); i++)
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\f' || s[i] == '\r' || s[i] == '\v')
		{
			s.erase(i, 1);
			i--;
		}
	return s;
}


                                                   /* LEXER*/

static const char delim = ';';

Lexer::Lexer() :s("") {}

bool Lexer::eof()const {
	return pos >= s.size();
}

string Lexer::getWord() const
{
	return word;
}

bool Lexer::isNumber(string word_)
{
	for (int i = 0; i != word_.length(); ++i)
		if (!isdigit(word_[i])) return false;
	return true;
}

bool Lexer::isDouble(string word_)
{
	for (int i = 0; i != word_.length(); ++i)
		if (!(isdigit(word_[i]) || (word_[i] == '.' && i != 0 && i != word_.length() - 1))) return false;
	return true;
}

bool Lexer::isWord(string word_)
{
	for (int i = 0; i != word_.length(); ++i)
		if (!isalpha(word_[i])) return false;
	return true;
}

void Lexer::init(const string& source) {
	s = source;
	pos = 0;
}

bool Lexer::get() {
	if (eof()) return false;
	auto pos1 = s.find_first_of(delim, pos);
	word = s.substr(pos, pos1 - pos);
	if (word.empty()) return false;
	pos = pos1 + 1;
	return true;
}

                                                          /*BUILDER*/

void Builder::addToContainer(RacingContainer * cont, const char* filename_, int &dataStrings)
{
	string s1 = "";
	bool wasFooterFound = false;
	int stages = 0;
	int records = 0;
	int missShots = 0;

	/* file opening and reading;
	** throw exception, if opening failed */
	ifstream *input = new ifstream(filename_);
	if ((*input).fail()) throw ("Error opening file");
	while (getline(*input, s1)) {
		trim(s1);
		if (s1 != "" && wasFooterFound) throw ("Wrong footer position!");
		if (s1 != "" && !wasFooterFound) {
			++dataStrings;
			//parsing text by fields and add new object to container, using method addToContainer from RacingContainer
			textParsingAndAddingToContainer(cont, s1, stages, missShots, wasFooterFound, dataStrings);
		}
	}
	(*input).close();
	delete input;
	//checking data of header&footer
	checkStagesAndMissingShots(stages, missShots, cont);
}


void Builder::textParsingAndAddingToContainer(RacingContainer *container_, const string & s, int &stages, int &missShots, bool &footerWasFound, const int dataStrings)
{

	string word = "";
	int records = 0;
	//creating new Lexer object
	Lexer *lex = nullptr;
	lex = new Lexer;

	(*lex).init(s);
	if (!(*lex).get()) throw (1);
	word = (*lex).getWord(); //record number or header/footer (filed 1)
	
	//if header was found 
	if (word.find("header:") == 0 && dataStrings != 0) throw ("Wrong header position!");
	if (word.find("header:") != 0 && dataStrings == 0) throw (1);
	if (word.find("header:") == 0 && dataStrings == 0) {
		word.erase(0, 7);

		//if number of stages is not a number
		if (!(*lex).isNumber(word)) throw (2);
		stages = stoi(word.substr(0, word.length()));

		//if there is another word in header
		if ((*lex).get()) throw (3);
		return;
	}

	//if footer was found
	if (word.find("footer:") == 0 && !footerWasFound ) {
		footerWasFound = true;
		word.erase(0, 7);

		//if number of records is not a number
		if (!(*lex).isNumber(word)) throw (2);
		records = stoi(word.substr(0, word.length()));
		if (records == 0) throw ("File has no data about racings!");
		if (!((dataStrings - 1) == records)) throw (-2.0);

		//if there isn't a note about number of missing shots
		if (!(*lex).get()) throw (3);

		//if number of missing shots is not a number
		word = (*lex).getWord();
		if (!(*lex).isNumber(word)) throw (3);
		missShots = stoi(word);
	
		//if there is another field in footer
		if ((*lex).get()) throw (4);
		return;
	}
		
	//if number of records is not a number
	if (!(*lex).isNumber(word)) throw (1);
	if (stoi(word) != dataStrings) throw (1.0); //if numeration is incorrect

	//stage (field 2)
	if (!(*lex).get()) throw (2);
	word = (*lex).getWord();
	if (!(*lex).isNumber(word)) throw (2);
	int stage_ = stoi(word); 
	if (stage_ < 0 || stage_>20) throw (2.0);

	//start number (field 3)
	if (!(*lex).get()) throw (3);
	word = (*lex).getWord();
	if (!(*lex).isNumber(word)) throw (3);
	int startNumber_ = stoi(word); 
	if (startNumber_ < 1 || startNumber_ >999) throw (3.0);

	//place (field 4)
	if(!(*lex).get()) throw (4);
	word = (*lex).getWord();
	if (!(*lex).isNumber(word)) throw (4);
	int place_ = stoi(word); 
	if (place_ < 1 || place_>50) throw (4.0);

	//surname (field 5)
	if (!(*lex).get()) throw (5);
	string surname_ = (*lex).getWord(); 
	if(!(*lex).isWord(surname_)) throw (5);

	//name (field 6)
	if (!(*lex).get()) throw (6);
	string name_ = (*lex).getWord(); 
	if (!(*lex).isWord(name_)) throw (6);

	//country, not used (filed 7)
	if (!(*lex).get()) throw (7);
	word = (*lex).getWord();
	if (!(*lex).isWord(word)) throw (7);

	//time of distance (filed 8)
	if (!(*lex).get()) throw (8);
	word = (*lex).getWord();
	if (!(*lex).isDouble(word)) throw (8);
	double timeOfDistance_ = stod(word); 
	if ((timeOfDistance_ < 1260 && timeOfDistance_ != -1) || (timeOfDistance_ > 3600)) throw (8.0);

	//first frontier in (field 9)
	if (!(*lex).get()) throw (9);
	word = (*lex).getWord();
	if (!(*lex).isDouble(word)) throw (9);
	double firstFrontierIn_ = stod(word); 
	if (firstFrontierIn_ < 300 || timeOfDistance_ - firstFrontierIn_ < 960) throw (9.0);

	//first frontier out (filed 10)
	if (!(*lex).get()) throw (10);
	word = (*lex).getWord();
	if (!(*lex).isDouble(word)) throw (10);
	double firstFrontierOut_ = stod(word); 
	if (firstFrontierOut_ - firstFrontierIn_ < 30 || timeOfDistance_ - firstFrontierOut_ < 930) throw (10.0);

	//second frontier in (field 11)
	if (!(*lex).get()) throw (11);
	word = (*lex).getWord();
	if (!(*lex).isDouble(word)) throw (11);
	double secondFrontierIn_ = stod(word); 
	if (secondFrontierIn_ < 930 || secondFrontierIn_ - firstFrontierOut_ < 300 || timeOfDistance_ - secondFrontierIn_ < 330) throw (11.0);

	//second frontier out (field 12)
	if (!(*lex).get()) throw (12);
	word = (*lex).getWord();
	if (!(*lex).isDouble(word)) throw (12);
	double secondFrontierOut_ = stod(word); 
	if (secondFrontierOut_ - secondFrontierIn_ < 30 || timeOfDistance_ - secondFrontierOut_ < 300) throw (12.0);

	//Missing shots (field 13)
	if (!(*lex).get()) throw (13);
	word = (*lex).getWord();
	if (!(*lex).isNumber(word)) throw (13);
	int missingShots_ = stoi(word); 
	if (missingShots_ > 20 || ((missingShots_ * 60) + 1260 > timeOfDistance_)) throw (13.0);

	//time of overcaming penalty circles (field 14) 
	if (!(*lex).get()) throw (14);
	word = (*lex).getWord();
	if (!(*lex).isDouble(word)) throw (14);
	double penaltyTime = stod(word);
	if (penaltyTime < missingShots_ * 60 || timeOfDistance_ < penaltyTime + 1260) throw (14.0);

	//if there is another word in line
	if ((*lex).get()) throw(15);
	delete lex;
	records++;
	(*container_).addToContainer(stage_, startNumber_, place_, name_, surname_, timeOfDistance_, firstFrontierIn_, firstFrontierOut_, secondFrontierIn_,
		secondFrontierOut_, missingShots_);
	return;
}
