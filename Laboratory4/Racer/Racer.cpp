/* LAB ¹4, Second semestr
Creator: Maria Korol, K-11 */

#include "Racer.h"

														/* RACER */

string Racer::info() const
{
	return surname + " " + name;
}

string Racer::getName() const
{
	return name;
}

string Racer::getSurname() const
{
	return surname;
}

int Racer::getStagesQuantity() const
{
	return stagesQuantity;
}

void Racer::setStages()
{
	increaseStagesQuantity();
}

void Racer::addTimeShooting(double & time_)
{
	timeIncreasing(time_);
}

double Racer::getTimeShootingPerSeason() const
{
	return timeShootingPerSeason;
}

bool Racer::getIsBestShooter() const
{
	return isBestShooter;
}

void Racer::bestShooter()
{
	changeStatus();
}

bool Racer::operator==(const Racer & other) const
{
	return name == other.name && surname == other.surname;
}

void Racer::timeIncreasing(const double time_)
{
	timeShootingPerSeason += time_;
}

void Racer::increaseStagesQuantity()
{
	++stagesQuantity;
}

void Racer::changeStatus()
{
	if (isBestShooter) isBestShooter = false;
	else isBestShooter = true;
}


														/* RACING */

Racing::Racing(int stage_, int startNumber_, int place_, string name_, string surname_, double timeOfDistance_, double firstFrontierIn_, double firstFrontierOut_, double secondFrontierIn_, double secondFrontierOut_, int missingShots_)
{
	set(stage_, startNumber_, place_, name_, surname_, timeOfDistance_, firstFrontierIn_, firstFrontierOut_, secondFrontierIn_,
		secondFrontierOut_, missingShots_);
}

int Racing::getStage() const
{
	return stage;
}

int Racing::getMissingShots() const
{
	return missingShots;
}

bool Racing::operator>(const Racing & other) const
{
	if (surname > other.surname) return true;
	if (surname == other.surname)
		if (name > other.name) return true;
	if (name == other.name)
		if (stage > other.stage) return true;
	return false;
}

bool Racing::operator<(const Racing & other) const
{
	if (surname < other.surname) return true;
	if (surname == other.surname)
		if (name < other.name) return true;
	if (name == other.name)
		if (stage < other.stage) return true;
	return false;
}

void Racing::set(int stage_, int startNumber_, int place_, string name_, string surname_, double timeOfDistance_,
	double firstFrontierIn_, double firstFrontierOut_, double secondFrontierIn_, double secondFrontierOut_, int missingShots_)
{
	stage = stage_;
	startNumber = startNumber_;
	place = place_;
	name = name_;
	surname = surname_;
	timeOfDistance = timeOfDistance_;
	firstFrontierIn = firstFrontierIn_;
	firstFrontierOut = firstFrontierOut_;
	secondFrontierIn = secondFrontierIn_;
	secondFrontierOut = secondFrontierOut_;
	missingShots = missingShots_;
}

double Racing::timeShootingWithPenalty()
{
	return (firstFrontierOut - firstFrontierIn) + (secondFrontierOut - secondFrontierIn) + (10 * missingShots);
}


string Racing::info()const
{
	return "Stage: " + std::to_string(stage) + ", start number: " + std::to_string(startNumber) + ", place: " + std::to_string(place) + ", time of distance: " + std::to_string(timeOfDistance) + ", missing shots: " + std::to_string(missingShots);
}

bool Racing::isRacersRace(Racer & racer) const
{
	return getName() == racer.getName() && getSurname() == racer.getSurname();
}




					