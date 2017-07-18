//Benjamin Berger

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]){
	if(argc == 3){

		string line, word;
		ifstream myFile (argv[1]);
		ofstream outFile (argv[2]);
		stringstream ss;
		int x;
		vector<int> numbers;
		vector<int> results;
		// vector<int> first;

		if(myFile.is_open()){
			while(getline(myFile, line)){
				ss.clear();
				ss << line;
				ss >> x;
				numbers.push_back (x);
				// cout << x << endl;

			}
		}
		myFile.close();

		for(int i = 0; i < numbers.size(); i++){
			for(int j = 0; j < numbers.size(); j++){
				for(int k = 0; k < numbers.size(); k++){
					if(numbers[i] == numbers[j] - numbers[k]){
						if((i != j) && (j != k) && (i !=k)){
							results.push_back (numbers[i]);
							results.push_back (numbers[j]);
							results.push_back (numbers[k]);
						}
					}
				}
			}
		}

		// for(int i = 0; i < results.size (); i = i + 3){
		// 	first.push_back (results[i]);
		// }


		// sort(first.begin(), first.end());

		// for(int i = 0; i < first.size();i++){
		// 	cout << first[i] << endl;
		// }


		// for(int i = 0; i < first.size(); i++){
		// 	for(int p = 0; p < results.size(); p = p + 3){
		// 		if(first[i] == results[p]){
		// 			outFile << results[p] << " " << results[p + 1] << " " << results[p +2] << endl;
		// 		}
		// 	}
		// }


		if(results.size () > 0){
			for(int p = 0; p < results.size(); p = p + 3){
				outFile << results[p] << " " << results[p + 1] << " " << results[p +2] << endl;
			}
		}





	}
		return 0;
}