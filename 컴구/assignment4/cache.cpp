#include "cache.h"
#include <cstdlib>
#include <ctime>

//Utility Function
int log2(long long int val){
	int cnt = 0;
	long long int temp = val>>1;
	while(temp>0){
		cnt+=1;
		temp=temp>>1;
	}
	return cnt;
}

int argmax(int* array, int length){
	int argmax = 0;
	int max = 0;
	for(int i = 0;i<length;i++){
		if(array[i]>max){
			max = array[i];
			argmax=i;
		}
	}
	return argmax;
}


//CACHE 
//Block
Block::Block(){
	_tag = 0;
	valid = false;
	dirty = false;
}

//Return 0 means Success.
//Return 1 means Failure.
int Block::load(long long int tag){
	if (_tag==tag and valid){
		return 0;	
	}
	else{
		return 1;
	}
} 

int Block::write(long long int tag){
	if (_tag==tag and valid){
		dirty = true;
		return 0;
	}	
	else{
		return 1;
	}	
}

int Block::allocate(long long int tag){
	valid = true;
	_tag = tag;
	return -1;
}

//Return -3 means "Dirty" while -4 meand "clean"
int Block::evict(){
	valid = false;
	if (dirty){
		dirty = false;
		return -3;
	}
	else{
		dirty = false;
		return -4;
	}
}

//Set
Set::Set(int associativity, int block_size, bool lru){
	_lru = lru;
	size = associativity;
	blocks = new Block[associativity];
	visit = new int[associativity];
	for(int i = 0;i <associativity;i++){
		visit[i]=0;
	}
	
}

int Set::load(long long int tag){
	if(_lru){
		for(int i = 0; i<size; i++){
			visit[i]+=1;
		}	
	}
	for(int i = 0; i<size;i++){
		int temp = blocks[i].load(tag);
		//0 is Cache Hit!
		if(temp == 0){
			visit[i] = 0;
			return 0;
		}
	}

	//look for empty.
	for(int i = 0; i<size;i++){
		//-1 is not success.. but no evict!(Luckily, there are empty space)
		if(!blocks[i].valid){
			blocks[i].allocate(tag);
			return -1;
		}
	}
	int evt =  evict();
	for(int i = 0; i<size;i++){
		if(!blocks[i].valid){
			blocks[i].allocate(tag);
			return evt;
		}
	}
	printf("Error");
	return 666;
}
int Set::write(long long int tag){
	if(_lru){
		for(int i = 0; i<size;i++){
			visit[i]+=1;
		}
	}
	for(int i = 0; i<size;i++){
		int temp = blocks[i].write(tag);
		if(temp == 0){
			visit[i] = 0;
			return 0;
		}
	}
	for(int i = 0 ;i<size;i++){
		if(blocks[i].valid==false){
			blocks[i].allocate(tag);
			return -1;
		}
	}
	int evt = evict();
	for(int i = 0;i<size;i++){
		if(blocks[i].valid==false){
			blocks[i].allocate(tag);
			return evt;
		}
	}
	printf("Error");
	return 666;
}

int Set::evict_choose(){
	return argmax(visit, size);
}
//When Dirty, return 1
int Set::evict(){
	int victim = 0;
	if(_lru){
		victim = evict_choose();
		visit[victim] = 0;
		return blocks[victim].evict();
	}
	//Random
	else{
		victim = rand()%size;
		return blocks[victim].evict();
	}
}
//-1 When it don't have to be evicted(No prob)

int Set::evictforce(long long int tag){
	int victim = 0;
	for (int i = 0; i<size; i++){
		if(blocks[i]._tag == tag and blocks[i].valid){
			visit[i] = 0;
			return blocks[i].evict();
		}
	}
	return -1;
}	
	

//Cache
Cache::Cache(int associativity, int block_size, int capacity, bool lru){
	_associativity = log2(associativity);
	_block_size = block_size;
	_capacity = capacity;
	_idx = capacity/block_size/associativity;	
	sets = new Set[_idx];
	for (int i = 0; i< _idx; i++){
		sets[i] = Set(associativity, block_size, lru);
	}
	//printf("%d is _block_size",_block_size);
};

//0 means success. 1 means eviction with not dirty. -1 means evict + dirty.
int Cache::load(long long int address){
	return 0;
}
int Cache::write(long long int address){
	return 0;
}


//L2Cache::L2Cache(int associativity, int block_size, int capacity, bool 


int L1Cache::load(long long int address,bool L1dirty){
	long long int offset_removed = address/_block_size;
	long long int tag = offset_removed/_idx;
	long long int idx = offset_removed%_idx;
//
//	printf("%llx, %llx \n", tag, idx);
	int dirty = 0;
	_Rcnt+=1;
	//L1 Miss test. -3 ->Dirtyevict -4 ->Cleanevict -1 ->miss 0->good
	int temp = sets[idx].load(tag);
	//printf("%d\n",temp);
	temp_addr= 0;
	if(temp==-3){
		_Rmiss+=1;
		_Dirtycnt+=1;
		return -1;
	}
	else if(temp==-4){
		_Rmiss+=1;
		_Cleancnt+=1;
		return 1;
	}
	else if(temp == -1){
		_Rmiss+=1;
		return 2;
	}
	else{
		return 0;
	}
}

int L1Cache::write(long long int address, bool L1dirty){
	//long long int offset_removed =address>>2>>_block_size;
	long long int offset_removed = address/_block_size;
	long long int tag = offset_removed/_idx;
	long long int idx = offset_removed%_idx;
	int dirty = 0;
	_Wcnt+=1;
	int temp = sets[idx].write(tag);
	temp_addr = 0;
	//-1 Dirtyevict 1 Cleanevict 2 Miss 0 hit
	if(temp==-3){
		_Wmiss+=1;
		_Dirtycnt+=1;
		return -1;
	}
	else if(temp==-4){
		_Wmiss+=1;
		_Cleancnt+=1;
		return 1;
	}
	else if(temp == -1){
		_Wmiss+=1;
		return 2;
	}
	else{
		return 0;
	}
}


//When L2 evict occur, Check L1 and evict.
int L1Cache::evict(long long int address){
	long long int offset_removed = address/_block_size;
	long long int tag = offset_removed/_idx;
	long long int idx = offset_removed%_idx;
	int test = 0;
	test = sets[idx].evictforce(tag);
	if (test == -3){
		_Dirtycnt+=1;
		return 1;
	}
	else if (test == -4){
		_Cleancnt+=1;
		return 0;
	}
	return -1;
}

