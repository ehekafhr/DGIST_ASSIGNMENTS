#include <stdio.h>
#include "memory.h"



Memory::Memory(char type, unsigned int memsize){
	start_addr =(type == 'd') ? 0x10000000 : 0x00400000;
	size = memsize;
	for (int i = 0; i<0x1000; i++){
		datas[i] = 0;
	}
}

unsigned int Memory::load(unsigned int addr){
	int pivot = (addr-start_addr)>>2;
	if(pivot<size){
		return datas[pivot];
		}
	return 0;
}

unsigned char Memory::load_byte(unsigned int addr){
	int off = addr%4;
	unsigned int bigaddr = addr-off;
	unsigned int pivot = (bigaddr-start_addr)>>2;
	unsigned char *readaddr = reinterpret_cast<unsigned char*>(&datas[pivot]);
	readaddr+=(3-off);
	return *readaddr;
}

void Memory::write(unsigned int addr, unsigned int data){
	int pivot = (addr-start_addr)>>2;
	unsigned char *writedata = reinterpret_cast<unsigned char*>(&data);
	for (int i =0;i<4;i++){
		Memory::write_byte(addr+i,*(writedata+(3-i)));
	};
}

void Memory::write_byte(unsigned int addr, unsigned int data){
	int off = addr%4;
	unsigned int bigaddr = addr-off;
	unsigned int pivot = (bigaddr-start_addr)>>2;
	unsigned char *readaddr = reinterpret_cast<unsigned char*>(&datas[pivot]);
	readaddr+=(3-off);
	unsigned char writeval = static_cast<unsigned char>(data);
	*readaddr = writeval;
}


void Memory::print(){
	int i = 0;
	unsigned int dataaddr = start_addr;
	unsigned int end = start_addr+size;
	printf("Memory content :\n");
	printf("-------------------------------------------\n");
	for(;dataaddr<=end;dataaddr+=4){
		printf("0x%x: 0x%x\n",dataaddr,datas[i]);
		i+=1;
	}
}

Memlay::Memlay(unsigned int datasize, unsigned int textsize){
                DATA = Memory('d', datasize);
                TEXT = Memory('t', textsize);
}

unsigned int Memlay::load(unsigned int addr, bool byte){
	if(byte){
		if(addr<0x10000000){
			return TEXT.load_byte(addr);
		}
		return DATA.load_byte(addr);
	}
        if (addr<0x10000000){
                return TEXT.load(addr);
        }
        return DATA.load(addr);
}

void  Memlay::write(unsigned int addr, unsigned int data, bool byte){
	if(byte){
		if(addr<0x10000000){
			TEXT.write_byte(addr,data);
		}
		else{
			DATA.write_byte(addr,data);
		}
	}
	else if (addr<0x10000000){
		TEXT.write(addr,data);
	}
	else{
		DATA.write(addr,data);
	}
}


void Memlay::print(unsigned int start, unsigned int end){
	unsigned int cnt = (end-start)>>2;
	unsigned int curaddr = start;
	printf("Memory content [0x%x..0x%x]:\n",start,end);
        printf("-------------------------------------------\n");
	for(int i= 0; i<=cnt;i++){
		unsigned int value = Memlay::load(curaddr,false);
		printf("0x%x: 0x%x\n",curaddr,value);
		curaddr+=4;
        }
}







