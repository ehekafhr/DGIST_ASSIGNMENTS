#include "state.h"
#include "memory.h"
#include <stdio.h>


void IF_ID::set(unsigned int kPC){
	instruction = Mem->load(kPC);
	PC = kPC;
	NPC = PC+4;
}

void MEM_WB::set_zero(){
	instruction=0;
	PC=0;

	MemRead = false;
	RegWrite = false;
	memval = 0;
	rd = 0;
	ALUres = 0;

	MEMforwardA = false;
	MEMforwardB = false;
}

void EX_MEM::set_zero(){
	PC=0;
	instruction=0;

	op=0;
	rs=0;
	rt=0;
	rd=0;
	ALUres = 0;

	offset = 0;
	RegDst = false;
	memaddr = 0;
	Byte = false;
	JR = false; JAL = false; BEQ = false; BNE = false; NPC = 0; Branch = false;
	PCSrc = false; MemRead = false; MemWrite = false; RegWrite = false;
}

void ID_EX::set_zero(){
	PC=0;
	instruction=0;
	regread1=0;
	regread2=0;

	BPC = 0;
	op=0; rs=0; rt=0; rd=0; shamt=0; target=0; imm_offset=0; funct =0; ALUSrc = false;

	Byte = false; JR= false; JAL = false; BEQ = false; BNE = false; NPC = 0; Sign = false;

	RegDst = false; Jump = false; ALUCtr = 0; Branch = false; Shift = 0; PCSrc = false; MemRead= false; MemWrite = false; RegWrite = false;
}

void IF_ID::set_zero(){
	PC =0;
	instruction=0;
}

void ID::push(){
	//input
	unsigned int PC = inpreg->get_PC();
	unsigned int ins = inpreg->get_ins();
	outreg->PC = PC;
	outreg->instruction = ins;

	//make op, rs, rt ,rd shamt, target, imm_offset, funct
	unsigned int op = ins>>26;unsigned int  rs = ins<<6>>27;unsigned int rt = ins<<11>>27; unsigned int rd = ins<<16>>27; unsigned int shamt = ins<<21>>27; unsigned int  funct = ins<<26>>26; unsigned int target = ins<<6>>6; unsigned int imm_offset = ins<<16>>16;

	//and save it.
	outreg -> op = op;
	outreg -> rs = rs;
	outreg -> rt = rt;
	outreg -> rd = rd;
	outreg -> shamt = shamt;
	outreg -> funct = funct;
	outreg -> target = target;
	outreg -> imm_offset = imm_offset;

	//calculate Signals
	outreg -> JR = (op == 0 and funct == 8) ? true : false;
	outreg -> JAL = (op ==3) ? true : false;
	outreg -> Jump = (op ==2) ? true : false;

	outreg -> NPC = (outreg->JAL or outreg->Jump) ? (PC>>28<<28) + target<<2 : PC+4;

	outreg -> Branch = (op == 4 or op == 5) ? true: false;
	outreg -> BEQ = (op ==4) ? true : false;
	outreg -> BNE = (op ==5) ? true : false;

	outreg -> Sign = (op ==0xc or op==0xd) ? false:true;

	//signals
	int Shift = 0;
	unsigned int ALUCtr = 0;
	unsigned int BPC = 0;
	bool MemRead = false;
	bool MemtoReg = false;
	bool MemWrite = false;
	bool RegWrite = false;
	bool RegDst = false;
	bool Byte = false;
	bool ALUSrc = false;

	//Rtype
	if(op==0){
		if(funct ==0x24) ALUCtr = 0b0000;//AND
		if(funct ==0x25 or funct==0 or funct ==0x2 or funct ==0x8) ALUCtr = 0b0001;//OR
		if(funct ==0x21) ALUCtr = 0b0010; //ADD
		if(funct ==0x23) ALUCtr = 0b0110; //Sub
		if(funct ==0x2b) ALUCtr = 0b0111; //solt
		if(funct ==0x27) ALUCtr = 0b1100; 

		RegDst = true;
		if(funct != 0x8)RegWrite = true;
		
		if(funct ==0) Shift = 1;
		else if(funct ==2) Shift = -1;
	}
	//Jtype
	else if (op == 2 or op ==3){
		outreg -> Jump = true;
		if(op == 3){
			RegWrite = true;
			outreg->rd = 31;
			outreg->rt = 31;

		}
	}
	//Itype
	else{
		ALUSrc = (op == 4 or op == 5) ? false : true;
		MemRead = (op ==0x23 or op ==0x20) ? true : false;
		MemtoReg = (op ==0x23 or op ==0x20) ? true : false;
		MemWrite = (op ==0x2b or op == 0x28) ? true : false;
		RegWrite = (op==9 or op==0xc or op==0xf or op==0x23 or op==0x20 or op==0xd or op==0xb) ? true : false;
		//RegDst = (op==0x4 or op==0x5 or op==0x2b or op==0x2b) ? true:false;
		RegDst = false;
		Byte = (op == 0x20 or op==0x28) ? true : false;


		if (op==0xc) ALUCtr = 0b0000;
		if (op==0xf or op==0xd) ALUCtr = 0b0001;
		if (op == 0x9 or op == 0x23 or op == 0x20 or op== 0x28) ALUCtr = 0b0010;
		if (op == 0x4 or op ==0x5) ALUCtr = 0b0110;
		if (op == 0xb) ALUCtr = 0b0111;
	}
        
	outreg -> ALUSrc = ALUSrc;
	outreg -> Shift = Shift;
	outreg -> ALUCtr = ALUCtr;
	outreg -> MemRead = MemRead;
	outreg -> MemWrite = MemWrite;
	outreg -> RegWrite = RegWrite;
	outreg -> RegDst = RegDst;

	outreg -> Byte = Byte;
	outreg -> regread1 = reg[rs];
	outreg -> regread2 = reg[rt];

	outreg -> BPC = inpreg->PC + 4 + imm_offset*4;
}

