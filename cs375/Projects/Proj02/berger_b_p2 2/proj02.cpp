#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

string dumb;
int k, p;
int num, numCont;
int numCurr = 0;

vector<int> locHeap;


void ordHeap(int k, int minHeap[][2]){
	int small, location;
	if(locHeap[k] > 1){
		if(locHeap[k] < 4){
			if(minHeap[locHeap[k]][1] < minHeap[1][1]){
				small = minHeap[locHeap[k]][1];
				location = locHeap[k];
				minHeap[locHeap[k]][1] = minHeap[1][1];
				minHeap[locHeap[k]][0] = minHeap[1][0];
				locHeap[k] = 1;
				minHeap[1][1] = small;
				minHeap[1][0] = k;
				locHeap[1] = location;
			}
		} else {
			if(minHeap[locHeap[k]][1] < minHeap[(k - (k%2))/2 ][1]){
				small = minHeap[locHeap[k]][1];
				location = locHeap[k];
				minHeap[locHeap[k]][1] = minHeap[(k-(k%2))/2][1];
				minHeap[locHeap[k]][0] = minHeap[(k-(k%2))/2][0];
				locHeap[k] = (k-(k%2))/2;
				locHeap[minHeap[(k-(k%2))/2][0]] = location;
				minHeap[(k-(k%2))/2][1] = small;
				minHeap[(k-(k%2))/2][0] = k;
				ordHeap((k-(k%2))/2, minHeap);
			}
		}


	}


}



void fndCont(string line, int minHeap[][2], ofstream& outfile){

 //parse the contestent id
	num = line.find(">");
	dumb = line.substr(16,num);
	k = stoi(dumb);

	outfile << "findContestant <" << k << ">" << endl;
	if(locHeap[k] > -1){
		outfile << "Contestant <" << k << "> is in the extended heap with score <" << minHeap[locHeap[k]][1] << ">." << endl;
	} else {
		outfile << "Contestant <" << k << "> is not in the extended heap." << endl;
	}

}

void insCont(string line, int minHeap[][2], ofstream& outfile){

 //parse contestant id
	num = line.find(">");
	dumb = line.substr(18,num);
	k = stoi(dumb);
 //parse contestant score
	dumb = line.substr(num + 3,line.length());
	num = dumb.find(">");
	dumb = dumb.substr(0, num);
	p = stoi(dumb);

	outfile << "insertContestant <" << k << "> <" << p << ">" << endl;

	if(locHeap[k] > -1){
		outfile << "Contestant <" << k << ">is already in the extended heap: cannot insert." << endl;
	} else {
		numCurr++;
		locHeap[k] = numCurr;
		minHeap[numCurr][1] = p;
		minHeap[numCurr][0] = k;
		ordHeap(k, minHeap);
		outfile << "Contestant <" << k << "> inserted with initial score <" << p << ">." << endl;
	}
}

void elmWeak(int minHeap[][2], ofstream& outfile){
					outfile << "eliminateWeakest" << endl;
	int location, small;
	int min, max = -1;
	for(int i = 1; i < numCont; i++){
		if(locHeap[i] == 1){
			min = i;
		}
		if(locHeap[i] == numCurr){
			max = i;
		}
	}
	outfile << "Contestant <" << minHeap[1][0] << "> with current lowest score <" << minHeap[1][1] <<"> eliminated." << endl;
	minHeap[1][0] = minHeap[numCurr][0];
	minHeap[1][1] = minHeap[numCurr][1];
	locHeap[max] = 1;
	locHeap[min] = -1;
	minHeap[numCurr][1] = -1;
	minHeap[numCurr][0] = -1;
	numCurr--;

	for(int k = 1; k <= numCurr; k++){
		if(k > 1){
			if(k < 4){
				if(minHeap[k][1] < minHeap[1][1]){
					small = minHeap[k][1];
					location = minHeap[k][0];
					minHeap[k][1] = minHeap[1][1];
					minHeap[k][0] = minHeap[1][0];
					locHeap[location] = 1;
					minHeap[1][1] = small;
					minHeap[1][0] = location;
					locHeap[minHeap[k][0]] = k;
				}
			}  else {
				if(minHeap[k][1] < minHeap[(k - (k%2))/2 ][1]){
					small = minHeap[locHeap[k]][1];
					location = locHeap[k];
					minHeap[locHeap[k]][1] = minHeap[(k-(k%2))/2][1];
					minHeap[locHeap[k]][0] = minHeap[(k-(k%2))/2][0];
					locHeap[k] = (k-(k%2))/2;
					locHeap[minHeap[(k-(k%2))/2][0]] = location;
					minHeap[(k-(k%2))/2][1] = small;
					minHeap[(k-(k%2))/2][0] = k;
				}
	
			}
			
		}
	}

}

