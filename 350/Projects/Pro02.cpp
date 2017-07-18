#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <stdio.h>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

ifstream input;
ofstream output;
sem_t sem_name, sem_two, sem_three;
queue<string> lines;
string line;

void *thrOne(void *a ){
	int value;
	input.open("tweet.txt", ifstream::in);
	cout << "after input creation" << endl;
	while(true){
		cout << lines.size() << " " << endl;
		sem_getvalue(&sem_name, &value);
		cout << value << endl;
//		sem_wait(&sem_name);
//		sem_wait(&sem_three);
		if(!input.eof()){	
			getline(input, line);
			lines.push(line);
		} else {
			lines.push("556");
			break;
			input.close();
//			sem_post(&sem_two);
//			sem_post(&sem_three);
			return NULL;
		}
//		sem_post(&sem_two);
//		sem_post(&sem_three);
	}
	input.close();
	return NULL;
}

//void *thrTwo(void *a){
//	cout << "lll" << endl;
//	output.open("output.txt", ofstream::out);
//	sem_wait(&sem_two);
//	sem_wait(&sem_three);
//	output << lines.front();
//	sem_post(&sem_name);
//	sem_post(&sem_three);
//	if(lines.front() == "556"){
//		output.close();
//		return NULL;
//	}
//
//	return NULL;
//
//}

int main(){
	sem_init(&sem_name, 0, 10);
	int k;
	sem_getvalue(&sem_name, &k);
	cout << k << endl;


	sem_init(&sem_two, 0, 0);
	sem_init(&sem_three, 0, 1);
	pthread_t t1, t2;
	
	cout << "before thread 1 creation" << endl;
	if(pthread_create(&t1, NULL, thrOne, NULL)){
		printf("nope\n");
		exit(1);
	}	
//	cout << "before thread 2 creation" << endl;
//	if(pthread_create(&t2, NULL, thrTwo, NULL)){
//		printf("nope\n");
//		exit(1);
//	}



	sleep(1);



	return 0;
}
