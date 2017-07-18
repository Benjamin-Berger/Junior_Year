#include <iostream>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <string.h>
//#include "time_functions.h"

using namespace std;
vector<vector<int> > matrix1(0);
vector<vector<int> > matrix2(0);
vector<vector<int> > result(0);

int numT;
int row = 0, col1 = 0, col2 = 0, mBreak = 0;

pthread_mutex_t* mut = new pthread_mutex_t;

void* test(void* arg) {
  int calc, temp1 = 0, temp2 = 0, i;

  pthread_mutex_lock(mut);
  i = *reinterpret_cast<int*>(arg);

  for(int k = 0; k < i; k++){
    temp1++;
    if(temp1 >= col1){
      temp1 = 0;
      temp2++;
    }
    if(temp2 >= col2){
      temp2 =0;
    }
  }

  //if(i == 0){
    //calc = matrix1[0][0] * matrix2[0][0];
    //result[0][0] = calc;
  //} else 
  if((i)%(col1) == 0){
//  cout << "matrix 1 " << matrix1[floor((i)/(col1 * col2))][(i)%col1];
//  cout << " * matrix 2 " << matrix2[(i)%col1][temp2]<< endl;
    calc =  matrix1[floor((i)/(col1 * col2))][(i)%col1] * matrix2[(i)%col1][temp2];
//  cout << calc << endl;
    result[floor((i)/(col1 * col2))][temp2] = calc;
  } else {
    calc =  matrix1[floor((i)/(col1 * col2))][(i)%col1] * matrix2[(i)%col1][temp2];
    result[floor((i)/(col1 * col2))][temp2] = result[floor((i)/(col1 * col2))][temp2] + calc;
  }


  pthread_mutex_unlock(mut);
  delete reinterpret_cast<int*>(arg);

  return NULL;
}

int main(int argc, char *argv[]) {
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
    size_t found = line.find('*');
    if(found != string::npos){
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

  input.close();

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
    size_t found = line.find('*');
    if(found !=string::npos){
      second = true;
    } else if(!second){
      ss.clear();
      ss << line;
      while(ss >> num){
        tCol++;
        matrix1[tRow][tCol] = atoi(num.c_str());
      }
    } else if(second){
      ss.clear();
      ss << line;
      while(ss >> num){
        tCol++;
        matrix2[tRow - mBreak][tCol] = atoi(num.c_str());
      }
    }
  }
//start_timing();

  pthread_mutex_init(mut, NULL);

  numT = (mBreak-1)*(col1) * (col2);


  vector<pthread_t*> pthreads;
  for (int i = 0; i < numT; ++i) {
    pthread_t* t1 = new pthread_t;
    pthreads.push_back(t1);
    int* t = new int(i);
    pthread_create(t1, NULL, test, t);
  }

  for (int i = 0; i < (int)pthreads.size(); ++i) {
    pthread_join(*pthreads[i], NULL);
    delete pthreads[i];
  }

//stop_timing();
  for(int j = 0; j < mBreak-1; j++){
    for(int p = 0; p < col2; p++){
      output << result[j][p] << " ";
      cout << result[j][p] << " ";
    }
    output << endl;
    cout << endl;
  }
// cout << get_wall_clock_diff() << endl;
// cout << get_CPU_time_diff() << endl;
 //printf("Wall_clock: %f\n", get_wall_clock_diff());
 //printf("CPU_time: : %f\n", get_CPU_time_diff());

  delete mut;
  input.close();
  output.close();
}