void ernPnts(string line, int minHeap[][2], ofstream& outfile){

	int small, location;

 //parse contestant id
	num = line.find(">");
	dumb = line.substr(12,num);
	k = stoi(dumb);
 //parse contestant score
	dumb = line.substr(num + 3,line.length());
	num = dumb.find(">");
	dumb = dumb.substr(0, num);
	p = stoi(dumb);


		outfile << "earnPoints <" << k << "> <" << p << ">" << endl;

	if(locHeap[k] > 0){
		minHeap[locHeap[k]][1] = minHeap[locHeap[k]][1] + p;
		for(int k = 1; k <= numCurr; k++){
			if(k > 1){
				if(k < 4){
					if(minHeap[k][1] < minHeap[1][1]){
						small = minHeap[k][1];
						location = minHeap[k][0];
						minHeap[k][1] = minHeap[1][1];
						minHeap[k][0] = minHeap[1][0];
						locHeap[location] = 1;
						minHeap[1][1] = small;
						minHeap[1][0] = location;
						locHeap[minHeap[k][0]] = k;
					}
				}  else {
					if(minHeap[k][1] < minHeap[(k - (k%2))/2 ][1]){
						small = minHeap[locHeap[k]][1];
						location = locHeap[k];
						minHeap[locHeap[k]][1] = minHeap[(k-(k%2))/2][1];
						minHeap[locHeap[k]][0] = minHeap[(k-(k%2))/2][0];
						locHeap[k] = (k-(k%2))/2;
						locHeap[minHeap[(k-(k%2))/2][0]] = location;
						minHeap[(k-(k%2))/2][1] = small;
						minHeap[(k-(k%2))/2][0] = k;
					}
		
				}
				
			}
		}

		outfile << "Contestant <" << k << ">'s score increased by <" << p << "> points to <" << minHeap[locHeap[k]][1] << ">." << endl;
	} else {
		outfile << "Contestant <" << k << "> is not in the extended heap." << endl;
	}




}

void losPnts(string line, int minHeap[][2], ofstream& outfile){
	int location, small;


 //parse contestant id
	num = line.find(">");
	dumb = line.substr(12,num);
	k = stoi(dumb);
 //parse contestant score
	dumb = line.substr(num + 3,line.length());
	num = dumb.find(">");
	dumb = dumb.substr(0, num);
	p = stoi(dumb);
		outfile << "losePoints <" << k << "> <" << p << ">" << endl;

	if(locHeap[k] > 0){
		minHeap[locHeap[k]][1] = minHeap[locHeap[k]][1] - p;
		for(int k = 1; k <= numCurr; k++){
			if(k > 1){
				if(k < 4){
					if(minHeap[k][1] < minHeap[1][1]){
						small = minHeap[k][1];
						location = minHeap[k][0];
						minHeap[k][1] = minHeap[1][1];
						minHeap[k][0] = minHeap[1][0];
						locHeap[location] = 1;
						minHeap[1][1] = small;
						minHeap[1][0] = location;
						locHeap[minHeap[k][0]] = k;
					}
				}  else {
					if(minHeap[k][1] < minHeap[(k - (k%2))/2 ][1]){
						small = minHeap[locHeap[k]][1];
						location = locHeap[k];
						minHeap[locHeap[k]][1] = minHeap[(k-(k%2))/2][1];
						minHeap[locHeap[k]][0] = minHeap[(k-(k%2))/2][0];
						locHeap[k] = (k-(k%2))/2;
						locHeap[minHeap[(k-(k%2))/2][0]] = location;
						minHeap[(k-(k%2))/2][1] = small;
						minHeap[(k-(k%2))/2][0] = k;
					}
		
				}
				
			}
		}

		outfile << "Contestant <" << k << ">'s score decreased by <" << p << "> points to <" << minHeap[locHeap[k]][1] << ">." << endl;
	} else {
		outfile << "Contestant <" << k << "> is not in the extended heap." << endl;
	}

}

