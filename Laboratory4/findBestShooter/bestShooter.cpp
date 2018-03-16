/* LAB ¹4, Second semestr
Creator: Maria Korol, K-11 */

#define _CRT_SECURE_NO_WARNINGS

#include "bestShooter.h"

void fillingRacerContainer(D_List<Racer> * racers, RacingContainer * container)
{

	/* sorting racings using bubble sorting algorithm */
	(*container).bubbleSorting();

	//creating and set iterator i of racing container to start
	RacingContainer::iterator i = (*container).front();

	//adding first racer to racer container
	Racing oneRace = i.operator*();
	(*racers).add_rear(oneRace);

	//adding other racers to racer container
	++i;
	for (; i != (*container).rear(); ++i)
		if (!(i.operator*() == oneRace)) {
			oneRace = i.operator*();
			(*racers).add_rear(oneRace);
		}
}

void calculateTimeShootingPerSeason(D_List<Racer>* racers, RacingContainer * container)
{

	/* creating and set iterator i of racing container to start
	** creating and set iterator j of racer's container to start */
	RacingContainer::iterator i = (*container).front();
	D_List<Racer>::iterator j = (*racers).front();

	//calculating time shooting per season for each racer and calculate quantity of stages
	for (; j != (*racers).rear(); ++j)
		while (i.operator*().isRacersRace(j.operator*())) {
			double time = i.operator*().timeShootingWithPenalty();
			j.operator*().addTimeShooting(time);
			j.operator*().setStages();
			++i;
		}
}

void findTheBestShooter(D_List<Racer>* racers, RacingContainer * container)
{

	/* creating and set iterator j of racer's container to start;
	** creating iterator best of racer's container and set it to start
	** set minTime of shooting by first racer / number of stages*/
	D_List<Racer>::iterator j = (*racers).front();
	double minTime = j.operator*().getTimeShootingPerSeason() / j.operator*().getStagesQuantity();

	//searching the best shooters
	for (; j != (*racers).rear(); ++j)
		if (j.operator*().getTimeShootingPerSeason() / j.operator*().getStagesQuantity() <= minTime)
			minTime = j.operator*().getTimeShootingPerSeason() / j.operator*().getStagesQuantity();
	j = (*racers).front();
	for (; j != (*racers).rear(); ++j)
		if (j.operator*().getTimeShootingPerSeason() / j.operator*().getStagesQuantity() == minTime)
			j.operator*().bestShooter();
}

void racesOfBestShooters(D_List<Racer>* racers, RacingContainer * container)
{
	cout << "The best shooter/shooters has been found. Whould you like to get information about their racings" << endl;
	cout << "to console or to a separate text file? Pls Enter '1' for first variant or '2' for second" << endl;
	int choice = 0;
	RacingContainer::iterator i = (*container).front();
	D_List<Racer>::iterator j = (*racers).front();
	cin >> choice;

	switch (choice) {
	case 1: 
		for (; j != (*racers).rear(); ++j) 
			if (j.operator*().getIsBestShooter()) {
				i = (*container).front();
				cout << "\nBest shooter of the season is: " << j.operator*().info() << endl;
				cout << "And their racings are:" << endl;
				for (; i != (*container).rear(); ++i)
					if (i.operator*().isRacersRace(j.operator*())) cout << i.operator*().info() << endl;
				j.operator*().bestShooter();
			}
		break;
	case 2: {
		cout << "Pls input a file name. Pls notice: if you enter an empty name," << endl;
		cout << "the result will be displayed on your console." << endl;
		string s;
		cin.ignore();
		getline(cin, s);
		trim(s);
		
		//if string is empty
		if (s == "") {
			for (; j != (*racers).rear(); ++j)
				if (j.operator*().getIsBestShooter()) {
					i = (*container).front();
					cout << "\nBest shooter of the season is: " << j.operator*().info() << endl;
					cout << "And their racings are:" << endl;
					for (; i != (*container).rear(); ++i)
						if (i.operator*().isRacersRace(j.operator*())) cout << i.operator*().info() << endl;
					j.operator*().bestShooter();
				}
			break;
		}
		else {
			char * fname = nullptr;
			fname = new char[s.length() + 1];
			strcpy(fname, s.c_str());
			ofstream *output = new ofstream(fname);
			if ((*output).fail()) throw ("Can not create output file!");
			for (; j != (*racers).rear(); ++j)
				if (j.operator*().getIsBestShooter()) {
					i = (*container).front();
					(*output) << "Best shooter of the season is: " << j.operator*().info() << endl;
					(*output) << "And their racings are:" << endl;
					for (; i != (*container).rear(); ++i)
						if (i.operator*().isRacersRace(j.operator*())) (*output) << i.operator*().info() << endl;
					j.operator*().bestShooter();
				}
			cout << "The information was succsesfully written! Pls check your file" << endl;
			(*output).close();
			delete output;
			break;
		}
	}
	default: throw ("Wrong choice input!"); break;
	}

}


