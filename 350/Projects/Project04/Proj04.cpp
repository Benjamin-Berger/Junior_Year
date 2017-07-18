#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>


using namespace std;

vector<vector<int> > matrix1(0);
vector<vector<int> > matrix2(0);
vector<vector<int> > result(0);

int numT;
int row = 0, col1 = 0, col2 = 0, mBreak = 0;


int main(int argc, char *argv[]){
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

  input.clear();
  input.seekg(0,ios::beg);

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

  numT = (mBreak-1)*(col1) * (col2);

int shmid;
//int *shm_ptr;
int *a;
key_t key=1234;

//shmid=shmget(key,3*sizeof(int),0666|IPC_CREAT);
//shm_ptr=(int *)shmat(shmid,(void *)0,0);
//a = shm_ptr;

//int *b = (int*)shmat(shmid, NULL, 0);

int segment_id = shmget(key, sizeof(int),0660 | IPC_CREAT);

int* shared = (int*)shmat(segment_id,NULL,0);



	int n = 0;
	pid_t pid;
  for(int i = 0; i < numT; i++){

  	pid = fork();
   if(pid < 0) {
        printf("Error");
        exit(1);
    } else if(pid > 0){
    	n++;
    	int calc, temp1 = 0, temp2 = 0, p;
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
		int status;
		while (n > 0) // “n” is the number of processes you created (so you have to count them as you fork)
		{
  			pid = wait(&status);
  			n--;
  		}

    	result[floor((i)/(col1 * col2))][temp2] = result[floor((i)/(col1 * col2))][temp2] + shared[i];
		wait(NULL);
    }else if (pid == 0) {
    	int calc, temp1 = 0, temp2 = 0;
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
  	//*a =  matrix1[floor((i)/(col1 * col2))][(i)%col1] * matrix2[(i)%col1][temp2];
  	shared[i] = matrix1[floor((i)/(col1 * col2))][(i)%col1] * matrix2[(i)%col1][temp2];
    //result[floor((i)/(col1 * col2))][temp2] = result[floor((i)/(col1 * col2))][temp2] + calc;
    //*a = calc;
      		//cout << "hi" << endl;
  		//cout << i << ": " << *a << endl;

        exit(0); 
    } 
  }





  for(int j = 0; j < mBreak-1; j++){
    for(int p = 0; p < col2; p++){
      output << result[j][p] << " ";
      cout << result[j][p] << " ";
    }
    output << endl;
    cout << endl;
  }


  input.close();
  output.close();

}
