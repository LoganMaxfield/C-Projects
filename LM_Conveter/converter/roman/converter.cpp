/*
*Name:Logan Maxfield
*Purpose: Take a string from the user and convert it approptiately, either from roman to arabic, arabic	
*		  to roman, or convert apostrophus to arabic. Repeat until the user enter 'quit'.
*Date: 2025-01-28
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string getUserInput();
bool isNumber(string userInput);
bool isApostrophus(string userInput);
double convertToArabic(string userInput);
string convertToRoman(string userInput);
string convertDigits(double num);
string convertDecimalValue(double userNum);
string convertApostrophus(string userInput);
double vinculumToArabic(int i, string userInput);
string removeTrailingZeros(string valToReturn);

//Constant value to hold the '.' value for roman numerals
constexpr double TWELFTH_FRACTION_VALUE = 1.0 / 12.0;

int main() {
	//print header to user
	cout << "Roman/Arabic converter, (c) 2025 - Logan Maxfield\n";
	cout << "type 'quit' to exit\n\n";

	string userInput{};
	string numPrinted{};

	while(1)
	{
		userInput = getUserInput();
		
		//If arabic to roman
		if (isNumber(userInput)) {
			numPrinted = convertToRoman(userInput);
			cout << userInput << " converted to roman is: " << removeTrailingZeros(numPrinted) << endl;
		}
		//Apostrophus
		else if (isApostrophus(userInput)) {
			cout << userInput << " converted to arabic is: " << convertApostrophus(userInput) << endl;
		}
		//roman to arabic
		else {
			numPrinted = to_string(convertToArabic(userInput));
			cout << userInput << " converted to arabic is: " << removeTrailingZeros(numPrinted) << endl;
		}

	}
}//end main

/*
* Name: convertToArabic()
* Purpose: Convert a string of roman numerals into an arabic number
* Return: a double
* Param: string
*/
double convertToArabic(string userInput) { 
	

	//useful variables
	double numToReturn{};
	char currentChar{};
	double currentValue{};
	double previousValue = 0;

	//for each char of the string convert it to its arabic value
	//NOTE we go from smallest to largest to make accounting for the subtraction rule easier.
	for(int i = userInput.length() - 1; i >= 0; i--) {
		currentValue = 0;
		currentChar = userInput[i];

		switch (currentChar) {
		case 'M': 
			currentValue += 1000;
			break;
		case 'D': 
			currentValue += 500;
			break;
		case 'C': 
			currentValue += 100;
			break;
		case 'L': 
			currentValue += 50;
			break;
		case 'X': 
			currentValue += 10;
			break;
		case 'V': 
			currentValue += 5;
			break;
		case 'I': 
			currentValue += 1;
			break;
		case 'S': 
			currentValue += 0.5;
			break;
		case '.': 
			currentValue += TWELFTH_FRACTION_VALUE;
			break;
		case '_': 
			//If we encounter a vinculum marker, we send the current state of i, as well as the string
			//to a helper method so we can convert the remainder of the string and multiply it by 1000.
			//Then add it to the amount we already converted
			return vinculumToArabic(i, userInput) + numToReturn;
			break;
		}

		//If previous number is larger than current, subtract
		if (previousValue > currentValue)
			numToReturn -= currentValue;
		//else we add
		else
			numToReturn += currentValue;

		//set new previous value
		previousValue = currentValue;
	}//end for


	return numToReturn;

}//end convertToArabic()

/*
* Name: Logan Maxfield	
* Purpose: This helper function takes the current state of the converted string from convertToArabic() and does the remaining
*		   conversions AND multiplies the result by 1000.
* Return: a double
* Param: an int, a string
*/
double vinculumToArabic(int i, string userInput) {
	char currentChar = ' ';
	double previousValue{};
	double currentValue{};
	double numToReturn{};

	//Same conversion as before
	for (int j = 0; j < i; j++) {
		currentChar = userInput[j];

		switch (currentChar) {
		case 'M':
			currentValue = 1000;
			break;
		case 'D':
			currentValue = 500;
			break;
		case 'C':
			currentValue = 100;
			break;
		case 'L':
			currentValue = 50;
			break;
		case 'X':
			currentValue = 10;
			break;
		case 'V':
			currentValue = 5;
			break;
		case 'I':
			currentValue = 1;
			break;
		}

		//If previous number is larger than current, subtract
		if (previousValue < currentValue)
				numToReturn += currentValue - (previousValue * 2);
		//else we add
		else
			numToReturn += currentValue;

		//set new previous value
		previousValue = currentValue;

		}//end for
	//Multiply the translated value by 1000, for the vinculum
	return numToReturn * 1000;
}

