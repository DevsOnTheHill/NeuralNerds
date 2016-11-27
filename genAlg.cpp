// 
//

//#include "stdafx.h" Commented out unless using Visual Studio
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <stdexcept>
#include <bitset>
using namespace std;

class chromo {
public:
	bitset<36> data; // We will be switching to strings.  They will take up more memory, but will simplify the design of the genetic algorithms.
	int fitness;
	chromo(bitset<36> in) {
		data = in;
	}

};

//Global variables declared here
char* decoded;
bitset<4> gene;
int counter;
double target = 5;
double num;
double val;
double num2;
int genSize = 10;
bool op = true;
bool number = false;
bool first = true;
bool isType = true;
bool yesNum = false;
bool prevNum = false;
char* function;
char type;
int num3;
double fitness;
int genNum=0;
int totalGens=10;
chromo*** genArr = new chromo**[totalGens];

void start() {
	genArr[genNum] = new chromo*[genSize];
	int a;
	//char *input;
	bitset<36> input;
	//input = new char[39];
	for (int i = 0; i < genSize; i++) {

		for (int x = 0; x < 36; x++) {
			a = rand() % 2;
			if (a == 1) {
				input.set(x, 1);
			}
			else {
				input.set(x, 0);
			}
		}
		//cout << input << endl;
		genArr[genNum][i] = new chromo(input);
		//cout << generation[i]->data << endl;
		;
	}
	
	genNum++;
}


double getNum(char n) {
	switch (n) {
	case'0': num3 = 0; break;
	case'1': num3 = 1; break;
	case'2': num3 = 2; break;
	case'3': num3 = 3; break;
	case'4': num3 = 4; break;
	case'5': num3 = 5; break;
	case'6': num3 = 6; break;
	case'7': num3 = 7; break;
	case'8': num3 = 8; break;
	case'9': num3 = 9; break;
	default: break;
	}
	return num3;

}

