#include <iostream>
#include <fstream>
#include <string>
#include "time_functions.h"

using namespace std;

int main(){
	string inName, outName;
	cout << "Enter input file path: ";
	cin >> inName;
	cout << "Enter output file path: ";
	cin >> outName;

	start_timing();

	ifstream inFile(inName.c_str(), ios::binary);
	ofstream outFile(outName.c_str(), ios::binary);

//	inFile.open("/Users/SnowFox/Users/Binyamin/Binyamin school/Bing 6th Sem/350/Lab01/example.txt");
//	outFile.open("output.txt");


// Said we can grab one character at a time	
	char c;
	while(inFile.get(c)){
		outFile << c;
	}

	stop_timing();
	cout << get_CPU_time_diff() << endl;


	inFile.close();
	outFile.close();









}
