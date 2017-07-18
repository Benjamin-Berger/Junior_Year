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


struct vecs{
        vector<int> A;
        vector<int> B;
        vector<int> C;
};

int main(){

        srand(time(NULL));
        struct vecs version2;

        version2.A.resize(100000);
        version2.B.resize(100000);
        version2.C.resize(100000);

        for(int i = 0; i < version2.A.size(); i++){
                version2.A[i] = rand() % 1000 + 1;
                version2.B[i] = rand() % 1000 + 1;
        }


	start_timing();
        int k;
        k = syscall(310 ,0);
        cout << "Ignore this: " <<k << endl;
        for(int i = 0; i < version2.A.size(); i++){
                version2.C[i] = version2.A[i] * version2.B[i];
        }
        k = syscall(310,1);
        cout << "Number of page faults: " << k << endl;
	stop_timing();
	cout << "CPU time: " <<  get_CPU_time_diff() << endl;
}

