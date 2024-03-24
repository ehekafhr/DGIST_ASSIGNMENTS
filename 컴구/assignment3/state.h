#ifndef STATE_H
#define STATE_H
#include "memory.h"
#include "binary.h"

class MEM_WB{
	private:
		Memlay* Mem;
	public:
		unsigned int instruction = 0;
		unsigned int PC = 0;
		MEM_WB(Memlay* mempointer){ Mem = mempointer;}

		bool MemRead = false;
		bool RegWrite = false;
		unsigned int memval = 0;
		unsigned int rd  = 0;

		unsigned int ALUres = 0;
		unsigned int offset = 0;

		bool BNE = false;
		bool BEQ = false;

		//about HAZARD
		bool MEMforwardA = false;
		bool MEMforwardB = false;

		//for flush
		void set_zero();


};

class EX_MEM{
	private:
		Memlay* Mem;
		MEM_WB* next_state_Reg;
	public:
		unsigned int instruction = 0;
		unsigned int PC = 0;
		EX_MEM(Memlay* mempointer, MEM_WB* regpointer){
			Mem = mempointer; next_state_Reg = regpointer;}	
		unsigned int ex_result=0;

		unsigned int memaddr = 0;
		//signals NEEDED
		unsigned int op = 0;
		unsigned int rs = 0;
		unsigned int rt = 0;
		unsigned int rd = 0;

		unsigned int offset = 0;
		unsigned int ALUres = 0;

		//ctrl
		bool Byte = false;
		
		bool JR = false;
		bool JAL = false;
		bool BEQ = false;
		bool BNE = false;
		unsigned int NPC = 0;
		bool Jump = false;
		bool Branch = false;
		bool PCSrc = false;
		bool MemRead = false;
		bool MemWrite = false;
		bool RegWrite = false;
		bool RegDst = false;

		unsigned int get_PC(){ return PC;}
		//for flush
		void set_zero();
};

class ID_EX{
	private:
		Memlay* Mem;
		EX_MEM* next_state_reg;
	public:
		unsigned int instruction = 0;
		unsigned int PC = 0;
		ID_EX(Memlay* mempointer, EX_MEM* regpointer){Mem=mempointer;
			next_state_reg = regpointer;}
		unsigned int BPC = 0;
		//signals
		unsigned int op = 0;
		unsigned int rs = 0;
		unsigned int rt = 0;
		unsigned int rd = 0;
		unsigned int shamt = 0;
		unsigned int target = 0;
		unsigned int imm_offset = 0;
		unsigned int funct = 0;

		//편의를 위함.
		bool JR = false;
		bool JAL = false;
		bool BEQ = false;
		bool BNE = false;
		unsigned int NPC = 0;

		//Control unit sig.
		bool Jump = false;
		unsigned int ALUCtr = 0;
		bool Branch = false;
		int Shift = 0;
		bool PCSrc = false;
		bool MemRead = false;
		bool MemWrite = false;
		bool RegWrite = false;
		bool Sign = false;
		bool Byte = false;
		bool RegDst = false;
		bool ALUSrc = false;

		//Register에서 읽어온 값
		unsigned int regread1 = 0;
		unsigned int regread2 = 0;

		void set_next_state(EX_MEM* ref){
			next_state_reg = ref;
		}

		unsigned int get_PC() {return PC;}

		void set_zero();
};
class IF_ID{
	private:
		Memlay* Mem;
		ID_EX* next_state_reg;
	public:
		unsigned int instruction = 0;
		unsigned int PC = 0;
		unsigned int NPC = 0;
		IF_ID(Memlay* mempointer, ID_EX* regpointer){
			Mem = mempointer; next_state_reg = regpointer;
		}
		void set(unsigned int kPC);
		void setmem(Memlay* pointer){Mem = pointer;}
		unsigned int get_PC() {return PC;}
		unsigned int get_ins() {return instruction;}
		void give();
		//signals
		//
		//flush!
		void set_zero();
};


class IF{
private:
	Memlay* Mem;
	IF_ID* latch;
	int* reg;
public:
	IF(Memlay* mempointer, IF_ID* inppointer, int* regpointer){
		Mem =  mempointer; latch = inppointer; reg = regpointer;
	}
	unsigned int PC = 0;
	void push(){latch->set(PC);}
	void flush(){latch->set_zero();}

};

class ID{
private:
	Memlay* Mem;
	IF_ID* inpreg;
	ID_EX* outreg;
	int* reg;
	
public:
	unsigned int PC = 0;
	ID(Memlay* mempointer, IF_ID* inppointer, ID_EX* outpointer, int* regpointer){
		Mem = mempointer;
		inpreg = inppointer;
		outreg = outpointer;
		reg = regpointer;
	}
	void push();
	void flush(){outreg->set_zero();}

};

class EX{
private:
	Memlay* Mem;
	ID_EX* inpreg;
	EX_MEM* outreg;
	int* reg;
public:
	EX(Memlay* mempointer, ID_EX* inppointer, EX_MEM* outpointer,  int* regpointer){
		Mem = mempointer;
		inpreg = inppointer;
		outreg = outpointer;
		reg = regpointer;
	}
	void push();
	void flush(){outreg->set_zero();}

};

class MEM{
private:
	Memlay* Mem;
	EX_MEM* inpreg;
	MEM_WB* outreg;
	int* reg;
public:
	MEM(Memlay* mempointer, EX_MEM* inppointer, MEM_WB* outpointer,int* regpointer){
		Mem = mempointer;
		inpreg = inppointer;
		outreg = outpointer;
		reg = regpointer;
	}
	void push();
	void flush(){outreg->set_zero();}
	
};

class WB{
private:
	Memlay* Mem;
	MEM_WB* inpreg;
	int* reg;
public:
	WB(Memlay* mempointer, MEM_WB* inppointer, int* regpointer){
		Mem =mempointer;
		inpreg = inppointer;
		reg = regpointer;
	}
	void push();
};
#endif
