#include <stdio.h>
#include <string.h>
#include <iostream>
#include "binary.h"
#include "memory.h"


//cycle
int Cycle_count = 0;

//for output
bool m = false;
unsigned int memstart = 0;
unsigned int memend =0;
bool d = false;
bool n = false;
int  num_instruction=0;


   //op 해석에 필요한 값들
char type = 'r';
unsigned int op =0;
unsigned int rs = 0;
unsigned int rt = 0;
unsigned int rd = 0 ;
unsigned int shamt = 0;
unsigned int target = 0;
short int imm_offset = 0;
unsigned int funct = 0;


//특수한 OP들을 나타내는 것들.. 최대한 줄이자
bool JR = false;
bool JAL = false;
bool BEQ = false;
    //한 Flux 계산 후 Temp값들.
unsigned int PCadd = 0; //(PC+=4 후의 값)

//Sector 2 results
unsigned int PC_Jump = 0;

//Control unit signal들i
bool Jump = false;
unsigned int ALUOp = 0;
bool Branch = false;
int Shift = 0; //Shift 의 부호.
bool Jr = false;
bool PCSrc = false;
bool MemRead = false;
bool MemtoReg = false;
bool MemWrite = false;
bool RegWrite = false;
bool ALUSrc = false;
bool RegDst = false;
int ALUctr = 0;
bool Sign = true;
bool Byte = false; //1byte load store용.
//Sector 3 results
int RD1 = 0; //Read data 1
int RD2 = 0; //Read data 2
unsigned int Sign_Extended = 0; //instr[15-0] padding
unsigned int WRA = 0; //write reg  addr
unsigned int ALUinput2 = 0; //RD1 = ALUinput2
unsigned int Branch_Addr =0;
//ALU result
int ALUres = 0;

//Sector 5
unsigned int Branch_PC = 0;
unsigned int Jump_PC = 0;
//Sector 6
int Rdata = 0;
int RWD = 0; //RegWriteData
//Other Signals
bool ovf = false;

