#include <iostream>
#include <fstream>
#include <string>

// Function 
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


int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	// Starting values
	int initialPopulation = 100;
	int initialWheatAmount = 2800;
	int initialCityArea = 1000;

	// Updated values
	int currentWheatAmount;
	int currentPopulation;
	int currentCityArea;
	int roundNumber = 1;
	int peopleDied;
	//int peopleArrived;

	// Yearly changing values
	int thisYearAcrePrice;
	int thisYearHarvestPerAcre;
	//int totalYearHarvest;
	int acresSown;

	// Player's input (global)
	int wheatToEat;


	// GAME START

	std::cout << "Greetings, my new Lord. The city welcomes you!\n" << std::endl;
	std::cout << "Today our city has:\n"
		<< initialCityArea << " acres of land\n"
		<< initialPopulation << " city dwellers\n"
		<< initialWheatAmount << " bushels of wheat.\n" << std::endl;

	currentWheatAmount = initialWheatAmount;
	currentCityArea = initialCityArea;
	currentPopulation = initialPopulation;

	// Main loop
	do
	{
		thisYearAcrePrice = AcrePrice();
		thisYearHarvestPerAcre = HarvestPerAcre();

		// Player input
		std::cout << "What do you desire, my Lord?" << std::endl << "Would you rather buy the land or sell it?" << std::endl;
		std::cout << "1: Buy" << std::endl;
		std::cout << "2: Sell" << std::endl;
		std::cout << "3: Do nothing" << std::endl;

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

	} while (roundNumber <= 10 || currentPopulation > 0 || static_cast<float>(peopleDied) / static_cast<float>(currentPopulation) < 0.45);
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

		std::cout << "We now have " << acresToBuy << " more acres of land." << std::endl << std::endl;
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

		std::cout << "We now have " << acresToSell << " less acres of land." << std::endl;
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
			std::cout << "1: Buy" << std::endl;
			std::cout << "2: Sell" << std::endl;
			std::cout << "3: Do nothing" << std::endl;
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