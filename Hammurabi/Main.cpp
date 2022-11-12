#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

// Function prototypes
int AcrePrice();
int HarvestPerAcre();

void BuySellLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice);
void BuyLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice);
void SellLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice);

void WheatToEat(int& currentWheatAmount, int& wheatToEat);
void WheatToSow(int& currentWheatAmount, int& currentCityArea, int& acresSown);

void PeopleDied(int& currentPopulation, int wheatToEat, int& peopleDied);
void PeopleArrived(int peopleDied, int thisYearHarvestPerAcre, int currentWheatAmount, int& currentPopulation);

void PlagueThreat(int& currentPopulation);

void TotalHarvest(int acresSown, int thisYearHarvestPerAcre, int currentPopulation, int& currentWheatAmount);
void RatTax(int& currentWheatAmount);

bool PlayFurther();
bool isGG(bool playFurther, int currentPopulation, int roundNumber, bool peopleAcception);

void SaveGame(int roundNumber, int currentWheatAmount, int currentPopulation, int currentCityArea);
void LoadGame(int& roundNumber, int& currentWheatAmount, int& currentPopulation, int& currentCityArea);
void NewGame(int& roundNumber, int& currentWheatAmount, int& currentCityArea, int& currentPopulation);

int main()
{
	srand(time(NULL));

	// Updated values
	int currentWheatAmount;
	int currentPopulation;
	int currentCityArea;
	int roundNumber;
	int peopleDied;
	int earlyPopulation;
	float starvationPercent;

	// Yearly changing values
	int thisYearAcrePrice;
	int thisYearHarvestPerAcre;
	int acresSown;

	// Player's input (global)
	int wheatToEat;
	int newGame;

	// Flags
	bool peopleAcception = true;
	bool playFurther = true;
	bool isGameStart = false;

	// Post game stats
	float averageAnnualDeathPercent = 0;
	float acrePerSoul;
	std::vector<int> annualDeathPercent;


	// Start / Continue
	std::cout << "1: Start new game\n2: Continue previous game" << std::endl;
	
	while (!isGameStart)
	{
		std::cin >> newGame;
		std::cout << std::endl;

		if (newGame == 1)
		{
			NewGame(roundNumber, currentWheatAmount, currentCityArea, currentPopulation);
			isGameStart = true;
		}
		else if (newGame == 2)
		{
			LoadGame(roundNumber, currentWheatAmount, currentPopulation, currentCityArea);
			isGameStart = true;
		}
		else
			std::cout << "Incorrect option" << std::endl;
	}
	
	// Main loop
	while (!isGG(playFurther, currentPopulation, roundNumber, peopleAcception))
	{
		if (roundNumber != 1)
		{
			playFurther = PlayFurther();
			if (!playFurther)
				break;
		}
		
		earlyPopulation = currentPopulation;
		thisYearAcrePrice = AcrePrice();
		thisYearHarvestPerAcre = HarvestPerAcre();

		// Player input
		std::cout << "What do you desire, my Lord?" << std::endl << "Would you rather buy the land or sell it?" << std::endl;
		std::cout << "1: Buy\n2: Sell\n3: Do nothing" << std::endl;

		BuySellLand(currentWheatAmount, currentCityArea, thisYearAcrePrice);

		WheatToEat(currentWheatAmount, wheatToEat);
		WheatToSow(currentWheatAmount, currentCityArea, acresSown);

		// Game response
		std::cout << "My Lord, allow me to tell you..." << std::endl;
		std::cout << "\tIn the year " << roundNumber << " of your honorable rule" << std::endl;

		PeopleDied(currentPopulation, wheatToEat, peopleDied);
		PeopleArrived(peopleDied, thisYearHarvestPerAcre, currentWheatAmount, currentPopulation);

		PlagueThreat(currentPopulation);

		std::cout << "\tCurrent city population is " << currentPopulation << " people;" << std::endl;

		TotalHarvest(acresSown, thisYearHarvestPerAcre, currentPopulation, currentWheatAmount);
		RatTax(currentWheatAmount);

		std::cout << "\tCurrent city area is " << currentCityArea << " acres;" << std::endl;
		std::cout << "\t1 acre of land cost " << thisYearAcrePrice << " bushels this year;" << std::endl;
		std::cout << std::endl;

		roundNumber++;

		starvationPercent = static_cast<float>(peopleDied) / static_cast<float>(earlyPopulation);
		if (starvationPercent > 0.45)
			peopleAcception = false;
		else
			peopleAcception = true;

		annualDeathPercent.push_back(starvationPercent * 100);
	}

	// Average annual death percent
	for (auto di = annualDeathPercent.begin(); di != annualDeathPercent.end(); di++)
	{
		averageAnnualDeathPercent += *di;
	}

	averageAnnualDeathPercent /= annualDeathPercent.size();
	std::cout << "\nAverage annual deaths:\t" << averageAnnualDeathPercent << "%" << std::endl;

	// Amount of acres per soul
	acrePerSoul = static_cast<float>(currentCityArea) / currentPopulation;
	std::cout << "Acre per soul:\t" << acrePerSoul << std::endl;

	if (playFurther == false)
	{
		std::cout << "You decided to quit game.\nThe world state will be saved." << std::endl;
		SaveGame(roundNumber, currentWheatAmount, currentPopulation, currentCityArea);
	}
		
	if (currentPopulation == 0)
		std::cout << "Your city extincted. You have no more people to rule." << std::endl;

	if (peopleAcception == false)
		std::cout << "More than 45% of your people died of starvation. People do not want you to rule anymore." << std::endl;

	if (roundNumber > 10)
	{
		std::cout << "GG! Good job!" << std::endl;
	}

	// Post game stats here
	// Чтобы статистика и результат выводились только по успешном завершении игры, надо этот блок положить в if (roundNumber > 10)
	if (averageAnnualDeathPercent > 33 && acrePerSoul < 7)
		std::cout << "Because of your incompetence in management, the people staged a riot, and expelled you from their city."
		<< "\nNow you are forced to eke out a miserable existence in exile." << std::endl;
	else if (averageAnnualDeathPercent > 10 && acrePerSoul < 9)
		std::cout << "You ruled with an iron hand, like Neroand Ivan the Terrible."
		<< "The people have breathed a sigh of relief, and no one wants to see you as a ruler anymore." << std::endl;
	else if (averageAnnualDeathPercent > 3 && acrePerSoul < 10)
		std::cout << "You did quite well, of course, you have detractors, "
		<< "but many would like to see you at the head of the city again." << std::endl;
	else
		std::cout << "Fantastic! Charlemagne, Disraeliand Jefferson couldn't have done better together!" << std::endl;		
}

