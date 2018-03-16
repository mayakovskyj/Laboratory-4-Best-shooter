/* LAB ¹4, Second semestr
Creator: Maria Korol, K-11 */

#pragma once
#include "Text.h"

void fillingRacerContainer(D_List<Racer> *racers, RacingContainer *container); //pushing racers to racer's container
void calculateTimeShootingPerSeason(D_List<Racer> *racers, RacingContainer *container); //filling the information about shooting and calculate quantity of stages of each racer per season
void findTheBestShooter(D_List<Racer> *racers, RacingContainer *container); //searching the best time with penalties among racers
void racesOfBestShooters(D_List<Racer> *racers, RacingContainer *container); //showing name and races' information about best shooter

/* To identify the best shooter of the season and display all they racings this prgramm uses next algorithm:
** 1. Sorting container of racing and filling container of racers;
** 2. Calculating time shooting per season and amount of stages for all racers;
** 3. Searching the best shooter using next rule: shootersTime = ((time of ffo - time of ffi) +
** + (time of sfo - sfi) + (missing shoots * 10 penalty points)) / amount of stages;
** Shooter/shooters who has the minimum of shootersTime are the best. 
** Displaying racings' data of best shooters */