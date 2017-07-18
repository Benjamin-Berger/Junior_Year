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
vector<int> matrix(1000);

int main(){
int shmid;
key_t key=1234;
//shmid=shmget(key,10*sizeof(int),0666|IPC_CREAT);
//int *b = (int*)shmat(shmid, NULL, 0);

int segment_id = shmget(key, sizeof(int),0660 | IPC_CREAT);

int* shared = (int*)shmat(segment_id,NULL,0);

if(shared == NULL){
	cout << endl;
}

pid_t pid;
int k;
int n = 0;

for(int i = 0; i < 1000; i++){
	n++;
	pid = fork();
	if(pid > 0){

		int status;
		while (n > 0) // “n” is the number of processes you created (so you have to count them as you fork)
		{
  			pid = wait(&status);
  			n--;
  		}
  		matrix[i] = shared[i];

	} else if(pid ==0){
		//b[0] = i;
		shared[i] = i*2;
		exit(0);
	}
}

for(int i = 0; i < 1000; i++){
	//matrix[i] = b[i];
	cout << matrix[i] << endl;
}



}