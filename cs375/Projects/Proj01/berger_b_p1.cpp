#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <map>
#include <math.h>
#include <time.h>
using namespace std;

int main(int argc, char* argv[]){
	int i, price, cash, cashLeft, j;
	ofstream outFile;
	ifstream mrkList;
	ifstream herList;
	int numCards = 0;
	string line, name;
	stringstream ss;

	vector<string> mrkNames;
	vector<int> mrkPrices;
	vector<string> herNames;
	vector<int> herPrices;
	int profit = 0, bestProf = 0;
	vector<string> temp;
	vector<string> final;

	vector<string> best;

	map<string, int> market;
	map<string, int> her;
	time_t then, now;	


	if(argc != 5){
		cout << "Invalid entry, exiting." << endl;
	} else {
		outFile.open("output.txt");
		mrkList.open(argv[2]);
		getline(mrkList, line);
		numCards = atoi(line.c_str());	
//putting Markter prices into 2 different vectors
		for(i = 0; i < numCards; i++){
			getline(mrkList, line);
			ss.clear();
			ss << line;
			ss >> name;
//			mrkNames.push_back(name);
			ss >> price;
//			mrkPrices.push_back(price);
			market.insert(pair<string, int> (name, price));
		}

//		i = 0;
//		while(mrkNames[i] != "Player5"){
//			i++;
//		}
			

		int k = 0;


		herList.open(argv[4]);
		while(!herList.eof()){
			herNames.clear();
			herPrices.clear();
			her.clear();
			bestProf = 0;

			getline(herList, line);
			if(line.empty()){
				break;
			}
			ss.clear();
			ss << line;
			ss >> numCards;
			ss >> cash;

			for(i = 0; i < numCards; i++){
				getline(herList, line);
				ss.clear();
				ss << line;
				ss >> name;
				herNames.push_back(name);
				ss >> price;
//				herPrices.push_back(price);
				her.insert (pair<string, int> (name, price));
			}
			for(i = 0; i < herNames.size(); i++){
				if(market.count(herNames[i]) == 0){
					cout << "Error, card not found in market data!" << endl;
					return 0;
				}
			}


			time(&then);
			//both files have been read. time for math.
			for(i = 0; i < pow(2, her.size()); i++){
				cashLeft = cash;
				temp.clear();
				profit = 0;
				for(j =0; j < her.size(); j++){
					if(i & (1<<j)){
						if((cashLeft - her[herNames[j]]) >= 0 ){	
							temp.push_back(herNames[j]);
							cashLeft = cashLeft - her[herNames[j]];
							profit = profit + (market[herNames[j]] - her[herNames[j]]);
							if(profit > bestProf){
								bestProf = profit;
								final.clear();
								for(int p = 0; p < temp.size(); p++){
									final.push_back(temp[p]);
								}
							}
						}
					}
				}
			}
			time(&now);
			outFile << numCards << " " << bestProf << " " << final.size() << " " << difftime(now, then) << endl;
			for(i = 0; i < final.size(); i++){
				outFile << final[i] << endl;
			}

			if(k == 1000){
				cout << "yo fix this" << endl;
				break;
				//just in case
			}
			k++;
			
		}






		outFile.close();
		mrkList.close();
		herList.close();
	}

}
