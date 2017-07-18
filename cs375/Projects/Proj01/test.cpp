#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


void func(vector<int> &tester, int size){
	int pSize = 2**size;
	int counter, j;

	for(counter = 0; counter < pSize; counter++){
		for(j=0; j < size; j++){
			if(counter & (1<<j)){
				cout << tester[j] << endl;;
			}
		}
	cout << endl;
	}



}



int main(){

	vector<int> tester;

	tester.push_back(1);
	tester.push_back(2);
	tester.push_back(3);
	int size = tester.size();
	func(tester, size);
	
}