// Function block
int AcrePrice() { return rand() % 10 + 17; }

int HarvestPerAcre() { return static_cast<int>(rand() % 6 + 1); }

void BuyLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice)
{
	// Correct amount input check
	bool isAmountCorrect = false;

	// Player input
	int acresToBuy;

	std::cout << "How many acres of land do you command to buy?\t";

	while (!isAmountCorrect)
	{
		std::cin >> acresToBuy;

		if (acresToBuy < 1)
		{
			std::cout << "We have to buy more than nothing.\n" << std::endl;
			std::cout << "How many acres of land do you command to buy?\t";
		}
		else if (currentWheatAmount - (acresToBuy * thisYearAcrePrice) < 0)
		{
			std::cout << "My Lord, we do not have enough wheat to buy that much land.\n" << std::endl;
			std::cout << "How many acres of land do you command to buy?\t";
		}
		else
			isAmountCorrect = true;

		currentWheatAmount -= (acresToBuy * thisYearAcrePrice);
		currentCityArea += acresToBuy;

		std::cout << "We now have " << acresToBuy << " more acres of land and " << currentWheatAmount << " bushels of wheat in total" << std::endl;
	}
}

void SellLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice)
{
	// Correct amount input check
	bool isAmountCorrect = false;

	// Player input
	int acresToSell;

	std::cout << "How many acres of land do you command to sell?\t";

	while (!isAmountCorrect)
	{
		std::cin >> acresToSell;

		if (acresToSell < 1)
		{
			std::cout << "We have to sell more than nothing.\n" << std::endl;
			std::cout << "How many acres of land do you command to sell?\t";
		}
		else if (currentCityArea < acresToSell)
		{
			std::cout << "My Lord, we do not have that much land to sell." << std::endl;
			std::cout << "How many acres of land do you command to sell?\t";
		}
		else
			isAmountCorrect = true;

		currentWheatAmount += (acresToSell * thisYearAcrePrice);
		currentCityArea -= acresToSell;

		std::cout << "We now have " << acresToSell << " less acres of land and " << currentWheatAmount << " bushels of wheat in total" << std::endl;
	}
}

void BuySellLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice)
{
	// Correct input check flag
	bool buySellCheck = false;

	while (!buySellCheck)
	{
		int buySell;
		std::cin >> buySell;

		switch (buySell)
		{
		case 1:
			BuyLand(currentWheatAmount, currentCityArea, thisYearAcrePrice);
			buySellCheck = true;
			break;

		case 2:
			SellLand(currentWheatAmount, currentCityArea, thisYearAcrePrice);
			buySellCheck = true;
			break;

		case 3:
			buySellCheck = true;
			break;

		default:
			std::cout << "I do not understand you, my Lord..." << std::endl;
			std::cout << "\nWould you rather buy the land or sell it?" << std::endl;
			std::cout << "1: Buy\n2: Sell\n3: Do nothing" << std::endl;
			break;
		}
	}
}

void WheatToEat(int& currentWheatAmount, int& wheatToEat)
{
	// Correct amount input check
	bool isAmountCorrect = false;

	while (!isAmountCorrect)
	{
		std::cout << "\nHow many bushels of wheat do you command to use as food?  ";
		std::cin >> wheatToEat;

		if (wheatToEat > currentWheatAmount)
			std::cout << "My Lord, we do not have that much wheat to feed." << std::endl;
		else if (wheatToEat < 1)
		{
			std::cout << "My Lord, our people need something to eat." << std::endl;
		}
		else
		{
			currentWheatAmount -= wheatToEat;
			isAmountCorrect = true;
		}
	}
}

void WheatToSow(int& currentWheatAmount, int& currentCityArea, int& acresSown)
{
	// Correct amount input check
	bool isAmountCorrect = false;

	int wheatToSow;

	while (!isAmountCorrect)
	{
		std::cout << "How many bushels of wheat do you command to sow?  ";
		std::cin >> wheatToSow;
		acresSown = wheatToSow * 2;

		if (wheatToSow > currentWheatAmount)
			std::cout << "My Lord, we do not have that much wheat to sow." << std::endl;
		else if (acresSown > currentCityArea)
		{
			std::cout << "My Lord, we do not have that much land to be sown." << std::endl;
		}
		else
		{
			currentWheatAmount -= wheatToSow;
			isAmountCorrect = true;
		}

		std::cout << std::endl;
	}
}

void PeopleDied(int& currentPopulation, int wheatToEat, int& peopleDied)
{
	peopleDied = currentPopulation - (wheatToEat / 20);
	if (peopleDied < 0)
		peopleDied = 0;

	currentPopulation -= peopleDied;

	if (peopleDied > 0)
		std::cout << "\t" << peopleDied << " people starved to death, ";
	else
		std::cout << "\tNobody starved to death, ";
}

void PeopleArrived(int peopleDied, int thisYearHarvestPerAcre, int currentWheatAmount, int& currentPopulation)
{
	int peopleArrived = peopleDied / 2 + (5 - thisYearHarvestPerAcre) * currentWheatAmount / 600 + 1;
	if (peopleArrived < 0)
		peopleArrived = 0;
	if (peopleArrived > 50)
		peopleArrived = 50;
	currentPopulation += peopleArrived;

	if (peopleArrived > 0)
		std::cout << peopleArrived << " people arrived in our great city;" << std::endl;
	else
		std::cout << " nobody arrived in our great city;" << std::endl;
}

void PlagueThreat(int& currentPopulation)
{
	float plagueChance = (static_cast<float>(rand() % 100)) / (static_cast<float>(100));
	if (plagueChance <= 0.15)
	{
		currentPopulation *= 0.5;
		std::cout << "\tThe plague annihilated half of the city population;" << std::endl;
	}
	else
		std::cout << "\tThis year the plague passed by;" << std::endl;
}

