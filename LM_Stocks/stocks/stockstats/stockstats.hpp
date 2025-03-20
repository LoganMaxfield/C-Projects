/*
* Logan Maxfield
* March 8th 2025
* This program reads a stock related .csv file and stores the data to preform various calculations on the set.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>
#include <iomanip>

using namespace std;

//Struct to hold stock data from each day
struct dayStats {
	string date{};
	double openValue{};
	double highValue{};
	double lowValue{};
	double closeValue{};
	int volumeTraded{};
};
//Type def for vector of structs
typedef vector<dayStats> stats;

//Following structs are for passing multiple values back from functions

// passes back the lowest low value and the date it occured
struct passBackLow {
	double lowestVal{};
	string date{};
};
// passes back the highest high value and the date it occured
struct passBackHigh {
	double highestVal{};
	string date{};
};
// passes back the lowest volume traded and the date it occured
struct passLowVol {
	int lowVol{};
	string date{};
};
//passes back the highest volume traded and the date it occured
struct passHighVol {
	int highVol{};
	string date{};
};
//passes back the best five day period and the date range it occured
struct passBestFive {
	double bestFive{};
	string dateOpen{};
	string dateClose{};
};
//passes back the worst five day period and the date range it occured
struct passWorstFive {
	double worstFive{};
	string dateOpen{};
	string dateClose{};
};
//passes back the best twenty day period and the date range it occured
struct passBestTwenty {
	double bestTwenty{};
	string dateOpen{};
	string dateClose{};
};
//passes back the worst twenty day period and the date range it occured
struct passWorstTwenty {
	double worstTwenty{};
	string dateOpen{};
	string dateClose{};
};

/*
* readStockFile() 
* Reads the stock file line by line into a struct then places that struct into a vector
* param : string fileName, stats& stockstats
* return : void
*/
void readStockFile(string fileName, stats& stockstats);
/*
* findLowestValue()
* Finds the lowest low value in the vector of structs
* param : const stats& vec
* return : passBackLow struct
*/
passBackLow findLowestValue(const stats& vec);
/*
* findHighestValue()
* Finds the highest high value in the vector of structs
* param : const stats& vec
* return : passBackHigh struct
*/
passBackHigh findHighestValue(const stats& vec);
/*
* findLowestVolume()
* Finds the lowest volume traded in the vector of structs
* param : const stats& vec
* return : passLowVol struct
*/
passLowVol findLowestVolume(const stats& vec);
/*
* findHighestVolume()
* Finds the highest volume traded in the vector of structs
* param : const stats& vec
* return : passHighVol struct
*/
passHighVol findHighestVolume(const stats& vec);
/*
* calcMeanClose()
* Calculates the mean of the close values in the vector of structs
* param : const stats& vec
* return : double
*/
double calcMeanClose(const stats& vec);
/*
* calcMeanVolume()
* Calculates the mean of the volume traded in the vector of structs
* param : const stats& vec
* return : double
*/
double calcMeanVolume(const stats& vec);
/*
* calcVariance()
* Calculates the variance of the volume traded in the vector of structs
* param : const stats& vec, double mean
* return : double
*/
double calcVariance(const stats& vec, double mean);
/*
* calcStandardDev()
* Calculates the standard deviation of the variance
* param : double& variance
* return : double
*/
double calcStandardDev(double& variance);
/*
* calcBestFiveDay()
* Calculates the best five day period in the vector of structs
* which is the difference between the open and close price in a series of five days.
* param : const stats& vec
* return : passBestFive struct
*/
passBestFive calcBestFiveDay(const stats& vec);
/*
* calcWorstFiveDay()
* Calculates the worst five day period in the vector of structs
* which is the difference between the open and close price in a series of five days.
* param : const stats& vec
* return : passWorstFive struct
*/
passWorstFive calcWorstFiveDay(const stats& vec);
/*
* calcBestTwentyDay()
* Calculates the best twenty day period in the vector of structs
* which is the difference between the open and close price in a series of twenty days.
* param : const stats& vec
* return : passBestTwenty struct
*/
passBestTwenty calcBestTwentyDay(const stats& vec);
/*
* calcWorstTwentyDay()
* Calculates the worst twenty day period in the vector of structs
* which is the difference between the open and close price in a series of twenty days.
* param : const stats& vec
* return : passWorstTwenty struct
*/
passWorstTwenty calcWorstTwentyDay(const stats& vec);
/*
* calcMedian()
* Calculates the median stock price from the sorted vectors of close and open values
* param : const stats& closeVals, const stats& openVals
* return : double
*/
double calcMedian(const vector<double>& vec);
/*
* quickSort()
* Sorts the vector of structs by the close or open value using the quick sort algorithm
* param : stats& vec, int low, int high, bool flag
* return : void
*/
void quickSort(vector<double>& vec, int low, int high);
/*
* partition()
* Partitions the vector of structs for the quick sort algorithm
* NOTE: Partion uses a bool paramter to determine if the vector is being sorted by close or open value
* param : stats& vec, int low, int high, bool flag
* return : int
*/
int partition(vector<double>& vec, int low, int high);
/*
* getMidpoints()
* returns a vector that is the average of the open and close values
* param vector of dailyStats
* return a vector of doubles
*/
vector<double> getMidpoints(const stats& vec);
