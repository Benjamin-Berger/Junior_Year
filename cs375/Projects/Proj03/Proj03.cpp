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

vector<string> knap;
map<string, int> market;
map<string, int> her;
vector<string> herNames;
string card;
bool greed = false;
vector<int> gString1;
map<int,string> greedy1;
vector<bool> bestSet;
vector<bool> curSet;
bool promise = true;
vector<string> elim;
int count1 = 0;


vector<double> x;

int greed1(int numCards, int cash){
	gString1.clear();
	greedy1.clear();
	gString1.resize(numCards + 1);


	int bestProf = 0;
	int i, ratio;


	for(i = 1; i <= numCards; i++){
		ratio = market[herNames[i]] / her[herNames[i]];
		gString1[i] = ratio;
		greedy1.insert(pair<int, string> (ratio, herNames[i]));
	}


	//sort(gString1.begin(), gString1.end());

	sort(gString1.begin() + 1, gString1.end(), greater<int>());

	for(i = 1; i <= numCards; i++){
		if(cash - her[greedy1[gString1[i]]] >= 0){
			cash = cash - her[greedy1[gString1[i]]];
			knap.push_back(greedy1[gString1[i]]);
		}
	}


	for(i = 0; i <= knap.size(); i++){
		bestProf = bestProf + market[knap[i]];
	}


	return bestProf;
}

int greed2(int numCards, int cash){
	int bestProf = 0;
	int maxProf = greed1(numCards, cash);
	int i;
	for(i = 0; i < numCards; i++){
		if(market[herNames[i]] > bestProf && (cash - her[herNames[i]]) >= 0){
			bestProf = market[herNames[i]];
			card = herNames[i];
		}
	}

	if(bestProf > maxProf){
		maxProf = bestProf;
		knap.clear();
	} 

	return maxProf;
}

int bound1(int i, int w, int p, int cash, int numCards){
	int bound = p;
	double y, z;

		
	for(int j = i; j < numCards; j++){
		x[j] = 0;
	}


	while(w < cash && i <= numCards){ 
		if(w + her[greedy1[gString1[i]]] <= cash){
			x[i] = 1;
			w = w + her[greedy1[gString1[i]]];
			bound = bound + market[greedy1[gString1[i]]];
		} else{
			y = cash - w;
			z = her[greedy1[gString1[i]]];
			x[i] = y/z;
			w = cash;
			bound = bound + market[greedy1[gString1[i]]] * x[i];
		}
			i = i+1;
	}

	return bound;
}



void backTrack(int i, int numCards, int cash, int prof, int weight, int &max){

	count1 = count1 + 1;

	//int bound =  bound1(i, weight, prof, cash, numCards);


	// for(int l = 1; l <= numCards; l++){
	// 	cout << curSet[l];
	// }
	// cout << endl;
	//cout << "KWF: " << bound << endl << endl;
	//cout << ""



	if(weight <= cash && prof > max){
		// cout << "prof: " << prof << endl;
		// cout << "max: " << max << endl;
		max = prof;
		for(int k = 0; k < curSet.size(); k++){
			bestSet[k] = curSet[k];
		}
	}

	if(weight >= cash){
		promise = false;
		// cout << "weight > cash" << endl;
	} else {
		if(bound1(i +1, weight, prof, cash, numCards) > max){
			promise = true;
			// cout << "bound : " <<  bound1(i +1, weight, prof, cash, numCards) << endl;
		} else{
			promise = false;
			// cout << "not promise" << endl;		
		}
	}
	// cout << i << endl;



	if(promise){
		curSet[i +1] = 1;
		backTrack(i +1, numCards, cash, prof + market[greedy1[gString1[i + 1]]], weight + her[greedy1[gString1[i + 1]]], max);
		curSet[i + 1] = 0;
		backTrack(i + 1, numCards, cash, prof, weight, max);
	}
}


int main(int argc, char *argv[]){

	ofstream outFile;
	ifstream mrkList;
	ifstream herList;

	string line, name, argument;
	stringstream ss;
	int numCards = 0, bestProf = 0, maxProf = 0;
	int cash, i, price, ratio;
	time_t then, now;

	//vector<string> knap;
	bool greed = false;


	if(argc != 8){
		cout << "Invalid entry, exiting." << endl;
	} else {
		outFile.open(argv[6]);
		mrkList.open(argv[2]);
		getline(mrkList, line);
		numCards = atoi(line.c_str());	
		for(i = 1; i <= numCards; i++){
			getline(mrkList, line);
			ss.clear();
			ss << line;
			ss >> name;
			ss >> price;
			market.insert(pair<string, int> (name, price));
		}

		herList.open(argv[4]);
		while(!herList.eof()){

			getline(herList, line);
			if(line.empty()){
				break;
			}
			ss.clear();
			ss << line;
			ss >> numCards;
			ss >> cash;

			herNames.resize(numCards +1);

			for(i = 1; i <= numCards; i++){
				getline(herList, line);
				ss.clear();
				ss << line;
				ss >> name;
				herNames[i] = name;
				ss >> price;
				her.insert (pair<string, int> (name, price));
			}
			// for(i = 0; i < herNames.size(); i++){
			// 	if(market.count(herNames[i]) == 0){
			// 		cout << "Error, card not found in market data!" << endl;
			// 		return 0;
			// 	}
			// }
		}
	}

	for(int k = 1; k <= numCards; k++){
		market[herNames[k]] = market[herNames[k]] - her[herNames[k]];
	}




	argument = argv[7];
	if(argument== "0"){
		//cout << greed1(numCards, cash) << endl;
		time(&then);
		int gOut = greed1(numCards, cash);
		time(&now);
		outFile << "Greedy 1: ";
		outFile << numCards << " " << gOut << " " << difftime(now, then) << endl;
		for(int i = 0; i < knap.size(); i++){
			outFile << knap[i] << endl;
		}
	} else if(argument == "1"){
		//cout << greed2(numCards, cash) << endl;
		time(&then);
		int gOut = greed2(numCards, cash);
		time(&now);
		outFile << "Greedy 2: ";
		outFile << numCards << " " << gOut << " " << knap.size() << " "<< difftime(now, then)<< endl;
		if(knap.size() > 0){
			for(int i = 0; i < knap.size(); i++){
				outFile << knap[i] << endl;
			}
		} else{
			outFile << card << endl;
		}


	} else if(argument == "2"){
		outFile << "Backtracking: ";
		x.resize(numCards + 1);
		curSet.resize(numCards +1);
		bestSet.resize(numCards +1);

		int max = greed2(numCards, cash);
		int prof = 0;
		int cards = 0;

		time(&now);
		backTrack(0, numCards, cash, 0, 0, max);
		time(&then);
		for(int k = 1; k <= numCards; k++){
			if(bestSet[k] == true){
				prof = prof + market[greedy1[gString1[k]]];
				cards++;
			}
		}

		outFile << numCards << " " << prof << " " << cards << " " << difftime(now, then) << endl;

		long expon = pow(2,numCards) - count1;

		outFile << count1 << " subsets considered : " << expon << " avoided via backtracking" << endl;

		 for(int i = 1; i <= numCards; i++){
		 	if(bestSet[i] == 1){
		 		outFile << greedy1[gString1[i]] << endl;
		 	}
		 }

	}



	outFile.close();
	mrkList.close();
	herList.close();

}