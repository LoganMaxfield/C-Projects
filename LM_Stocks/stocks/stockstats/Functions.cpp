#include "stockstats.hpp"

void readStockFile(string fileName, stats& stockstats) {

	ifstream inFile;
	inFile.open(fileName);
	//if file fails to open exit program
	if (!inFile) {
		cerr << "Error: failed to open file" << endl;
		exit(1);
	}

	string temporary = "";
	getline(inFile, temporary); //skip the first line

	string line;
	//read each line to a string, then take each portion of the string we need and store it in a struct
	//at the end add that struct to the vector.
	while (getline(inFile, line)) {
		istringstream iss(line);
		dayStats temp;
		getline(iss, temp.date, ' ');
		getline(iss, temporary, ',');

		getline(iss, temporary, ',');
		temp.openValue = stod(temporary);

		getline(iss, temporary, ',');
		temp.highValue = stod(temporary);

		getline(iss, temporary, ',');
		temp.lowValue = stod(temporary);

		getline(iss, temporary, ',');
		temp.closeValue = stod(temporary);

		getline(iss, temporary, ',');
		temp.volumeTraded = stoi(temporary);

		stockstats.push_back(temp);
	}
	inFile.close();
}

passBackLow findLowestValue(const stats& vec) {
	passBackLow temp;
	temp.lowestVal = vec[0].lowValue;//Initialize the lowest value to the first value in the vector
	//Loop through the other elements to find lowest value
	for (size_t i = 1; i < vec.size(); i++)
	{
		if (vec[i].lowValue < temp.lowestVal) {
			temp.lowestVal = vec[i].lowValue;
			temp.date = vec[i].date;
		}
	}
	return temp;
}

passBackHigh findHighestValue(const stats& vec) {
	passBackHigh highestValue;
	highestValue.highestVal = vec[0].highValue;//Initialize the highest value to the first value in the vector
	//Loop through the other elements to find highest value
	for (size_t i = 1; i < vec.size(); i++)
	{
		if (vec[i].highValue > highestValue.highestVal) {
			highestValue.highestVal = vec[i].highValue;
			highestValue.date = vec[i].date;
		}
	}
	return highestValue;
}

passLowVol findLowestVolume(const stats& vec) {
	passLowVol lowVol;
	lowVol.lowVol = vec[0].volumeTraded;//Initialize the lowest volume to the first value in the vector
	//Loop through the other elements to find lowest volume
	for (size_t i = 1; i < vec.size(); i++)
	{
		if (lowVol.lowVol > vec[i].volumeTraded) {
			lowVol.lowVol = vec[i].volumeTraded;
			lowVol.date = vec[i].date;
		}
	}
	return lowVol;
}

passHighVol findHighestVolume(const stats& vec) {
	passHighVol highVol;
	highVol.highVol = vec[0].volumeTraded;//Initialize the highest volume to the first value in the vector
	//Loop through the other elements to find highest volume
	for (size_t i = 1; i < vec.size(); i++)
	{
		if (highVol.highVol < vec[i].volumeTraded) {
			highVol.highVol = vec[i].volumeTraded;
			highVol.date = vec[i].date;
		}
	}
	return highVol;
}

double calcMeanClose(const stats& vec) {
	double mean;
	double sum = vec[0].closeValue;//Initialize the sum to the first value in the vector
	//add the rest of the values to the sum
	for (size_t i = 1; i < vec.size(); i++) {
		sum += vec[i].closeValue;
	}
	//divide the sum by the number of elements in the vector to get the mean
	mean = sum / vec.size();
	return mean;
}

double calcMeanVolume(const stats& vec) {
	double mean;
	long long sum = vec[0].volumeTraded;//Initialize the sum to the first value in the vector
	//add the rest of the values to the sum
	for (size_t i = 1; i < vec.size(); i++) {
		sum += vec[i].volumeTraded;
	}
	//divide the sum by the number of elements in the vector to get the mean
	mean = static_cast<double>(sum) / vec.size();
	return mean;
}

double calcVariance(const stats& vec, double mean) {
	double variance{};
	double sum{};
	//loop through the vector and add the squared difference between the value and the mean to the sum
	for (size_t i = 0; i < vec.size(); i++) {
		sum += pow(static_cast<double>(vec[i].volumeTraded) - mean, 2);
	}
	//divide the sum by the number of elements in the vector to get the variance
	variance = sum / vec.size();
	return variance;
}

double calcStandardDev(double& variance) {
	return sqrt(variance);//return the square root of the variance to get the standard deviation
}

