#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <math.h>

using namespace std;
vector<vector<int> > matrix1(0);
vector<vector<int> > matrix2(0);
vector<vector<int> > result(0);

int numT;
int row = 0, col1 = 0, col2 = 0, mBreak = 0;


void *mMult(void *a){
	int calc, temp1 = 0, temp2 = 0;
//	calc = matrix1[][] * matrix2[][];
	int i = *((int *) a);
	//cout << i << endl;


//the purpose of temp2 is to know which collumn I am working on for the second matrix and the resulting one. 
	for(int k = 0; k < i; k++){
		temp1++;
		if(temp1 >= col2){
			temp1 = 0;
			temp2++;
		}
		if(temp2 >= col1){
			temp2 =0;
		}
	}




	//base case so i dont have to worry about %0
	//if(i == 0){
	//	calc = matrix1[0][0] * matrix2[0][0];
	//	result[0][0] = calc;
	//	cout << "res " << result[0][0] << endl;
	//} else if((col1)%(i) == 0){
	//	calc =  matrix1[floor((i-1)/(col1 * col2))][(i-1)%col1] * matrix2[(i-1)%col1][temp2];
	//	result[floor((i-1)/(mBreak-1))][temp2] = calc;
	//} else {
	//will work on this after

//		calc = matrix1[][] * matrix2[][];
//		result[][] = result[][] + calc;
	//}
 if((i)%(col1) == 0){
    cout << "matrix 1 " << matrix1[floor((i)/(col1 * col2))][(i)%col1];
    cout << " * matrix 2 " << matrix2[(i)%col1][temp2]<< endl;
    calc =  matrix1[floor((i)/(col1 * col2))][(i)%col1] * matrix2[(i)%col1][temp2];
    cout << calc << endl;
    result[floor((i)/(col1 * col2))][temp2] = calc;
  } else {
    calc =  matrix1[floor((i)/(col1 * col2))][(i)%col1] * matrix2[(i)%col1][temp2];
    result[floor((i)/(col1 * col2))][temp2] = result[floor((i)/(col1 * col2))][temp2] + calc;
  }


	free(a);
	return NULL;
}



int main(int argc, char* argv[]){
	ifstream input;
	ofstream output;
	stringstream ss;
	string line, num;
	int tRow = -1, tCol = -1;
	bool second = false;

	input.open(argv[1]);
	output.open(argv[2]);

	//read dimentions
	while(getline(input, line)){
		row++;
		if(line == "*****"){
			mBreak = row;
			second = true;
		} else if(!second && col1 == 0){
			ss.clear();
			ss << line;
			while(ss >> num){
				col1++;
			}
		} else if(second && col2 == 0){
			ss.clear();
			ss << line;
			while(ss >> num){
				col2++;
			}
		}
	}

//	cout << "Matrix 1 is " << mBreak -1 << " X " << col1 << endl;
//	cout << "Matrix 2 is " << row - mBreak << " X " << col2 << endl;
	input.close();

	//creating 2d array
//	int matrix1[(mBreak -1)][col1];
//	int matrix2[row - mBreak][col2];
//	int result[mBreak - 1][col2];
	
	int i;


	matrix1.resize(mBreak-1);
	for(i = 0; i < mBreak-1; i++){
		matrix1[i].resize(col1);
	}
	matrix2.resize(row-mBreak);
	for(i = 0; i < row - mBreak; i++){
		matrix2[i].resize(col2);
	}
	result.resize(mBreak-1);
	for(i = 0; i < mBreak -1; i++){
		result[i].resize(col2);
	}


	input.open(argv[1]);
	second = false;
	while(getline(input, line)){
		tRow++;
		tCol = -1;
		if(line == "*****"){
			second = true;
		} else if(!second){
			ss.clear();
			ss << line;
			while(ss >> num){
				tCol++;
				matrix1[tRow][tCol] = stoi(num);
			}
		} else if(second){
			ss.clear();
			ss << line;
			while(ss >> num){
				tCol++;
				matrix2[tRow - mBreak][tCol] = stoi(num);
			}
		}
	}

	for(int i = 0; i < row -mBreak; i++){
		for(int k = 0; k < col2; k++){
//			cout << matrix2[i][k] << " ";
		}
//		cout << endl;
	}

//sending to thread
	pthread_t t1;
	numT = (mBreak-1)*(col1) * (col2);

	for(int i = 0; i < numT; i++){
		int *pas = (int*)malloc(sizeof(*pas));
		*pas = i;
	
		pthread_create(&t1, NULL, mMult, pas);
	}


	sleep(1);


	for(int j = 0; j < mBreak-1; j++){
		for(int p = 0; p < col2; p++){
			cout << result[j][p] << " ";
		}
		cout << endl;
	}

	input.close();
	output.close();
}
