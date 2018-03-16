/* LAB ¹4, Second semestr
Creator: Maria Korol, K-11 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "copyright.h"
#include "bestShooter.h"


using namespace std;
using std::string;

int main(int argc, char *argv[]) {
	copyright();
	cout << "\tLabaratory work 4: ''Text''\n";
	cout << "\tBy racings' information from text file identify who was the best shooter in the season.\n";
	cout << "\tmax number of stages of the season is 20, start numbers from 1 to 999, places from 1 to 50,\n";
	cout << "\tmax time of distance is 3600 seconds(1 hour) and min time without penalty circles is 1260 seconds(21 minutes),\n";
	cout << "\tmin time of first frontier in is 300 seconds(5 minutes), first frontier out > ffin at least for 30 seconds,\n";
	cout << "\tmin time of second frontier in is 930 seconds(15.5 minutes), second frontier out > sfin at least for 30 seconds,";
	cout << "\tdifference between time of ffo and sfin at least 600 seconds(10 minutes),\n";
	cout << "\tdifference between time of second frontier out and time of distance at least 300 seconds(5 minutes).\n";
	cout << "\tMax number of missing shots is 20(20 shots in general)\n";
	cout << "\tMin time of overcaming penalty circles is (missing shots * 60 seconds) (1 circle per minute).\n\n";

	char * filename = nullptr;
	int dataStrings = -1;

	try {
		cout << argv[1] << endl;
		if (!argv[1]) {
			cout << "Pls Enter the name of input file!" << endl;
			string s;
			getline(cin, s);
			trim(s);
			if (s == "") throw ("Wrong file name!");
			filename = new char[s.length() + 1];
			strcpy(filename, s.c_str());
		}

		else {
			filename = new char[strlen(argv[1])];
			filename = argv[1];
		}

		//creating builder object
		Builder *f = nullptr;
		f = new Builder;

		//creating Container of racings
		RacingContainer *container = nullptr;
		container = new RacingContainer;

		(*f).addToContainer(container, filename, dataStrings);
		delete f;

		//creating container of racers
		D_List<Racer> * racers = nullptr;
		racers = new D_List<Racer>;

		//solution
		fillingRacerContainer(racers, container);
		calculateTimeShootingPerSeason(racers, container);
		findTheBestShooter(racers, container);

		//showing name and races information about best shooter
		racesOfBestShooters(racers, container);

		delete container;
		delete racers;
		system("pause");
		return 0;
	}

	/* catch (int -- number of field) for syntax errors, catch (double -- number of field) 
	for semantic errors, catch(const char[]) for others */
	catch (const char exception[]) {
		cout << exception << endl;
		system("pause");
		return 0;
	}

	catch (int i) {
		//line 0 -- header;
		cout << "Syntax error in line " << dataStrings << ", field " << i << endl;
		system("pause");
		return 0;
	}
	catch (double i) {
		if (i == -2) cout << "Semantic error in footer: wrong amount of records" << endl;
		if (i == -1) cout << "Semantic error in header: wrong amount of stages" << endl;
		if (i == 0) cout << "Semantic error in footer: wrong amount of missing shots" << endl;
		if (i > 0) cout << "Semantic error in data line " << dataStrings << ", field " << (int)i << endl;
		system("pause");
		return 0;
	}
}
