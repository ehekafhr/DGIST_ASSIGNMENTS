#ifndef CACHE_H
#define CACHE_H

#include <list>
#include <iostream>
//Utility Function
int log2(long long int val);
int argmax(int* array, int size);

//CACHE
class Block{
private:
	
	bool dirty = false;
	
public:
	bool valid = false;
	long long int _tag;
	Block();
	int load(long long int tag);
	int write(long long int tag);
	int allocate(long long int tag);
	int evict();
};


class Set{
private:
	int size = 0;
	Block* blocks;
	bool _lru = false;
public:
	int* visit;
	Set(int associativity,int block_size, bool lru); 
	Set(){size = 1024;}
	int load(long long int tag);
	int write(long long int tag);
	int evict_choose();
	int evict();
	int evictforce(long long int tag);
};


class Cache{

public:
	Set* sets;
	int _associativity = 0;
	int _block_size = 0;
	int _capacity = 0;
	long long int _idx = 0;
	int _taglen = 0;


	Cache(int associativity, int block_size, int capacity, bool lru);

	int load(long long int address);
	int write(long long int address);

	//Data. Public.
	int _Rcnt = 0;
	int _Wcnt = 0;
	int _Rmiss = 0;
	int _Wmiss = 0;
	int _Dirtycnt = 0;
	int _Cleancnt = 0;
};

class L1Cache : public Cache{

public:
	L1Cache(int associativity, int block_size, int capacity, bool lru) : Cache(associativity, block_size, capacity, lru){};
	//void L2set(Cache* pointer){L2 = pointer;}
	long long int temp_addr = 0;
	int load(long long int address, bool L1dirty=false);
	int write(long long int address, bool L1dirty=false);
	int evict(long long int address);
	//int loadmiss(long long int address){return L2->load(address);}
};

class Medium{
public:

};


#endif
