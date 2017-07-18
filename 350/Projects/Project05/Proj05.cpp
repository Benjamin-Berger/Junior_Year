#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>
#include "time_functions.h"


int rc=0, wc=0, W = 0, R = 0;
pthread_mutex_t mutex1,mread;


using namespace std;

void *writer(void *arg)
{
	int w = *reinterpret_cast<int*>(arg);
	int s, m;
	w++;
	for(int i = 0; i < 10; i ++){
		pthread_mutex_lock(&mutex1);
		wc++;
		get_wall_time_ints(&s,&m);
		cout << ">>> DB value set to: "<< s << ":" << m << " by writer number: " << w<< endl;
//		printf(">>> DB value set to: SSS:%.3f by writer number: %d \n", &m, w);
		pthread_mutex_unlock(&mutex1);
		for(int p = 0; p < W; p++){} //just for waiting
	}
//	printf("Writer %d leaving\n",w);
	pthread_exit(0);
	
 
}

void *reader(void *arg){
	int r = *reinterpret_cast<int*>(arg);
	r++;
	int s, m;
	for(int i = 0; i < 10; i++){
		pthread_mutex_lock(&mread);
		rc++;
		if(rc==1)
		pthread_mutex_lock(&mutex1);
		pthread_mutex_unlock(&mread);
//		printf(">>> DB value read =: SSS:mmm by reader number: %d \n", r);
		get_wall_time_ints(&s,&m);
		cout << ">>> DB value read =: "<< s << ":" << m << " by reader number: " << r<< endl;
		pthread_mutex_lock(&mread);
		rc--;
		if(rc==0)
		pthread_mutex_unlock(&mutex1);
		pthread_mutex_unlock(&mread);
		for(int p = 0; p < R; p++){} // just for waiting
	}
//	printf("Reader %d leaving \n",r );
	pthread_exit(0);
}


int main(int argc, char *argv[]){
	
	int a = 0, b = 0;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	R = atoi(argv[3]);
	W = atoi(argv[4]);


	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mread,NULL);


//	int n = 5;
	vector<pthread_t*> pthreads; 

//	pthread_t* t1 = new pthread_t;	
//	int* t = new int(n);
//	pthread_create(t1, NULL, reader, t);


	for(int i = 0; i < a;i++){
		pthread_t* t1 = new pthread_t;
		pthreads.push_back(t1);
		int* t = new int(i);
		pthread_create(t1, NULL, reader, t);
	}

	for(int i = 0; i < b;i++){
		pthread_t* t1 = new pthread_t;
		pthreads.push_back(t1);
		int* t = new int(i);
		pthread_create(t1, NULL, writer, t);
	}

//	for(int i = 0; i < a;i++){
//		pthread_t* t1 = new pthread_t;
//		pthreads.push_back(t1);
//		int* t = new int(i);
//		pthread_create(t1, NULL, reader, t);
//	}
	
	
	for (int i = 0; i < (int)pthreads.size(); ++i) {
    		pthread_join(*pthreads[i], NULL);
    		delete pthreads[i];
  	}

}
