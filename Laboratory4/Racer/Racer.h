/* LAB ¹4, Second semestr
Creator: Maria Korol, K-11 */

#pragma once
#include <string>
#include <iostream>

using namespace std;
using std::string;

class Racer {
public:
	Racer() = default;
	bool operator ==(const Racer &other) const;
	string info()const; // name + surname
	string getName()const;
	string getSurname()const;
	int getStagesQuantity()const;
	void setStages();
	double getTimeShootingPerSeason()const;
	bool getIsBestShooter()const;
	void bestShooter(); //mark for best shooter in the season
	void addTimeShooting(double &time_); //increase time shooting per season for the time shooting with penalties of one race
	virtual ~Racer() = default;
protected:
	string name;
	string surname;
	int stagesQuantity = 0;
	bool isBestShooter = false;
	double timeShootingPerSeason = 0; //final time shooting with penalties per season
protected:
	void timeIncreasing(const double time_);
	void increaseStagesQuantity();
	void changeStatus();
};

class Racing :public Racer {
public:
	Racing(int stage_, int startNumber_, int place_, string name_, string surname_, double timeOfDistance_,
		double firstFrontierIn_, double firstFrontierOut_, double secondFrontierIn_, double secondFrontierOut_, int missingShots_);
	Racing() {}
	int getStage()const;
	int getMissingShots()const;
	bool operator >(const Racing &other) const;
	bool operator <(const Racing &other) const;
	double timeShootingWithPenalty(); //calculating difference of frontier's time in and out + 10 seconds for each missing shot 
	string info()const; //stage + start number + place + time of distance + missing shots
	bool isRacersRace(Racer & racer)const; //does Racer was taking part in this race
	virtual ~Racing() = default;
private:
	void set(int stage_ = 0, int startNumber_ = 0, int place_ = 0, string name_ = "", string surname_ = "", double timeOfDistance_ = 0,
		double firstFrontierIn_ = 0, double firstFrontierOut_ = 0, double secondFrontierIn_ = 0, double secondFrontierOut_ = 0, int missingShots_ = 0);
private:
	int stage;
	int startNumber;
	int place;
	double timeOfDistance;
	double firstFrontierIn;
	double firstFrontierOut;
	double secondFrontierIn;
	double secondFrontierOut;
	int missingShots;
};