void EX::push(){
	outreg->instruction = inpreg->instruction;
	outreg->op = inpreg->op;
	outreg->rs = inpreg->rs;
	outreg->rt = inpreg->rt;
	outreg->rd = inpreg->rd;
	outreg->Byte = inpreg->Byte;
	outreg->RegDst = inpreg->RegDst;

	outreg->BNE = inpreg->BNE;
	outreg->BEQ = inpreg->BEQ;
	outreg->offset = inpreg->imm_offset;
	//printf("EX stage: rs is %d , rt is %d, rd is %d\n", inpreg->rs, inpreg->rt, inpreg->rd);
	outreg->PC = inpreg->PC;

	outreg->RegWrite = inpreg->RegWrite;
	outreg->MemRead = inpreg->MemRead;
	outreg->MemWrite = inpreg->MemWrite;

	unsigned int Sign_Extended = extend(inpreg->imm_offset, inpreg->Sign);
	unsigned int RD1 = inpreg->regread1;
	unsigned int RD2 = inpreg->regread2;
	outreg->memaddr = inpreg->regread1;

	unsigned int ALUinput2 = mux(Sign_Extended, RD2, inpreg->ALUSrc);
	//printf("%d\n", inpreg->shamt);
	if (inpreg->Shift ==1) ALUinput2 = ALUinput2<<inpreg->shamt;
	else if(inpreg->Shift == -1) ALUinput2 = ALUinput2 >>inpreg->shamt;

	unsigned int Brnach_Addr = (Sign_Extended<<2)+inpreg->get_PC();

	unsigned int ALUres = 0;
	unsigned int ALUCtr = inpreg->ALUCtr;

	//printf("EX stage: RD1 is %d, Rd2 is %d, ALUCtr is %d\n", RD1, ALUinput2, ALUCtr);
	if(ALUCtr == 0b0000) ALUres = RD1 & ALUinput2;
	else if(ALUCtr == 0b0001) ALUres = RD1 | ALUinput2;
	else if(ALUCtr == 0b0010) ALUres = RD1 + ALUinput2;
	else if(ALUCtr == 0b0110) ALUres = RD1 - ALUinput2;
	else if(ALUCtr == 0b0111) {
		int temp = RD1 - ALUinput2;
		if(temp<0){
			ALUres =1;
		}
		else{
			ALUres =0;
		}
	}
	else if(ALUCtr == 0b1100) ALUres = ~(RD1 |ALUinput2);
	if(inpreg->op == 0xf) ALUres = ALUres<<16;
	//printf("ALUres is %d", ALUres);
	if(inpreg->op ==0x3) ALUres = inpreg->PC+4;
	outreg->PCSrc = (inpreg->BEQ) ? inpreg->Branch&&(!ALUres):inpreg->Branch&&(ALUres);
	outreg->ALUres = ALUres;
}
void MEM::push(){

	outreg->PC = inpreg->PC;

	outreg->instruction = inpreg->instruction;
	if (inpreg->MemWrite){
		Mem->write(inpreg->ALUres, reg[inpreg->rt],inpreg->Byte);
	}
	if (inpreg->MemRead){
		outreg->memval = Mem->load(inpreg->ALUres,inpreg->Byte);
	}
	else{
		//printf("MEM stage: ALURES: %d\n",inpreg->ALUres);
		outreg->memval = inpreg->ALUres;
	}
	if(inpreg->RegDst){
		outreg->rd = inpreg->rd;
	}
	else{
		outreg->rd = inpreg->rt;
	}

	outreg->offset = inpreg->offset;
	outreg->ALUres = inpreg->ALUres;
	outreg->BNE = inpreg->BNE;
	outreg->BEQ = inpreg->BEQ;
	outreg->MemRead = inpreg->MemRead;
	outreg->RegWrite = inpreg->RegWrite;

}
void WB::push(){
	if(inpreg->RegWrite){
		//printf("WBstage: REGWRITE memval: %d, rd: %d\n", inpreg->memval,inpreg->rd);
		if(inpreg->MemRead){
			reg[inpreg->rd] = inpreg->memval;
			//printf("RegWrite%d, %d\n", inpreg->memval, inpreg->rd);
		}
		else{
			//printf("ALURES%d,\n",inpreg->memval);
			reg[inpreg->rd] = inpreg->memval;
		}
	}
}
