#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include </usr/include/unistd.h>
#include "time_functions.h"


using namespace std;

int main(){



        srand(time(NULL));

        vector<int> A(100000);
        vector<int> B(100000);
        vector<int> C(100000);

        for(int i = 0; i < A.size(); i++){
                A[i] = rand() % 1000 + 1;
                B[i] = rand() % 1000 + 1;
        }
        int k;
	start_timing();

        k = syscall(310 ,0);
	cout << "Ignore this: " << k << endl;
        for(int i = 0; i < A.size(); i++){
                C[i] = A[i] * B[i];
        }
        k = syscall(310,1);
        cout << "Number of page faults: " <<  k << endl;
	stop_timing();
	cout << "CPU time: " << get_CPU_time_diff() << endl;
}


