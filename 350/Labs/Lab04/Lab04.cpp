#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <stdlib.h>

typedef struct student {
int id;
char name[32];
char phone[16];
char address[128];
} student_t;


using namespace std;

int main(){

	char yShort[] = "y";
	char yLong[] = "yes";
	char quit[16];
	vector<string> names;
	vector<string> phones;
	vector<string> addresses;
	map<int,int> id;
	int i, k;;
	int idLine;
	string line;
	char buffer[200];
	char name[32];
	char phone[16];
	char address[128];
	FILE *input;
	input = fopen("students.txt", "r");
	size_t ln;
	bool isDig = true;
	i = 0;
	while(!feof(input)){
		fgets(buffer, 200, input);
		idLine = atoi(buffer);
		id.insert(pair<int,int>(idLine, i++));

		fgets(name, 32, input);
		fgets(phone, 16, input);
		fgets(address, 128, input);
		ln = strlen(name) - 1;
		if(name[ln] == '\n'){
			name[ln] = '\0';
		}
		ln = strlen(phone) - 1;
		if(phone[ln] == '\n'){
			phone[ln] = '\0';
		}
		ln = strlen(address) - 1;
		if(address[ln] == '\n'){
			address[ln] = '\0';
		}
		names.push_back(name);
		phones.push_back(phone);
		addresses.push_back(address);
	
	}

	while(true){
		isDig = true;	
		printf("ID >> ");
		fgets(buffer, 200, stdin);
		for(k = 0; k < strlen(buffer) -1; k++){
			if(!isdigit(buffer[k])){
				isDig = false;
			}
		}
		if(isDig){
			printf("Record: ");
			idLine = atoi(buffer);
			if(id.count(idLine) > 0){
				i = id.find(idLine)->second;
				cout << names[i] << ", " << phones[i] << ", " << addresses[i] << endl;
//		printf("%s\n", names[0]);
			} else{
				printf("Does not exist!\n");
			}
		} else {
			cout << "Invalid entry, please enter a number!" << endl;
		}	
		printf("Quit(y/n)? >> ");
		fgets(quit, 16, stdin);
		quit[strlen(quit) -1] = '\0';
		if(strcmp(quit, yShort) == 0 || strcmp(quit, yLong) == 0){
			break;
		} 
	}

	fclose(input);





}