int main(int argc, char* argv[]) {
    const char* filename = argv[argc-1];

    const char* mcommand = "-m";
    const char* dcommand = "-d";
    const char* ncommand = "-n"; 
    for (int i = 1; i<argc-1; i++){
	   if(!strcmp(argv[i],mcommand)){
			   m=true;
			   i+=1;
			   const char* memory_print = argv[i];
			   sscanf(memory_print,"0x%x:0x%x",&memstart,&memend);
			   //printf("0x%x:0x%x\n", memstart, memend);;
	   }
	   else if(!strcmp(argv[i],dcommand)){
		   d = true;
		   continue;
	   }
	   else if(!strcmp(argv[i],ncommand)){
		   n = true;
		   i+=1;
		   num_instruction  = atoi(argv[i]);
	   }
    }
    //printf("0x%x:0x%x", memstart, memend);

    FILE* binary_code;
    binary_code = fopen(filename, "r");
    unsigned int codes[1024]={};
    int codnum = 0;
    
    char size[64] = {};
    // textsize
    fgets(size, 64, binary_code);
    unsigned int textsize = char2int(size);
    // datasize
    fgets(size, 64, binary_code);
    unsigned int datasize = char2int(size);
    //printf("%d is the textsize and \n%d is the datasize \n", textsize, datasize);

    Memlay Mmemory(datasize, textsize);

    unsigned int textaddr = 0x00400000;
    unsigned int dataaddr = 0x10000000;
    unsigned int PC = 0x00400000;
    int registers[32]={0};


    for(int i= 0;i<(textsize>>2);i++){
	    char line[64] ={0};
	    fgets(line, 64, binary_code);
	    Mmemory.write(textaddr+(i<<2),char2int(line));
    }
    for(int i = 0;i<(datasize>>2);i++){
	    char line[64]= {0};
	    fgets(line, 64, binary_code);
	    Mmemory.write(dataaddr+(i<<2),char2int(line));
    }
    //Mmemory.print();
    fclose(binary_code);

   
    unsigned int curline = 0;

    while(true){

	    if(n){
		    if (Cycle_count == num_instruction) break;
	    }

	    //First Sector
	    curline = Mmemory.load(PC);
	    if (curline == 0){
		    break; //end
	    }
	    PCadd = PC+4;
	   //First Sector end

	   //Second Sector
	   
	   //#1 Jump
	   PC_Jump = cut(curline, 6,0)<<2+(cut(PC,0,28));
		

	   //#2 Control Unit
	   op = curline >> 26;

	   if (op  == 0){
		   type = 'r';
	   }
	   else if (op ==2 or op == 3){
		   type = 'j';
	   }
	   else{
		   type = 'i';
	   }

	   JR = false;

	   if (type == 'r'){
	   	   //Signals
		   Jump = false;
		   Branch = false;
		   MemRead = false;
		   MemtoReg = false;
		   MemWrite = false;
		   RegWrite = true;
		   RegDst = true;
		   ALUSrc = false;
		   Shift = 0;

		   //analysis
		   rs = cut(curline, 6,21);
		   rt = cut(curline, 11,16);
		   rd = cut(curline, 16,11);
		   shamt = cut(curline,21,6);
		   funct = cut(curline, 26,0);
		   //For JR
		   
		   if(funct == 8) {
			   JR = true;
			   RegWrite = false;
			   RegDst = false;
		   }
		   
		   //For Shifter
		   if(funct == 0) Shift = 1;
		   else if (funct == 2) Shift = -1;
		   else Shift = 0;
		   

		   //ALU
		   if(funct == 0x24) ALUctr = 0b0000; //AND
		   if(funct == 0x25 or funct == 0x2 or funct == 0x0) ALUctr = 0b0001; //OR(shift는 0와 OR)
		   if(funct == 0x21) ALUctr = 0b0010; //ADD
		   if(funct == 0x23) ALUctr = 0b0110; //SUBTRACT
		   if(funct == 0x2b) ALUctr = 0b0111; //solt
		   if(funct == 0x27) ALUctr = 0b1100; //NOR
	   }

	   if (type == 'i'){

		   //analysis
		   rs = cut(curline, 6, 21);
		   rt = cut(curline, 11,16);
  		   imm_offset = cut(curline, 16,0);

		   //Signals
		   Shift = 0;
		   if(op ==0xf) {
			   Shift = 1;
			   shamt = 16;
		   }
		   Jump = false;
		   Sign = (op == 0xc or op == 0xd) ? false : true; //ORI, ANDI는 zero-extend
		   Branch = (op == 4 or op == 5) ? true : false;
		   BEQ = (op == 4) ? true : false;
		   MemRead = (op == 0x23 or op == 0x20) ? true : false;
		   MemtoReg = (op == 0x23 or op == 0x20) ? true : false;
		   MemWrite = (op == 0x2b or op == 0x28) ? true : false;
		   RegWrite = (op == 9 or op == 0xc or op == 0xf or op == 0x23 or op == 0x20 or op == 0xd or op== 0xb) ? true: false;
		   RegDst = (op==0x4 or op==0x5 or op == 0x2b or op == 0x28) ? true : false;
		   ALUSrc = (op == 0x4 or op == 0x5) ? false : true;
		   Byte = (op == 0x20 or op == 0x28 ) ? true : false;
		   if(op == 0xc) ALUctr = 0b0000; //AND
		   if(op == 0xf or op == 0xd) ALUctr = 0b0001; //OR
		   if(op ==0x9 or op == 0x23 or op == 0x20 or op ==0x28 ) ALUctr = 0b0010; //add
		   if(op ==0x4 or op == 0x5) ALUctr = 0b0110; //sub
		   if(op == 0xb) ALUctr = 0b0111;

	   }
	   JAL = false;
	   if (type == 'j'){
	   	Jump = true;
		Branch =false;
		MemRead = false;
		MemtoReg = false;
		MemWrite = false;
		RegWrite = false;
		RegDst = false;
	        	
		if (op == 0x3){
			JAL = true;
		}
	   }	
	   	
	   //Control Unit end

	   //Third section start
	   RD1 = registers[rs];
	   RD2 = registers[rt];
	   WRA = (RegDst) ? rd : rt;
	   Sign_Extended = extend(imm_offset,Sign);
	   //printf("Sign_Extended is: %d, RD2 is: %d\n", Sign_Extended, RD2);
	   ALUinput2 = mux(static_cast<int>(Sign_Extended), RD2, ALUSrc);

	   //printf("ALUinput2 = %d\n",ALUinput2);
	   
	   if(Shift == 1) ALUinput2 = ALUinput2 <<shamt;
	   else if(Shift == -1) ALUinput2 = ALUinput2 >> shamt;
	   Branch_Addr = (Sign_Extended<<2) + PCadd;

	   //Third section end
	   //ALU section(section #4)
	   if(ALUctr == 0b0000) ALUres = RD1 & ALUinput2;
	   else if(ALUctr == 0b0001) ALUres = RD1 | ALUinput2;
	   else if(ALUctr == 0b0010) ALUres = RD1 + ALUinput2;
	   else if(ALUctr == 0b0110) ALUres = RD1 - ALUinput2;
	   else if(ALUctr == 0b0111) {
		   int temp = RD1 - ALUinput2;
		   if (temp < 0 ){
			   ALUres = 1;
		   }
		   else{
			   ALUres = 0;
		   }
	   }
	   else if(ALUctr == 0b1100) ALUres = ~(RD1 | ALUinput2);
	   //printf("WRA is: %d\n", WRA);
	   //printf("OPcode: %d\n", op);
	   //printf("ALUctr is %d\n", ALUctr);
	   //printf("ALUres is %d\n", ALUres);

	   PCSrc = (BEQ) ? Branch&&(!ALUres) : Branch && ALUres;
	   	   
	   //ALU section end;
	   //5th section start
	   Branch_PC = mux(Branch_Addr, PCadd, PCSrc);
	   Jump_PC = mux(PC_Jump ,Branch_PC, Jump);
	   PC = mux(static_cast<unsigned int>(RD1), Jump_PC, JR);

	   //5th section end.
	   //6th section start(Memread/Write)
	   if(MemWrite){
		   Mmemory.write(ALUres, RD2,Byte);
	   }
	   else if(MemRead){
		   Rdata = Mmemory.load(ALUres,Byte);
	   }
	   Rdata = static_cast<unsigned int>(Rdata);
	   RWD = mux(Rdata, ALUres, MemtoReg);
	   //printf("Rdata is: %d\n", Rdata);
	   //6th section end
	   //last section(Regwrite)
	   if(RegWrite) registers[WRA] = RWD;
	   if(JAL) registers[31] = PCadd;
	   if(d){
                    printf("Current register values:\n");
                    printf("-------------------------------------------\n");
		    printf("PC: 0x%x\nRegisters: \n",PC);
                    for(int i =0 ; i<32; i++){
                            printf("R%d: 0x%x\n",i, registers[i]);
                    }
		    printf("\n");
		    if(m) Mmemory.print(memstart,memend);
           }

	   Cycle_count +=1; 
    }
    if(!d){
    	printf("Current register values:\n");
    	printf("-------------------------------------------\n");
    	printf(	"PC: 0x%x\nRegisters: \n",PC);
    	for(int i =0 ; i<32; i++){
	    	printf("R%d: 0x%x\n",i, registers[i]);
    	}
	printf("\n");
	if(m) Mmemory.print(memstart,memend);
    }
    return 0;
}