void TotalHarvest(int acresSown, int thisYearHarvestPerAcre, int currentPopulation, int& currentWheatAmount)
{
	int totalHarvest = acresSown * thisYearHarvestPerAcre;
	if (acresSown > currentPopulation * 10)
		totalHarvest = currentPopulation * 10;

	currentWheatAmount += totalHarvest;

	std::cout << "\tWe collected " << totalHarvest << " bushels of wheat, " << thisYearHarvestPerAcre << " bushel per acre;" << std::endl;
}

void RatTax(int& currentWheatAmount)
{
	float ratio = (static_cast<float>(rand() % 8) / 100);
	int ratTax = currentWheatAmount * ratio;
	
	currentWheatAmount -= ratTax;

	std::cout << "\tRats destroyed " << ratTax << " bushels of wheat, leaving us " << currentWheatAmount << " bushels in our barns;" << std::endl;
}

bool PlayFurther()
{
	bool isCorrect = false;
	int choice;

	while (!isCorrect)
	{
		std::cout << "1: Play further\n2: Quit game" << std::endl;
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			return true;
			isCorrect = true;
			break;

		case 2:
			return false;
			isCorrect = true;
			break;

		default:
			std::cout << "I do not understand you, my Lord..." << std::endl;
			std::cout << "1: Play further\n2: Quit game" << std::endl;
			break;
		}
	}
}

bool isGG(bool playFurther, int currentPopulation, int roundNumber, bool peopleAcception)
{
	if (peopleAcception == true)
	{
		if (currentPopulation != 0)
		{
			if (roundNumber <= 10)
			{
				if (playFurther == true)
				{
					return false;
				}
				else 
					return true;
			}
			else 
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

void SaveGame(int roundNumber, int currentWheatAmount, int currentPopulation, int currentCityArea)
{
	std::fstream save;
	std::string filename = "GameSave.txt";

	save.open(filename, std::fstream::in | std::fstream::out);

	if (save.is_open())
	{
		save << roundNumber << "\n";
		save << currentWheatAmount << "\n";
		save << currentPopulation << "\n";
		save << currentCityArea;
	}
	else
	{
		save.clear();
		save.open(filename, std::ios::out);
		save.close();
		save.open(filename);

		save << roundNumber << "\n";
		save << currentWheatAmount << "\n";
		save << currentPopulation << "\n";
		save << currentCityArea;
	}

	save.close();
}

void LoadGame(int& roundNumber, int& currentWheatAmount, int& currentPopulation, int& currentCityArea)
{
	std::fstream save;
	std::string filename = "GameSave.txt";

	std::string buffer;
	std::vector<int> sValues;
	
	save.open(filename, std::fstream::in | std::fstream::out);

	if (save.is_open())
	{
		while (!save.eof())
		{
			save >> buffer;
			sValues.push_back(std::stoi(buffer));
		}

		std::vector<int>::iterator s_it = sValues.begin();

		roundNumber = *s_it;
		++s_it;
		currentWheatAmount = *s_it;
		++s_it;
		currentPopulation = *s_it;
		++s_it;
		currentCityArea = *s_it;
	}
	else
	{
		std::cout << "Couldn't open save" << std::endl;
	}

	std::cout << "Welcome back, my Lord!" << std::endl;
	std::cout << "This is year " << roundNumber << " of your rule" << std::endl;
	std::cout << "Today our city has:\n"
		<< currentWheatAmount << " bushels of wheat.\n"
		<< currentPopulation << " city dwellers\n"
		<< currentCityArea << " acres of land\n" << std::endl;
}

void NewGame(int& roundNumber, int& currentWheatAmount, int& currentCityArea, int& currentPopulation)
{
	int initialPopulation = 100;
	int initialWheatAmount = 2800;
	int initialCityArea = 1000;

	std::cout << "Greetings, my new Lord. The city welcomes you!\n" << std::endl;
	std::cout << "Today our city has:\n"
		<< initialWheatAmount << " bushels of wheat.\n"
		<< initialPopulation << " city dwellers\n"
		<< initialCityArea << " acres of land\n" << std::endl;

	roundNumber = 1;
	currentWheatAmount = initialWheatAmount;
	currentCityArea = initialCityArea;
	currentPopulation = initialPopulation;
}