/*
* Name: convertToRoman()
* Purpose: Converts the number passed into a string of roman numerals using two helper functions.
* Return: a string of roman numerals
* Param: a string
*/
string convertToRoman(string userInput) {

	//Convert string of numbers to a double and initialize variables
	double userNum = stod(userInput);
	double decimalPortion = userNum - static_cast<int>(userNum);
	string strToReturn{};
	
	//If working with large numbers, account for vinculum notations
	if (userNum >= 4000.0) {
		//First Convert everything above the thousands
		double temp = userNum / 1000;
		strToReturn = convertDigits(temp) + '_';
		//Then deal with 1s,10s,100s
		strToReturn.append(convertDigits(static_cast<int>(userNum) % 1000));
	}
	else {
		strToReturn = convertDigits(userNum);
	}
	//IF decimals exist convert them to roman numerals with helper function
	if(decimalPortion > 0)
		strToReturn.append(convertDecimalValue(decimalPortion));

	return strToReturn;

}//end convertToRoman()

/*
* Name: isNumber()
* Purpose: This function checks each char of a string to see if it is a numeric digit
* Return: true if only numeric digits or false if non-numeric chars are found
* Param: string
*/
bool isNumber(string userInput) {
	
	//Evaluate if each char of the string is a digit
	for (int i = 0; i < userInput.length(); i++) {
		if (!isdigit(userInput[i]) && userInput[i] != '.') {
			return false;
		}
	}
	return true;
}//end isNumber()

/*
* Name: convertDigits()
* Purpose: This helper function converts the number passed to a string of roman numerals.
*			this is done by dividing the number by the largest of the roman numerals and working
*			our way down and adding a roman numeral to a string for each division
* Return: a string
* Param: a string
*/
string convertDigits(double num) {
	
	string strToReturn{};

	//Handle numbers greater than 1000 and work our way down.
	while (num >= 1000) {
		strToReturn.append("M");
		num -= 1000;
	}
	if (num >= 900) {
		strToReturn.append("CM");
		num -= 900;
	}
	if (num >= 500) {
		strToReturn.append("D");
		num -= 500;
	}
	if (num >= 400) {
		strToReturn.append("CD");
		num -= 400;
	}

	//Since we could have multiple 100's here use a loop
	while (num >= 100) {
		strToReturn.append("C");
		num -= 100;
	}
	if (num >= 90) {
		strToReturn.append("XC");
		num -= 90;
	}
	if (num >= 50) {
		strToReturn.append("L");
		num -= 50;
	}
	if (num >= 40) {
		strToReturn.append("L");
		num -= 40;
	}

	//Same exception here, use loop
	while (num >= 10) {
		strToReturn.append("X");
		num -= 10;
	}
	if (num >= 9) {
		strToReturn.append("IX");
		num -= 9;
	}
	if (num >= 5) {
		strToReturn.append("V");
		num -= 5;
	}
	if (num >= 4) {
		strToReturn.append("IV");
		num -= 4;
	}
	//Get remaining 1's
	while (num >= 1) {
		strToReturn.append("I");
		num -= 1;
	}

	return strToReturn;

}//end convertDigits()

/*
* Name: convertDecimalValue()
* Purpose: This helper function takes the fractional portion of userInput and converts it into the corresponding
*		   digits, being 'S' for 0.5 or '.' for 1/12
* Return: A string
* Param: a double
*/
string convertDecimalValue(double userNum) {
	
	string strToReturn{};
	//Convert strictly the fractional portion of userInput
	if(userNum >= 0.5){
		strToReturn.append("S");
		userNum -= 0.5;
	}
	while (userNum >= TWELFTH_FRACTION_VALUE) {
		strToReturn.append(".");
		userNum -= TWELFTH_FRACTION_VALUE;
	}

	return strToReturn;
}//end convertDecimal()

