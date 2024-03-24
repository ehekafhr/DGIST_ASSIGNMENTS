#ifndef MEMORY_H
#define MEMORY_H

class Memory{
	private:
		unsigned int datas[0x1000]= {0};

	
		char type;
		unsigned int start_addr;
		unsigned int size;
	public:
		Memory(char type = 'd', unsigned int memsize = 0);
		unsigned int load(unsigned int addr);
		unsigned char load_byte(unsigned int addr);
		void write(unsigned int addr, unsigned int data);
		void write_byte(unsigned int addr, unsigned int data);
		void print();
};

class Memlay{
	private:
		Memory DATA{};
		Memory TEXT{};
	public:
		Memlay(unsigned int datasize, unsigned int textsize);
		unsigned int load(unsigned int addr, bool byte = false);
		void write(unsigned int addr, unsigned int data, bool byte = false);
		void print(unsigned int start, unsigned int end);
};

#endif
