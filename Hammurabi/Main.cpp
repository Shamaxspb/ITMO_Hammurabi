#include <iostream>
#include <fstream>
#include <string>

// Function prototypes
bool WasPlague();
int AcrePrice();
int HarvestPerAcre();
void RatTax(int& currentWheatAmount, int& ratsDestroyed);

void BuySellLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice);
void BuyLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice);
void SellLand(int& currentWheatAmount, int& currentCityArea, int thisYearAcrePrice);



void PlayerInput(int& currentWheatAmount, int& currentCityArea, int& thisYearAcrePrice, int& wheatToEat, int& acresSown);

void ReportToTheLord(int& currentWheatAmount, int& currentPopulation, int& currentCityArea, int wheatToEat,
	int& thisYearHarvestPerAcre, int& thisYearAcrePrice, int& acresSown, int& ratsDestroyed, int& roundNumber, int& peopleDied);

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
	int peopleDied = 0;
	//int peopleArrived;

	// Yearly changing values
	int thisYearAcrePrice;
	int thisYearHarvestPerAcre;
	//int totalYearHarvest;
	int acresSown;
	int ratsDestroyed;

	// Player's input (global)
	int buySell;
	int wheatToEat;

	// Flags
	bool buySellCheck = false;


	//============================================================================================================================== GAME START

	std::cout << "Greetings, my new Lord. The city welcomes you!\n" << std::endl;
	std::cout << "Today our city has:\n"
		<< initialCityArea << " acres of land\n"
		<< initialPopulation << " city dwellers\n"
		<< initialWheatAmount << " bushels of wheat.\n" << std::endl;

	currentWheatAmount = initialWheatAmount;
	currentCityArea = initialCityArea;
	currentPopulation = initialPopulation;

	// Main loop
	while (roundNumber <= 10 || currentPopulation > 0 || 
		static_cast<float>(peopleDied) / static_cast<float>(currentPopulation) < 0.45)
	{
		thisYearAcrePrice = AcrePrice();
		thisYearHarvestPerAcre = HarvestPerAcre();

		std::cout << "What do you desire, my Lord?" << std::endl << "Would you rather buy the land or sell it?" << std::endl;
		std::cout << "1: Buy" << std::endl;
		std::cout << "2: Sell" << std::endl;
		std::cout << "3: Do nothing" << std::endl;

		BuySellLand(currentWheatAmount, currentCityArea, thisYearAcrePrice);

		std::cout << "Breakpoint" << std::endl;
		int q;
		std::cin >> q;
		
		



		/*PlayerInput(currentWheatAmount, currentCityArea, thisYearAcrePrice, wheatToEat, acresSown);

		ReportToTheLord(currentWheatAmount, currentPopulation, currentCityArea,	thisYearHarvestPerAcre, thisYearAcrePrice,
						wheatToEat, acresSown, ratsDestroyed, roundNumber, peopleDied);*/

		roundNumber++;
	}
}

// Function block
bool WasPlague()
{
	float plagueChance = (static_cast<float>(rand() % 100)) / (static_cast<float>(100));
	if (plagueChance > 0.15)
		return false;
	else
		return true;
}

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

		std::cout << "We now have " << acresToSell << " less acres of land." << std::endl << std::endl;
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



void RatTax(int& currentWheatAmount, int& ratsDestroyed)
{
	float ratTax = (static_cast<float>(rand() % 8) / static_cast<float>(100));
	ratsDestroyed = currentWheatAmount * ratTax;
	currentWheatAmount -= ratsDestroyed;
}

void PlayerInput(int& currentWheatAmount, int& currentCityArea, int& thisYearAcrePrice, int& wheatToEat, int& acresSown)
{
	// Player's input
	int buySell;
	int acresToBuy;
	int acresToSell;
	int wheatToSow;

	// Flags
	bool buySellCheck = false;
	bool amountCheck = false;
	bool enoughWheat = false;

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
			{
				currentWheatAmount -= wheatToEat;
				amountCheck = true;
			}

			std::cout << std::endl;
		}
		amountCheck = false;

		while (!amountCheck)
		{
			std::cout << "How many bushels of wheat do you command to sow?  ";
			std::cin >> wheatToSow;

			if (wheatToSow > currentWheatAmount)
				std::cout << "My Lord, we do not have that much wheat to sow.\n" << std::endl;
			else if (wheatToSow * 2 > currentCityArea)
			{
				std::cout << "My Lord, we do not have that much land to be sown." << std::endl;
			}
			else
			{
				acresSown = wheatToSow * 2;
				currentWheatAmount -= wheatToSow;
				amountCheck = true;
			}

			std::cout << std::endl;
		}
		amountCheck = false;

		/*if (currentWheatAmount < (wheatToEat + wheatToSow))
		{
			std::cout << "My Lord, we do not have that much wheat. You should redistribute it.\n" << std::endl;
		}
		else
			enoughWheat = true;*/
		enoughWheat = true;
	}
}

void ReportToTheLord(int& currentWheatAmount, int& currentPopulation, int & currentCityArea, int wheatToEat, 
	int& thisYearHarvestPerAcre, int& thisYearAcrePrice, int& acresSown, int& ratsDestroyed, int& roundNumber, int& peopleDied)
{
	int peopleArrived;
	int totalYearHarvest;

	std::cout << "My Lord, allow me to tell you..." << std::endl;
	std::cout << "\tIn the year " << roundNumber << " of your honorable rule" << std::endl;

	peopleDied = currentPopulation - (static_cast<int>(wheatToEat / 20));
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
	if (peopleArrived > 50)
		peopleArrived = 50;
	currentPopulation += peopleArrived;

	if (peopleArrived > 0)
		std::cout << peopleArrived << " people arrived in our great city;" << std::endl;
	else
		std::cout << "\tNobody arrived in our great city;" << std::endl;

	if (WasPlague())
	{
		currentPopulation *= 0.5;
		std::cout << "\tThe plague annihilated half of the city population;" << std::endl;
	}
	else
		std::cout << "\tThis year the plague passed by;" << std::endl;

	std::cout << "\tCurrent city population is " << currentPopulation << " people;" << std::endl;

	totalYearHarvest = acresSown * thisYearHarvestPerAcre;
	if (acresSown > currentPopulation * 10)
		totalYearHarvest = currentPopulation * 10;

	currentWheatAmount += totalYearHarvest;

	std::cout << "\tWe collected " << totalYearHarvest << " bushels of wheat, " << thisYearHarvestPerAcre << " bushel per acre;" << std::endl;

	RatTax(currentWheatAmount, ratsDestroyed);

	std::cout << "\tRats destroyed " << ratsDestroyed << " bushels of wheat, leaving us " << currentWheatAmount << " bushels in our barns;" << std::endl;

	std::cout << "\tCurrent city area is " << currentCityArea << " acres;" << std::endl;

	std::cout << "\t1 acre of land now costs " << thisYearAcrePrice << " bushels;" << std::endl;

	std::cout << std::endl;
}