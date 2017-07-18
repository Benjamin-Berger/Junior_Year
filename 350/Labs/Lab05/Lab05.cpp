#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //fork
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int fd[2];

void thingy(int n){
	if(n == 1){
		return;
	} else {
		pipe(fd);
//		write(fd[1], num, strlen(num));
		thingy(n -1);
	}
}



int main(){
	int N;
	char num[100];
	int fd[2];
	char temp[100];

	printf("Enter N: ");
	fgets(num, 100, stdin);

	num[strlen(num) - 1] = '\0';

	N = atoi(num);
	
	cout << "Enter Message: ";
	char mess[100];
	fgets(mess, 100, stdin);

	if(N == 0){
		cout << mess << endl;
	} else {
		pid_t pid;
		while(N > 0){
			pid = fork();
			if(pid == 0){ //in child
				close(fd[0]);
				write(fd[1], mess, (strlen(mess)+1));
				exit(0);
			} else {
				close(fd[1]);

				N = read(fd[0], mess, sizeof(mess));
				printf("%s\n", mess);
			}
		N--;
		}
	}
}