void cwnWinr(int minHeap[][2], ofstream& outfile){
	int location, small, min, max = -1;
	outfile << "crownWinner" << endl;



	while(numCurr > 1){
		for(int i = 1; i < numCont; i++){
			if(locHeap[i] == 1){
				min = i;
			}
			if(locHeap[i] == numCurr){
				max = i;
			}
		}
	minHeap[1][0] = minHeap[numCurr][0];
	minHeap[1][1] = minHeap[numCurr][1];
	locHeap[max] = 1;
	locHeap[min] = -1;
	minHeap[numCurr][1] = -1;
	minHeap[numCurr][0] = -1;
	numCurr--;

	for(int k = 1; k <= numCurr; k++){
		if(k > 1){
			if(k < 4){
				if(minHeap[k][1] < minHeap[1][1]){
					small = minHeap[k][1];
					location = minHeap[k][0];
					minHeap[k][1] = minHeap[1][1];
					minHeap[k][0] = minHeap[1][0];
					locHeap[location] = 1;
					minHeap[1][1] = small;
					minHeap[1][0] = location;
					locHeap[minHeap[k][0]] = k;
				}
			}  else {
				if(minHeap[k][1] < minHeap[(k - (k%2))/2 ][1]){
					small = minHeap[locHeap[k]][1];
					location = locHeap[k];
					minHeap[locHeap[k]][1] = minHeap[(k-(k%2))/2][1];
					minHeap[locHeap[k]][0] = minHeap[(k-(k%2))/2][0];
					locHeap[k] = (k-(k%2))/2;
					locHeap[minHeap[(k-(k%2))/2][0]] = location;
					minHeap[(k-(k%2))/2][1] = small;
					minHeap[(k-(k%2))/2][0] = k;
				}
	
			}
			
		}
	}
	}



	outfile << "Contestant <" << minHeap[1][0] << "> wins with score <" << minHeap[1][1] << ">!" << endl;


}

void shwCont(int minHeap[][2], ofstream& outfile){

	outfile << "showContestants" << endl;

	for(int i = 1; i < numCont; i++){
		if(locHeap[i] > 0){
			outfile << "Contestant <" << i << "> in extended heap location <" << locHeap[i] << "> with score <" << minHeap[locHeap[i]][1] << ">." << endl;
		}
	}
}

void shwHndl(ofstream& outfile){
	outfile << "showHandles" << endl;

	for(int i = 1; i < numCont; i++){
		if(locHeap[i] > 0){
			outfile << "Contestant <" << i << "> stored in extended heap location <" << locHeap[i] << ">." << endl;
		} else {
			outfile << "There is no Contestant <" << i << "> in the extended heap: handle[<" << i << ">] = -1." << endl;
		}
	}

}

void shwLoct(string line, ofstream& outfile){


 //parse the contestent id
	num = line.find(">");
	dumb = line.substr(14,num);
	k = stoi(dumb);

		outfile << "showLocation <" << k << ">" << endl;

	if(locHeap[k] > 0){
		outfile << "Contestant <" << k << "> stored in extended heap location <" << locHeap[k] << ">." << endl;
	} else {
		outfile << "There is no Contestant <" << k << "> in the extended heap: handle[<" << k << ">] = -1." << endl;
	}



}

int main(int argc, char* argv[]){
	ifstream infile;
	ofstream outfile;
	string line, func, delim = " ";
	int pos;

	if(argc == 3) {
		infile.open(argv[1]);
		outfile.open(argv[2]);


		//setting up for number of initial nodes
		getline(infile, line);
		numCont = stoi(line);
		numCont++;

		int minHeap[numCont][2];
		minHeap[0][1] = -1;
		for(int i = 1; i < numCont; i++){
			minHeap[i][0] = i;
			minHeap[i][1] = -1;
			locHeap.push_back(-1);
		}
		locHeap.push_back(-1);		


		//read functions in file
//		getline(infile, line);
//		pos = line.find(delim);
//		func = line.substr(0, pos);
//		outfile << pos << endl;


		while(getline(infile, line)){




			string test;
			pos = line.find(delim);
			if(pos != -1){
				func = line.substr(0, pos);
			} else{
				func = line.substr(0, line.length() -1);
			}

			//send to functions
			if(func == "findContestant"){
				fndCont(line, minHeap, outfile);
			} else if(func == "insertContestant"){
				insCont(line, minHeap, outfile);
			} else if(func == "eliminateWeakest"){
				elmWeak(minHeap, outfile);
			} else if(func == "earnPoints"){
				ernPnts(line, minHeap, outfile);
			} else if(func == "losePoints"){
				losPnts(line, minHeap, outfile);
			} else if(func == "crownWinner"){
				cwnWinr(minHeap, outfile);
			} else if(func == "showContestants"){
				shwCont(minHeap, outfile);
			} else if(func == "showHandles"){
				shwHndl(outfile);
			} else if(func == "showLocation"){
				shwLoct(line, outfile);
			} else {
				outfile << "function not found" << endl;
			}
		}
		

		infile.close();
		outfile.close();
	} else {
		outfile << "error in commandline" << endl;
	}


}
