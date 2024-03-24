#include <stdio.h>
#include <string.h>
#include <iostream>
#include "binary.h"
#include "memory.h"
#include "state.h"

//cycle
int Cycle_count = 0;

//for output
bool m = false;
unsigned int memstart = 0;
unsigned int memend =0;
bool d = false;
bool n = false;
bool p = false;
int  num_instruction=0;


//Signal
bool taken = false;
bool stall[5]= {false, false, false, false, false};
bool jump = false;
int temPC = 0;

int main(int argc, char* argv[]) {
    const char* filename = argv[argc-1];
    const char* mcommand = "-m";
    const char* dcommand = "-d";
    const char* ncommand = "-n"; 
    const char* pcommand = "-p";
    const char* antp = "-antp";
    const char* atp = "-atp";

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
	   else if(!strcmp(argv[i],pcommand)){
		   p = true;
		   continue;
	   }
	   else if(!strcmp(argv[i], antp)){
		   taken = false;
		   continue;
	   }
	   else if(!strcmp(argv[i], atp)){
		   taken = true;
		   continue;
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


    MEM_WB MW(&Mmemory);
    EX_MEM EM(&Mmemory, &MW);
    ID_EX IE(&Mmemory, &EM);
    IF_ID II(&Mmemory, &IE);

    MW.set_zero(); EM.set_zero(); IE.set_zero(); II.set_zero();

    IF IFstage(&Mmemory, &II, registers);
    ID IDstage(&Mmemory, &II, &IE, registers);
    EX EXstage(&Mmemory, &IE, &EM, registers);
    MEM MEMstage(&Mmemory,&EM, &MW, registers);
    WB WBstage(&Mmemory, &MW, registers);

    unsigned int WPC;
    while(true){

	    if(n){
		    if (Cycle_count == num_instruction) break;
	    }

	    if(PC>0x00400000+textsize or PC<0x00400000) PC = 0;



	    WPC = MW.PC;

	    IFstage.PC = PC;
            //Stop!
	    
            if(Cycle_count!=0 and !II.instruction and !IE.instruction and !EM.instruction and !MW.instruction) break;
	    if(!stall[4]) {WBstage.push();
	    	if(!stall[3]) {MEMstage.push();
	    		if(!stall[2]) {EXstage.push();
	    			if(!stall[1]) {IDstage.push();
	    				if(!stall[0]) {IFstage.PC =PC;
						IFstage.push();}
	    				else { II.set_zero();}
				}
				else {IE.set_zero();}
			}else {EM.set_zero();}
		}else {MW.set_zero();}
	    }
	    
	    for (int i = 0 ; i<5;i++){
		    stall[i] = false;
	    }

	    Cycle_count+=1;

	    //HAZARD DETECTION
	   
	    //Jump- Stall
	    jump = false;
	    unsigned int curins = II.instruction;
	    unsigned int op = curins>>26;
	    unsigned int funct = curins<<26>>26;
	    if(op == 3 or op == 2 or (op == 0 and funct == 8)){
		    stall[0] = true;
		    jump = true;
	    }
	    if(taken and (op ==4 or op ==5)){
		    stall[0] = true;
	    }
	    if(EM.MemRead and (EM.rd==IE.rs or EM.rd==IE.rt)){
			    stall[2] = true;
	    }	    
	    
	    //base pc update
	    if(II.NPC<0x00400000+textsize and II.NPC>0x00400000-4){
		    PC=II.NPC;
	    }
		    
	    //PC = II.NPC;

	    //Branch
	    if(taken and (IE.op == 4 or IE.op ==5)){
		    II.set_zero();
		    //stall[0] = true;
		    PC = IE.BPC;
	    }

	    //MEM/WB TO EX
	    if(MW.RegWrite){
		    if(MW.rd == IE.rs){
			    IE.regread1 = MW.memval;
		    }
		    if (MW.rd == IE.rt){
			    IE.regread2 = MW.memval;
		    }
	    }


	    //EX/MEM TO EX
	    if(EM.RegWrite and !EM.MemRead){
		   //printf("EM.ALUres is %d\n", EM.ALUres);
		   unsigned int WR = 0;
		   if(EM.RegDst) {WR = EM.rd;}
		   else WR=EM.rt;
		   if  (WR == IE.rs){
			    IE.regread1 = EM.ALUres;
		   }
		   if (WR == IE.rt){
			   IE.regread2 = EM.ALUres;
		   }
	    }

	    //MEM_WB TO MEM
	    if(MW.RegWrite){
		    if(MW.rd == EM.rs){
			    EM.memaddr = MW.memval;
		    }
	    }
	    //PC=II.NPC;
	    if(IE.Jump or IE.JAL){
		    PC = IE.NPC;
	    }
	    else if (IE.JR){
		    PC = IE.regread1;
	    }
	   
	    if (!taken){
		    if(MW.BNE){
			    if(MW.ALUres){
			    PC = MW.PC+(MW.offset<<2)+4;
			    II.set_zero();
			    IE.set_zero();
			    EM.set_zero();
			    stall[0]=false;
			    }
		    }
		    if(MW.BEQ and !MW.ALUres){
			    PC =4+MW.PC+MW.offset<<2;
			    II.set_zero();
			    IE.set_zero();
			    EM.set_zero();
			    stall[0] = false;
		    }
	    }
	    if (taken){
		    if(MW.BNE and !MW.ALUres){
			    PC = MW.PC+4;
			    II.set_zero();
			    IE.set_zero();
			    EM.set_zero();
			    stall[0] = false;
		    }
		    if(MW.BEQ and MW.ALUres){
			    PC = MW.PC+4;
			    II.set_zero();
			    IE.set_zero();
			    EM.set_zero();
			    stall[0] = false;
		    }
	    }

	    if(PC>0x00400000+textsize or PC<0x00400000) PC = 0;
	    printf("===== Cycle %d =====\n", Cycle_count);

            if(p){

                printf("Current pipeline PC state:\n");
		std::cout<<"{";;
		if(II.PC and II.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<II.PC;
		std::cout<<"|";
		if(IE.PC and IE.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<IE.PC;
		std::cout<<"|";
		if(EM.PC and EM.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<EM.PC;
		std::cout<<"|";
		if(MW.PC and MW.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<MW.PC;
		std::cout<<"|";
		if(WPC and WPC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<WPC;
		std::cout<<"}\n\n";

                //printf("{0x%x|0x%x|0x%x|0x%x|0x%x}\n\n", PC, II.PC,IE.PC,EM.PC,MW.PC);

            }
            if(d){
                    printf("Curent register values:\n");
                    printf("PC: 0x%x\n", PC);
                    printf("Registers: \n");
                    for(int i = 0 ; i<32; i++){
                            printf("R%d: 0x%x\n",i,registers[i]);
                    }
                    printf("\n");
                    if(m) {Mmemory.print(memstart,memend);
		    printf("\n");}
            }

    }

    if(!n){
	printf("===== Completion cycle: %d =====\n\n", Cycle_count);

        printf("Current pipeline PC state:\n");
        std::cout<<"{";;
        if(II.PC and II.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<II.PC;
        std::cout<<"|";
        if(IE.PC and IE.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<IE.PC;
        std::cout<<"|";
        if(EM.PC and EM.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<EM.PC;
        std::cout<<"|";
        if(MW.PC and MW.PC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<MW.PC;
        std::cout<<"|";
        if(WPC and WPC<(0x00400000+textsize)) std::cout<<"0x"<<std::hex<<WPC;
        std::cout<<"}\n\n";
    	printf("Current register values:\n");
    	printf("PC: 0x%x\n", PC);
	printf(	"Registers: \n");

    	for(int i =0 ; i<32; i++){
	    	printf("R%d: 0x%x\n",i, registers[i]);
    	}
	printf("\n");
	if(m) Mmemory.print(memstart,memend);
    }
    return 0;
}