passBestFive calcBestFiveDay(const stats& vec) {
	passBestFive bestFiveDay;
	bestFiveDay.bestFive;
	double close{};
	double open{};
	double difference = vec[4].closeValue - vec[0].openValue;//initialize the difference to the first five day difference
	//loop through the vector and find the best five day period
	for (size_t i = 1; i < vec.size() - 4; i++) {
		open = vec[i].openValue;
		close = vec[i + 4].closeValue;
		difference = close - open;

		if (bestFiveDay.bestFive < difference) {
			bestFiveDay.bestFive = difference;
			bestFiveDay.dateOpen = vec[i].date;
			bestFiveDay.dateClose = vec[i + 4].date;
		}
	}
	return bestFiveDay;
}

passWorstFive calcWorstFiveDay(const stats& vec) {
	passWorstFive worstFiveDay;
	worstFiveDay.worstFive;
	double close{};
	double open{};
	double difference = vec[4].closeValue - vec[0].openValue;//initialize the difference to the first five day difference
	//loop through the vector and find the worst five day period
	for (size_t i = 1; i < vec.size() - 4; i++) {
		open = vec[i].openValue;
		close = vec[i + 4].closeValue;
		difference = close - open;
		if (worstFiveDay.worstFive > difference) {
			worstFiveDay.worstFive = difference;
			worstFiveDay.dateOpen = vec[i].date;
			worstFiveDay.dateClose = vec[i + 4].date;
		}
	}
	return worstFiveDay;
}

passBestTwenty calcBestTwentyDay(const stats& vec) {
	passBestTwenty bestTwentyDay;
	bestTwentyDay.bestTwenty;
	double close{};
	double open{};
	double difference = vec[19].closeValue - vec[0].openValue;//initialize the difference to the first twenty day difference
	//loop through the vector and find the best twenty day period
	for (size_t i = 1; i < vec.size() - 19; i++) {
		open = vec[i].openValue;
		close = vec[i + 19].closeValue;
		difference = close - open;

		if (bestTwentyDay.bestTwenty < difference) {
			bestTwentyDay.bestTwenty = difference;
			bestTwentyDay.dateOpen = vec[i].date;
			bestTwentyDay.dateClose = vec[i + 19].date;
		}
	}
	return bestTwentyDay;
}

passWorstTwenty calcWorstTwentyDay(const stats& vec) {
	passWorstTwenty worstTwentyDay;
	worstTwentyDay.worstTwenty;
	double close{};
	double open{};
	double difference = vec[19].closeValue - vec[0].openValue;//initialize the difference to the first twenty day difference
	//loop through the vector and find the worst twenty day period
	for (size_t i = 1; i < vec.size() - 19; i++) {
		open = vec[i].openValue;
		close = vec[i + 19].closeValue;
		difference = close - open;
		if (worstTwentyDay.worstTwenty > difference) {
			worstTwentyDay.worstTwenty = difference;
			worstTwentyDay.dateOpen = vec[i].date;
			worstTwentyDay.dateClose = vec[i + 19].date;
		}
	}
	return worstTwentyDay;
}

double calcMedian(const vector<double>& vec) {
	size_t midpoint = vec.size() / 2;
	//If even number of elements, take the average of the two middle elements of the open and close
	if (vec.size() % 2 == 0) 
		return (vec[midpoint] + vec[midpoint - 1]) / 2;
	//If odd number of elements, take the middle elements of the open and close and get the average
	else 
		return vec[midpoint];
}

void quickSort(vector<double>& vec, int low, int high) {
	if (low < high) {
		//partition the vector
		int partitionIndex = partition(vec, low, high);
		//recursively call quicksort on the two halves of the vector
		quickSort(vec, low, partitionIndex - 1);
		quickSort(vec, partitionIndex + 1, high);
	}
}

int partition(vector<double>& vec, int low, int high) {
		//set the pivot
		double pivot = vec[high];
		int i = (low - 1);
		//loop through the vector and swap elements if they are less than the pivot
		for (int j = low; j <= high - 1; j++) {
			if (vec[j] < pivot) {
				i++;
				swap(vec[i], vec[j]);
			}
		}
		//swap the pivot with the element at i+1
		swap(vec[i + 1], vec[high]);
		return (i + 1);
}

vector<double> getMidpoints(const stats& vec) {
	vector<double> midpoints;
	double temp;
	for (size_t i = 0; i < vec.size(); i++) {
		temp = vec[i].closeValue + vec[i].openValue;
		midpoints.push_back(temp / 2);
	}
	return midpoints;
}





