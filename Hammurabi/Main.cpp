#include <iostream>
#include <fstream>
#include <string>

bool WasPlague()
{
	float plagueChance = (static_cast<float>(rand() % 100)) / (static_cast<float>(100));
	if (plagueChance > 0.15)
		return false;
	else
		return true;
}

int AcrePrice()
{
	return rand() % 10 + 17;
}

int Harvest()
{
	return static_cast<int>(rand() % 6 + 1);
}

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
	int roundNumber = 0;
	int peopleDied;
	int peopleArrived;

	// Yearly changing values
	int thisYearAcrePrice;
	int thisYearHarvestPerAcre;
	int totalYearHarvest;

	// Player's input
	int buySell;
	int acresToBuy;
	int acresToSell;
	int wheatToEat;
	int wheatToSow;

	// Flags
	bool buySellCheck = false;
	bool amountCheck = false;
	bool enoughWheat = false;


	//============================================================================================================================== GAME START

	thisYearAcrePrice = AcrePrice();
	thisYearHarvestPerAcre = Harvest();

	std::cout << "Greetings, my new Lord. The city welcomes you!\n" << std::endl;
	std::cout << "Today our city has:\n"
		<< initialCityArea << " acres of land\n"
		<< initialPopulation << " city dwellers\n"
		<< initialWheatAmount << " bushels of wheat.\n" << std::endl;

	currentWheatAmount = initialWheatAmount;
	currentCityArea = initialCityArea;
	currentPopulation = initialPopulation;

	std::cout << "What do you desire, my Lord?" << std::endl << "Would you rather buy the land or sell it?" << std::endl;
	std::cout << "1: Buy" << std::endl;
	std::cout << "2: Sell" << std::endl;

	while (!buySellCheck)
	{
		std::cin >> buySell;

		if (buySell == 1)
		{
			std::cout << "How many acres of land do you command to buy?\t";
			while (!amountCheck)
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
					amountCheck = true;
			}
			amountCheck = false;

			currentWheatAmount -= (acresToBuy * thisYearAcrePrice);
			currentCityArea += acresToBuy;

			std::cout << "We now have " << acresToBuy << " more acres of land." << std::endl << std::endl;
			buySellCheck = true;
		}
		else if (buySell == 2)
		{
			std::cout << "How many acres of land do you command to sell?\t";
			while (!amountCheck)
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
					amountCheck = true;
			}
			amountCheck = false;

			currentWheatAmount += (acresToSell * thisYearAcrePrice);
			currentCityArea -= acresToSell;

			std::cout << "We now have " << acresToSell << " less acres of land." << std::endl << std::endl;
			buySellCheck = true;
		}
		else
		{
			std::cout << "I do not understand you, my Lord..." << std::endl;
			std::cout << "\nWould you rather buy the land or sell it?" << std::endl;
			std::cout << "1: Buy" << std::endl;
			std::cout << "2: Sell" << std::endl;
		}
	}

	while (!enoughWheat)
	{
		while (!amountCheck)
		{
			std::cout << "How many bushels of wheat do you command to use as food?  ";
			std::cin >> wheatToEat;

			if (wheatToEat > currentWheatAmount)
				std::cout << "My Lord, we do not have that much wheat to feed.\n" << std::endl;
			else if (wheatToEat < 1)
			{
				std::cout << "My Lord, our people need something to eat." << std::endl;
			}
			else
				amountCheck = true;

			std::cout << std::endl;
		}
		amountCheck = false;

		while (!amountCheck)
		{
			std::cout << "How many bushels of wheat do you command to sow?  ";
			std::cin >> wheatToSow;

			if (wheatToSow > currentWheatAmount)
				std::cout << "My Lord, we do not have that much wheat to sow.\n" << std::endl;
			else
				amountCheck = true;

			std::cout << std::endl;
		}
		amountCheck = false;

		if (currentWheatAmount < (wheatToEat + wheatToSow))
		{
			std::cout << "My Lord, we do not have that much wheat. You should redistribute it.\n" << std::endl;
		}
		else
			enoughWheat = true;
	}


	//============================================================================================================================== MAIN GAMEPLAY

	std::cout << "My Lord, allow me to tell you..." << std::endl;
	std::cout << "\tIn the year " << roundNumber << " of your honorable rule" << std::endl;

	peopleDied = currentPopulation - wheatToEat / 20;
	if (peopleDied < 0)
		peopleDied = 0;
	currentPopulation -= peopleDied;

	if (peopleDied > 0)
		std::cout << "\t" << peopleDied << " people starved to death, ";
	else
		std::cout << "\tNobody starved to death, ";

	peopleArrived = (static_cast<int>(peopleDied) / 2) + ((5 - thisYearHarvestPerAcre) * currentWheatAmount / 600) + 1;
	if (peopleArrived < 0)
		peopleArrived = 0;
	currentPopulation += peopleArrived;

	if (peopleArrived > 0)
		std::cout << peopleArrived << " people arrived in our great city;";
	else
		std::cout << "\tNobody starved to death, ";

	if (WasPlague())
	{
		currentPopulation *= 0.5;
		std::cout << "\tThe plague annihilated half of the city population;" << std::endl;
	}
	else
		std::cout << "\tThis year the plague passed by;" << std::endl;

	std::cout << "\tCurrent city population is " << currentPopulation << " people;" << std::endl;






	std::cout << std::endl;
}