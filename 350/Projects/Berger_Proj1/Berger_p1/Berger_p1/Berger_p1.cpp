#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "time_functions.h"



using namespace std;

ifstream input;
ofstream output;
sem_t sem_name, sem_two, sem_three;
queue<string> lines;
string line;

void *thrOne(void *a){

	input.open(((char*)a), ifstream::in);
	while (true){
		sem_wait(&sem_name);
		sem_wait(&sem_three);
		if (!input.eof()){
			getline(input, line);
			lines.push(line);
			sem_post(&sem_two);
		}
		else {
			lines.push("556");
			//			break;
			input.close();
			sem_post(&sem_two);
			sem_post(&sem_three);
			return NULL;
		}
		sem_post(&sem_three);
	}
	input.close();
	return NULL;
}

void *thrTwo(void *a){
	output.open(((char*)a), ofstream::out);
	while (true){
		sem_wait(&sem_two);
		sem_wait(&sem_three);
		if (lines.front().length() > 0){
			if (lines.front() != "556"){
				output << lines.front() << endl;
				lines.pop();
				sem_post(&sem_name);
				sem_post(&sem_three);
			}
			else {
				output.close();
				return NULL;
			}
		}
		else {
			lines.pop();
			sem_post(&sem_name);
			sem_post(&sem_three);
		}
	}
	return NULL;

}

int main(int argc, char *argv[]){
	sem_init(&sem_name, 0, 10);
	sem_init(&sem_two, 0, 0);
	sem_init(&sem_three, 0, 1);
	pthread_t t1, t2;

	start_timing();

	if (pthread_create(&t1, NULL, thrOne, argv[1])){
		printf("nope\n");
		//		exit(1);
	}
	if (pthread_create(&t2, NULL, thrTwo, argv[2])){
		printf("nope\n");
		//		exit(1);
	}
	stop_timing();
	Sleep(1);
	printf("Wall_clock: %f\n", get_wall_clock_diff());
	printf("CPU_time: : %f\n", get_CPU_time_diff());

	int a;
	printf("Press a key and Enter to exit: ");
	scanf("%d\n", &a);

	return 0;
}