//DECODE(chromo)  This function will take a chromo argument and return the fitness value for that chromo
double decode(chromo c) {

	decoded = new char[10];
	counter = 0;
	fitness = 0;
	for (int i = 0; i < 32; i++) {

		for (int x = 0; x<4; x++) {
			gene.set(x, c.data[x + i]);// = c.data[i];
		}
		if ((i) % 4 == 0 || i == 31) {
			if (gene == (bitset<4>)(string("0000"))) {
				decoded[counter] = '0';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0001"))) {
				decoded[counter] = '1';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0010"))) {
				decoded[counter] = '2';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0011"))) {
				decoded[counter] = '3';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0100"))) {
				decoded[counter] = '4';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0101"))) {
				decoded[counter] = '5';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0110"))) {
				decoded[counter] = '6';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0111"))) {
				decoded[counter] = '7';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1000"))) {
				decoded[counter] = '8';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1001"))) {
				decoded[counter] = '9';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1010"))) {
				decoded[counter] = '+';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1011"))) {
				decoded[counter] = '-';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1100"))) {
				decoded[counter] = '*';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1101"))) {
				decoded[counter] = '/';
				counter++;
			}
			else { //This is serving as our null character in the string if the data is unintelligble.
				decoded[counter] = 'a';
				counter++;
			}
		}





	}


	decoded[9] = '\0';
	val = 0;
	num = 0;
	number = false;
	op = true;
	first = true;
	counter = 0;
	type = 'n';

	for (int i = 0; i < 9; i++) {
		if (type == 'n') {
			switch (decoded[i]) {
			case'0': type = 'o'; counter++; break;
			case'1': type = 'o'; counter++; break;
			case'2': type = 'o'; counter++; break;
			case'3': type = 'o'; counter++; break;
			case'4': type = 'o'; counter++; break;
			case'5': type = 'o'; counter++; break;
			case'6': type = 'o'; counter++; break;
			case'7': type = 'o'; counter++; break;
			case'8': type = 'o'; counter++; break;
			case'9': type = 'o'; counter++; break;
			default: type = 'n'; break;
			}
		}
		else if (type == 'o'&&i != 8) {
			switch (decoded[i]) {
			case'+': type = 'n'; counter++; break;
			case'-': type = 'n'; counter++; break;
			case'*': type = 'n'; counter++; break;
			case'/': type = 'n'; counter++; break;
			default: type = 'o'; break;
			}
		}



	}
	isType = true;
	yesNum = false;
	prevNum = false;
	function = new char[counter + 1];
	function[counter] = '\0';
	counter = 0;
	type = 'n';

	for (int i = 0; i < 9; i++) {
		if (type == 'n') {
			switch (decoded[i]) {
			case'0': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'1': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'2': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'3': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'4': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'5': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'6': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'7': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'8': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'9': type = 'o'; function[counter] = decoded[i]; counter++; break;
			default: type = 'n'; break;
			}
		}
		else if (type == 'o'&&i != 8) {
			switch (decoded[i]) {
			case'+': type = 'n'; function[counter] = decoded[i]; counter++; break;
			case'-': type = 'n'; function[counter] = decoded[i]; counter++; break;
			case'*': type = 'n'; function[counter] = decoded[i]; counter++; break;
			case'/': type = 'n'; function[counter] = decoded[i]; counter++; break;
			default: type = 'o'; break;
			}
		}




	}








	for (int i = 0; i < counter; i++) {
		switch (function[i]) {
		case'+': num2 = getNum(function[i + 1]); val += num2; break;
		case'-': num2 = getNum(function[i + 1]); val -= num2; break;
		case'*': num2 = getNum(function[i + 1]); val *= num2; break;
		case'/': num2 = getNum(function[i + 1]); if (num2 != 0) { val /= num2; }
				 else {} break;
		default:  break;
		}
		if (first) {
			val = getNum(function[i]);
			first = false;
		}

	}



	

	cout << endl;
	cout << "---------------------------------------------------------" << endl;
	//if (val == target) {
	//	fitness = 1;
	//	cout << "solution found: " << endl;
		
	//}
	//else {
		
		
//	}
	fitness = (1 / (target - val));
	cout << "Chromosome data: " << c.data << endl;
	cout << "characters: " << decoded << endl;
	cout << "function: "<< function << endl;
	cout << "solution: " << val << endl;
	cout << "Fitness: " << fitness << endl;
	cout << "---------------------------------------------------------" << endl;



	



	


	delete[] decoded;
	delete[] function;

	return fitness;
}





int main()
{
	start();
	cout << "Generation complete. Decoding..." << endl;
	//bitset<4> test;
	//test.set(1, 1);
	//bitset<4> t2(string("0010"));
	//if (test == (bitset<4>)(string("0010"))) {//I can compare bitsets like this
	//if (test == t2) {
	//	cout << "Success" << endl;
	//}
	//cout << test << endl;
	int maxFitness = 0;
	int fit = 0;
	int fitnum=0;
	chromo *fittest;
	for (int i = 0; i < genSize; i++) {
		fit = decode(*genArr[0][i]); 		//Note deserved here. Because Decode prints the data, we're getting a ton of values, Want to make this more efficient.
		if (maxFitness < fit) {
			maxFitness = fit;
			fittest = genArr[0][i];
			fitnum = i;

		}
	}
	//	if (fit == 1) {
	//		break;
		//}
		//cout << "pass" << endl;
	
	/*  We need a way to check for finding a solution, I don't have perfect understanding of the code yet. */

	// cout << "Solution found";
	// cout << " on try #"<<fitnum;}
	// cout << "Max fitness: " << maxFitness << endl; //changed fitness to maxFitness, allowing for tracking the fittest score
	

	//int l = 0 % 4;
	//cout << l << endl;
	//cout << "pass" << endl;
	int end;
	cin >> end;// This serves as a check to see if the second generation iteration works. If so, it can continue until all memorty is allocated.

	start(); //2nd Gen should start here

	
	for (int i = 0; i < genSize; i++) {
		fit = decode(*genArr[1][i]); 		//Note deserved here. Because Decode prints the data, we're getting a ton of values, Want to make this more efficient.
		if (maxFitness < fit) {
			maxFitness = fit;
			fittest = genArr[1][i];
			fitnum = i;

		}
	}


	int end2;
	cin >> end2;
	return 0;
}

