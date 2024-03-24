#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include "cache.h"


#define KB 1024

using namespace std;
//Hyper
int capacity = 0;
int associativity = 0;
int block_size = 0;
bool lru = false;


int main(int argc, char* argv[]){

	//Arguments..
	const char* filename = argv[argc-1];
	const char* ccommand = "-c";
	const char* acommand = "-a";
	const char* bcommand = "-b";
	const char* lrucommand = "-lru"; const char* randomcommand = "-random";

	bool c = false; bool a = false; bool b = false; bool p = false;
	
	for(int i = 1; i<argc-1; i++){
		if(!strcmp(argv[i],ccommand)){
			c=true;
			i+=1;
			capacity = atoi(argv[i]);
		}
		else if(!strcmp(argv[i],acommand)){
			a=true;
			i+=1;
			associativity = atoi(argv[i]);
		}
		else if(!strcmp(argv[i],bcommand)){
			b=true;
			i+=1;
			block_size = atoi(argv[i]);
		}
		else if(!strcmp(argv[i],lrucommand)){
			p=true;
			lru=true;
		}
		else if(!strcmp(argv[i],randomcommand)){
			p=true;
		}
	}

	//Everything Okay?
	if(!c or !a or !b or !p){
		printf("Not enough Arguments!");
		return 1;
	}
	if(capacity>1024 or capacity<4){
		printf("Wrong Capacity!");
		return 1;
	}
	if(associativity>16){
		printf("Wrong associativity!");
		return 1;
	}
	if(block_size<16 or block_size>128){
		printf("Wrong block size!");
		return 1;
	}


	//Let's Make Caches...

	capacity*=1024;
	Cache* L2 = new Cache(associativity, block_size, capacity/4, lru);
	//L2->load(10);
	L1Cache* LS = new L1Cache(associativity, block_size, capacity, lru);
	int way2 = associativity;
	if(associativity>2) way2 = associativity>>2;
	L1Cache* L1 = new L1Cache(way2, block_size, capacity/4,lru);
	//L1->L2set(L2);
	//L1Cache* L3 = new L1Cache(associativity, block_size, capacity/4, lru);
	//L3->L2set(L2);
	
	//printf("Clear!");
		
	FILE* tracefile;
	tracefile = fopen(filename, "r");
	//printf("FILE LOADED");
	long long int address = 0;
	char buffer[64] ={0};
		
	//L1.Cacheset(&l2);
	int lcnt = 0;
	while(fgets(buffer,64,tracefile)){
		lcnt+=1;
		string line(buffer);
		//printf("linecount: %d\n", lcnt);
		istringstream iss(line);
		string WR, addr;
		iss >> WR >> addr;		
		address = std::stoll(addr, 0, 16);	
		//std::cout<<address<<std::hex<<std::endl;
		//printf("%lld",address);
		//IF WRITE
		if(WR[0]=='W'){
			//printf("W");
			int temp = L1->write(address);
			// -1 dirtyeviction 0 sucess 1 cleanevict 2 compularsary miss
			if(temp==-1 or temp==2 or temp==1){
				// dirty eviction.
				int temp2 = LS->write(address);
			}
		}
		//IF READ
		else{
			int temp = L1->load(address);
			if(temp==-1 or temp==2 or temp==1){
				int temp2 = LS->load(address);
			}
			//printf("R");
		}
		//if(lcnt == 100000) break;
	}
	fclose(tracefile);



	float L1missR = float(L1->_Rmiss)/float(L1->_Rcnt);
        float L2missR = float(LS->_Rmiss)/float(LS->_Rcnt);
        float L1missW = float(L1->_Wmiss)/float(L1->_Wcnt);
        float L2missW = float(LS->_Wmiss)/float(LS->_Wcnt);

//	printf("%d L2WMC %d L2RMC\n",LS->_Wcnt,LS->_Rcnt);


	string remove =".out";
	string wfile = filename;
	size_t pos = wfile.find(remove);
	if(pos != string::npos){
		wfile.erase(pos, remove.length());
	}

	capacity = capacity >> 10;
	wfile = wfile + "_" + to_string(capacity) + "_" + to_string(associativity) + "_" + to_string(block_size)+".out";
	
	ofstream writefile(wfile);



	writefile<<"-- General Stats --\n";
	writefile<<"L1 Capacity:	"<< capacity/4<<"\n";
	writefile<<"L1 way:	" << way2 << "\n";
	writefile<<"L2 Capacity:	"<<capacity<<"\n";
	writefile<<"L2 way:	" << associativity << "\n";
	writefile<<"Block Size:	" << block_size <<"\n";
	writefile<<"Total accesses:	"<<lcnt<<endl;
	writefile<<"Read accesses:	"<<L1->_Rcnt<<"\n";
	writefile<<"Write accesses:	"<<L1->_Wcnt<<"\n";
	writefile<<"L1 Read misses:"<<L1->_Rmiss<<"\n";
	writefile<<"L2 Read misses:"<<LS->_Rmiss<<"\n";
	writefile<<"L1 Write misses:"<<L1->_Wmiss<<"\n";
	writefile<<"L2 Write misses:"<<LS->_Wmiss<<"\n";
	writefile<<"L1 Read miss rate:	"<<int(L1missR*100)<<"%\n";
	writefile<<"L2 Read miss rate:	"<<int(L2missR*100)<<"%\n";
	writefile<<"L1 Write miss rate:	"<<int(L1missW*100)<<"%\n";
	writefile<<"L2 Write miss rate:	"<<int(L2missW*100)<<"%\n";
	writefile<<"L1 Clean eviction:	"<<L1->_Cleancnt<<"\n";
	writefile<<"L2 Clean eviction:	"<<LS->_Cleancnt<<"\n";
	writefile<<"L1 Dirty eviction:	"<<L1->_Dirtycnt<<"\n";
	writefile<<"L2 Dirty eviction:	"<<LS->_Dirtycnt<<"\n";
		
	writefile.close();
	return 0;
}