/*
* Name: getUserInput()
* Purpose: This function prompts the user for input and reads it into variable userInput 
*			call toUpper on each char of userInput.
* Return: a string
* Param: none
*/
string getUserInput() {

	//Ask user for input
	string userInput{};
	cout << "please enter a roman or arabic number: ";
	cin >> userInput;

	for (size_t i = 0; i < userInput.length(); i++)
		userInput[i] = toupper(userInput[i]);		

	//If userInput = 'quit' exit program.
	if (userInput._Equal("QUIT")) {
		exit(0);
	}
	return userInput;
}

/*
* Name: isApostrophus()
* Purpose: Evaluate the passed string and check if it contains apostrophus notation.
* Return: boolean
* Param: a string
*/
bool isApostrophus(string userInput) {

	//Parse string to check if it contains the ')' character
	for (int i = 0; i < userInput.length(); i++) {
		if (userInput[i] == ')') {
			return true; //If string contains ')' it must be an Apostrophus string.
		}
	}

	return false;
}//end isApostrophus

/*
* Name: convertApostrophus()
* Purpose: To take a string of apostrophus numerals from the user and return the value in one of the 2 scenarios
*		   Balanced and unbalanced.
* Return: a string
* Param: a string
*/
string convertApostrophus(string userInput) {
	

	//Initialize Variables
	int lastIndexOfPar{};
	int cCounter{};
	int dCounter{};
	double calcValue{500};
	string temp{};

	//Parse string for amount of 'C's and ')'s as well as the last index of ')'
	for (int i = 0; i < userInput.length(); i++) {
		if (userInput[i] == ')') {
			dCounter++;
			lastIndexOfPar = i;
		}
		//Only count 'C' for the first half of the string
		if (userInput[i] == 'C' && i < (userInput.length() / 2) + 1) {
			cCounter++;
		}
	}//end for	

	//convert the extra numerals after the apostrophus to an arabic number
	string tempString = userInput.substr(lastIndexOfPar + 1, userInput.length());
	double valueToReturn = convertToArabic(tempString);

	//Branch 1 : Balanced Apostrophus		 
	//			 for each pair of 'C' and ')' after the first "CI)" (which is 1000), multiply that by 10
	if (cCounter == dCounter) {
		calcValue = 1000;
		if (cCounter == 1 && dCounter == 1) {
			temp = to_string(calcValue);
		}
		else {
			for (int i = 0; i < cCounter - 1; i++)// -1 for the original "CI)"
				calcValue *= 10;

			temp = to_string(valueToReturn + calcValue); //Convert the value to a string to remove trailing zeroes.
		}
		return removeTrailingZeros(temp);
	}
	//Branch 2 Unbalanced Apostrophus
	else {
		if (userInput[0] == 'C')//Initlaize for forward 'C' case
			calcValue = 1000;

		else if (userInput[0] == 'I')//Initialize for no forward 'C'
			calcValue = 500;

		double initialBonusPar{ 500 }; //Initialize the first additional ')' value

		if (cCounter > 0) {
			//Multiply by 10 for each 'C'
			for (int i = 0; i < cCounter - 1; i++) {
				calcValue *= 10;
			}
			//IF there are extra ')' multiply the initaialBonusPar(500) by 10 for each extra ')'
			while (dCounter - cCounter > 1) {
				initialBonusPar *= 10;
				--dCounter;
			}
			calcValue += initialBonusPar;
		}

		//For the case of no leading 'C' multiply the value by 10 for each ')'
		else {
			for (int i = 0; i < dCounter - 1; i++) {
				calcValue *= 10;
			}
		}

		temp = to_string(valueToReturn + calcValue);
		return removeTrailingZeros(temp);
	}
}// end convertApostrophus()

/*
* Name: removeTrailingZeros()
* Purpose: Take a string and remove all trailing zeroes, if present remove the extra '.'
* Return: a string
* Param: a string
*/
string removeTrailingZeros(string valToReturn) {
	//Find and store the last digit that IS NOT '0'
	int marker = valToReturn.find_last_not_of('0');
	//Erase everything from that marker + 1 (being the first 0) to the end of the string
	valToReturn.erase(marker + 1, valToReturn.size());
	//In the case that we have a leftover '.' remove it.
	if (valToReturn[marker] == '.') {
		valToReturn.erase(marker);
	}
	return valToReturn;
}
