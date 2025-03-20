/*
* Logan Maxfield
* March 8th 2025
* This program reads a stock related .csv file and stores the data to preform various calculations on the set.
*/

#include "stockstats.hpp"

int main(int argc, char* argv[])
{
	//if no file argument is given exit program
	if (argc <= 1) {
		cerr << "Error incorrect number of command line argurments" << endl;
		return EXIT_FAILURE;
	}

	//set number formatting for comma seperators
	cout.imbue(locale("en_US.UTF-8"));

	//Print header and set filename from command line argument
	cout << "stocks by Logan Maxfield" << endl;
	string fileName = argv[1];
	//remove .csv from the printed fileName
	string printFile = fileName.substr(0, fileName.find('.' , 0));
	cout << "Stock: \"" << printFile << "\"" << endl;

	//Create vector to store stock stats and read the file using readStockFile()
	stats stockStats;
	readStockFile(fileName, stockStats);
	if (stockStats.size() == 0) {
		cerr << "Error reading file\nFile Empty" << endl;
		exit(1);
	}

	//Call functions to find the lowest and highest values and volumes
	//Store them in a series of structs if functions require multiple values
	//See function prototypes for headers as well as body code for more detail
	passBackLow lowestVal = findLowestValue(stockStats); 
	passBackHigh highestValue = findHighestValue(stockStats);
	passLowVol lowestVol = findLowestVolume(stockStats);
	passHighVol highestVol = findHighestVolume(stockStats);
	double meanClose = calcMeanClose(stockStats);
	double meanVol = calcMeanVolume(stockStats);
	double varianceVol = calcVariance(stockStats, meanVol);
	double stddev = calcStandardDev(varianceVol);
	passBestFive bestFiveDay = calcBestFiveDay(stockStats);
	passWorstFive worstFiveDay = calcWorstFiveDay(stockStats);
	passBestTwenty bestTwentyDay = calcBestTwentyDay(stockStats);
	passWorstTwenty worstTwentyDay = calcWorstTwentyDay(stockStats);

	vector<double> vecMedian = getMidpoints(stockStats); // return a vector of doubles that is the average of each days open and close values
	quickSort(vecMedian, 0, vecMedian.size() - 1); // sort the vector of doubles
	double medianStockPrice = calcMedian(vecMedian); // get the median of that vector


	//Formatted output using the values above and specific dates from the vector
	cout << "From: " << stockStats[0].date << " to " << stockStats[stockStats.size() - 1].date << endl; // start and end date
	cout << "# Days: " << stockStats.size() << endl; // number of days or days that have stock values
	cout << "\nHistorical" << endl;

	cout << fixed << setprecision(2); // Set to 2 decimal places for the following money values
	cout << setw(20) << right << "Lowest Value: " << setw(13) << lowestVal.lowestVal << " on " << lowestVal.date << endl;
	cout << setw(20) << "Highest Value: " << setw(13) << highestValue.highestVal << " on " << highestValue.date << endl;
	//No decimal places possible so no need to change precision
	cout << setw(20) << "Low volume: " << setw(13) << lowestVol.lowVol << " on " << lowestVol.date << endl;
	cout << setw(20) << "High volume: " << setw(13) << highestVol.highVol << " on " << highestVol.date << endl;
	//even though mean is statistical garth outputs it with 2 decimal places so i stayed true to that.
	cout << setw(20) << "Mean close: " << setw(13) << meanClose << endl;
	cout << fixed << setprecision(1); // Set to 1 decimal place for the following statistical values
	cout << setw(20) << "Mean volume: " << setw(13) << meanVol << endl;
	cout << setw(20) << "Volume stddev: " << setw(13) << stddev << endl;
	cout << setw(20) << "Median stock price: " << setw(13) << medianStockPrice << endl;

	cout << "\nWorst 5 day period: " << worstFiveDay.dateOpen << " to " << worstFiveDay.dateClose << " = " << setw(12) << worstFiveDay.worstFive << endl;
	cout << "Best  5 day period: " << bestFiveDay.dateOpen << " to " << bestFiveDay.dateClose << " = " << setw(12) << bestFiveDay.bestFive << endl;

	cout << "\nWorst 20 day period: " << worstTwentyDay.dateOpen << " to " << worstTwentyDay.dateClose << " = " << setw(11) << worstTwentyDay.worstTwenty << endl;
	cout << "Best  20 day period: " << bestTwentyDay.dateOpen << " to " << bestTwentyDay.dateClose << " = " << setw(11) << bestTwentyDay.bestTwenty << endl;

}//End Main

