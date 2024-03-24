#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
//잡다한함수들
long long int char2int(char* word) {
	if (word[0] == '0' and word[1] == 'x') {
		return std::strtoll(word, nullptr, 16);
	}
	return atoi(word);
}
struct addr_Tag {
	unsigned long long int address;
	char* tag = {};
};
struct addr_Data {
	unsigned long long int address;
	unsigned long long int data;
};
struct Memory {
	addr_Tag Set[512];
	addr_Data Set2[2048] = {};
	int Tagcount = 0;
	int Datacount = 0;
	void add(addr_Tag pair) {
		Set[Tagcount] = pair;
		Tagcount += 1;
	}
	void addData(addr_Data pair) {
		Set2[Datacount] = pair;
		Datacount += 1;
	}
	unsigned long long int get_addr(char* tag) {
		for (int i = 0; i < Tagcount; i++) {
			char checker[128] = {};
			strcpy(checker, Set[i].tag);
			if (!strcmp(checker , tag)) {
				return Set[i].address;
			}
		}
		return 0;
	}

	unsigned long long int get_data(unsigned long long int addr) {
		for (int i = 0; i < Datacount; i++) {
			if (Set2[i].address == addr) {
				return Set2[i].data;
			}
		}
		return 0;
	}
	//for test
	void print() {
		for (int i = 0; i < Tagcount; i++) {
			addr_Tag temp = Set[i];
			printf("Tag is: %s, And addr is: 0x%llX\n", temp.tag, temp.address);
		}
	}
	void print2() {
		for (int i = 0; i < Datacount; i++) {
			addr_Data temp = Set2[i];
			printf("Data is: 0x%llX, And addr is: 0x%llX\n", temp.data, temp.address);
		}
	}
};
int main(int argc, char* argv[])
{
	//기본 변수, 어레이

	int PC=0x400000; //Program counter
	unsigned long long int textcounter = 0x00400000;
	unsigned long long int dataCounter = 0x10000000;



	const char* filename = argv[1];
	//file 입력df
	FILE* assmbly;

	//"instructions"라는 배열에 한 줄 한줄 입력
	assmbly = fopen(filename, "r");
	char line[64] = { 0 };
	char instructions[2048][64] = { 0 };
	int inscount = 0;
	while (fgets(line, 64, assmbly)) {
		if (strcmp(line,"\n")) {
			strcpy(instructions[inscount], line);
			inscount += 1;
		}
	}


	fclose(assmbly);
	Memory Datamem = {};
	Memory Textmem = {};
	//std::cout << "-------------------Mem Part start------------------" << std::endl;
	//Label들 위치 정하기(메모리 정해놓기)
	int readcounter = 0;
	//.data part
	int curcnt = 1; //.data잖아.
	while (true) {
		readcounter += 1;
		
		//char* NameTec = strtok(instructions[i], ":");
		char templine[128] = {};
		char templine2[128] = {};
		strcpy(templine, instructions[curcnt]);

		strcpy(templine2, templine);  //for Check if .text
		if (!strcmp(strtok(templine2, " "),".text\n")) {
			readcounter+=1;
			break;
		}
		curcnt += 1;
		
		char* Checker = strchr(templine,':');
		//:가 없다?
		if (!Checker) {
			
			addr_Data temp;
			temp.address = dataCounter;
			char* value = strtok(templine, " ");
			char* number = {};
			while (value != NULL) {
				number = value;
				value = strtok(NULL, " ");
			}
			unsigned long long int Dval = char2int(number);
			temp.data =Dval;
			Datamem.addData(temp);
			dataCounter += 4;
			//std::cout << "Data added";
			continue;
		}
		else {
			addr_Tag temp;
			temp.address = dataCounter;
			char* tag;
			tag = new char[64];
			strcpy(tag, templine);
			temp.tag = strtok(tag,":");
			Datamem.add(temp);

			char templine2[128] = {};
			strcpy(templine2, instructions[curcnt]);
			char* mod = strtok(templine2, " ");
			strtok(mod, " ");

			addr_Data temp2;
			temp2.address = dataCounter;
			char* value = strtok(templine, " ");
			char* number = {};
			while (value != NULL) {
				number = value;
				value = strtok(NULL, " ");
			}
			unsigned long long int Dval = char2int(number);
			temp2.data = Dval;
			Datamem.addData(temp2);
			
			if (strcmp(tag, strtok(instructions[curcnt],":"))) {
				dataCounter +=4;
			}
		}

	}
	//Datamem.print();
	//std::cout << "print2" << std::endl;
	//Datamem.print2();
	//.text part
	
	for (; readcounter < inscount; readcounter++) {
	//char* NameTec = strtok(instructions[i], ":");
		char templine[128] = {};
		strcpy(templine, instructions[readcounter]);
		
	        if(!templine){
			continue;
		}	
		// "LA"
		char LAchecker[128] = {};
		strcpy(LAchecker, instructions[readcounter]);
		int LAcount = 0;
		bool lacheck = false;
		char* latok = strtok(LAchecker, " ");
		while (latok) {
			if (!strcmp(latok, "la") and LAcount<2) {
				lacheck = true;
				strtok(NULL, " ");
				char* nametec = strtok(NULL, " ");
				char* name = strtok(nametec, "\n");
				unsigned long long address = Datamem.get_addr(name);
				//printf("addr is: 0x%llX\n", address);
				if ((address)%0x1000 != 0 and address){
					textcounter += 4;
					break;	
				}
			}
			latok = strtok(NULL, " ");
			LAcount += 1;
		}
		if(lacheck){
			textcounter+=4;
			continue;
		}
		
		char* Checker = strchr(templine, ':');
		//:가 없다..
		if (!Checker) {
			textcounter += 4;
			continue;
		}
		else {
			addr_Tag temp;
			temp.address = textcounter;
			strtok(templine, ":");
			char* tag;
			tag = new char[64];
			strcpy(tag, templine);
			temp.tag = tag;
			Textmem.add(temp);
			char blankchecker[128] = {};
			strcpy(blankchecker, instructions[readcounter]);

			char* nullchk = {};
			nullchk = strtok(blankchecker," ");
			nullchk = strtok(NULL," ");
			if (nullchk) {
				//std::cout<<"nullchk is"<< nullchk <<std::endl;

				textcounter += 4;
			}
		}
	}
	//std::cout << "TEXTMEM" << std::endl;
	//Textmem.print();
	//std::cout << "-------------------Mem Test End------------------" << std::endl;

	//instruction들을 "이쁘게 정리"
	//Tag 제거

	for (int i = curcnt + 1; i < inscount; i++) {

		char* labelplace = strstr(instructions[i], ":");
		if (labelplace) {
			strcpy(instructions[i], labelplace + 1);
		}
	}
	//빈 라인 지우고 깔끔하게.

	//std::cout << "-------------------Clear Test START------------------" << std::endl;
	char Cinstructions[2048][64] = { 0 };
	int Cinscount = 0;
	for (int i = curcnt+1; i < inscount; i++){
		if (strcmp(instructions[i], "\n")) {
			strcpy(Cinstructions[Cinscount], instructions[i]);
			Cinscount += 1;
		}
	}
	//std::cout << Cinscount << std::endl;
	//해석
	for (int i = 0; i < Cinscount; i++) {
		//std::cout << Cinstructions[i];
	}
	//std::cout << "-------------------Clear Test End------------------" << std::endl;
	//여기서부터는 main에 있는 data들 주루룩. Tag는 이미 사라져 있을 것.
	int cnt = 0;

	//.data 영역 자 해석 드가자~!~!~!



	int textsize = 0;
	unsigned long long int textsec[2048] = {};
	PC+=4;
	for (int i = 0; i < Cinscount; i++) {
		char* OP = strtok(Cinstructions[i], " ");
		unsigned long int result = 0;
		if (!OP) {
			break;
		}
		//LA
		if (!strcmp(OP, "la")) {
			int rt = atoi(strtok(NULL, " ") + 1);
			char* temp = strtok(NULL,"\n");
			unsigned long long int addr = Textmem.get_addr(temp);
			if(!addr){
				addr = Datamem.get_addr(temp);
			}
			
			int op = 0xf;
			unsigned int imm = addr >> 16;
			result = (op << 26) + (rt << 16) + imm;
		        textsec[textsize] = result;
			PC+=4;
			textsize +=1;	
			if (addr % 0x10000 != 0) {
				
				int op = 0xd;
				int rs = rt;
				unsigned int imm = addr % 0x10000;
			//	std::cout<<imm<<std::endl;
			//	printf("0x%lX\n", result);

				textsec[textsize] = (op << 26) + (rs << 21) + (rt << 16) + imm;
				textsize += 1;
				PC+=4;
			}
			continue;
		}

		//I
		if (!strcmp(OP, "addiu")) {
			int op = 9;
			int rt = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			unsigned short int imm = static_cast<unsigned short int>(char2int((strtok(NULL, "\n"))));
		//	std::cout<<imm<<std::endl;
			result = (op << 26) + (rs << 21) + (rt << 16) + imm;
		}
		else if (!strcmp(OP, "andi")) {
			int op = 0xc;
			int rt = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			unsigned int imm = static_cast<unsigned short int>(char2int(strtok(NULL, " ")) );

			result = (op << 26) + (rs << 21) + (rt << 16) + imm;
		}
		else if (!strcmp(OP, "lui")) {
			int op = 0xf;
			int rt = atoi(strtok(NULL, " ") + 1);
			unsigned int imm = static_cast<unsigned short int>(char2int(strtok(NULL, " ")));
			result = (op << 26)  + (rt << 16) + imm;
		}
		else if (!strcmp(OP, "ori")) {
			int op = 0xd;
			int rt = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			unsigned int imm = static_cast<unsigned short int>(char2int(strtok(NULL, " ")));
			result = (op << 26) +(rs<<21)+ (rt << 16) + imm;
		}
		else if (!strcmp(OP, "sltiu")) {
			int op = 0xb;
			int rt = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			unsigned int imm = static_cast<unsigned short int>(char2int(strtok(NULL, "\n")));
			result = (op << 26) + (rs << 21) + (rt << 16) + imm;
		}
		else if (!strcmp(OP, "lw")) {
			int op = 0x23;
			int rt = atoi(strtok(NULL, " ") + 1);
			unsigned int offset = static_cast<unsigned int>(char2int(strtok(NULL, "$")));
			int rs = atoi(strtok(NULL, ")"));
			result = (op << 26) + (rs << 21) + (rt << 16) + offset;
		}
		else if (!strcmp(OP, "lb")) {
			int op = 0x20;
			int rt = atoi(strtok(NULL, " ") + 1);
			unsigned int offset = static_cast<unsigned short int>(char2int(strtok(NULL, "$")));
			int rs = atoi(strtok(NULL, ")"));
			result = (op << 26) + (rs << 21) + (rt << 16) + offset;
		}
		else if (!strcmp(OP, "sw")) {
			int op = 0x2b;
			int rt = atoi(strtok(NULL, " ") + 1);
			unsigned int offset = static_cast<unsigned short int>(char2int(strtok(NULL, "$")));
			int rs = atoi(strtok(NULL, ")"));
			result = (op << 26) + (rs << 21) + (rt << 16) + offset;
		}
		else if (!strcmp(OP, "sb")) {
			int op = 0x28;
			int rt = atoi(strtok(NULL, " ") + 1);
			unsigned int offset = static_cast<unsigned short int>(char2int(strtok(NULL, "$")));
			int rs = atoi(strtok(NULL, ")"));
			result = (op << 26) + (rs << 21) + (rt << 16) + offset;
		}
		else if (!strcmp(OP, "beq")) {
			int op = 0x4;
			int rs = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			unsigned long long int addr = Textmem.get_addr(strtok(NULL, "\n") );
			unsigned int offset = static_cast<unsigned short int>((addr - PC)>>2);
			result = (op << 26) + (rs << 21) + (rt << 16) + offset;
		}
		else if (!strcmp(OP, "bne")) {
			int op = 0x5;
			int rs = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			unsigned long long int addr = Textmem.get_addr(strtok(NULL, "\n"));
			unsigned int offset = static_cast<unsigned short int>((addr - PC) >> 2);
			result = (op << 26) + (rs << 21) + (rt << 16) + offset;
		}
		//R
		else if (!strcmp(OP, "addu")) {
			int op = 0;
			int rd = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			result = (op << 26) + (rs << 21) + (rt << 16) + (rd << 11) + 0x21;
		}
		else if (!strcmp(OP, "and")) {
			int op = 0;
			int rd = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			result = (op << 26) + (rs << 21) + (rt << 16) + (rd << 11) + 0x24;
		}
		else if (!strcmp(OP, "nor")) {
			int op = 0;
			int rd = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			result = (op << 26) + (rs << 21) + (rt << 16) + (rd << 11) + 0x27;
		}
		else if (!strcmp(OP, "or")) {
			int op = 0;
			int rd = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			result = (op << 26) + (rs << 21) + (rt << 16) + (rd << 11) + 0x25;
		}
		else if (!strcmp(OP, "sltu")) {
			int op = 0;
			int rd = atoi(strtok(NULL, " ") + 1);
			int rs = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			result = (op << 26) + (rs << 21) + (rt << 16) + (rd << 11) + 0x2b;
		}
		else if (!strcmp(OP, "sll")) {
			int op = 0;
			int rd = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			int shamt = atoi(strtok(NULL, " ") );
			result = (op << 26)  + (rt << 16) + (rd << 11) + ( shamt<<6);
		}
		else if (!strcmp(OP, "srl")) {
			int op = 0;
			int rd = atoi(strtok(NULL, " ") + 1);
			int rt = atoi(strtok(NULL, " ") + 1);
			int shamt = atoi(strtok(NULL, " ") );
			result = (op << 26) + (rt << 16) + (rd << 11) + (shamt << 6)+2;
		}
		else if (!strcmp(OP, "subu")){
			int op = 0;
			int rd = atoi(strtok(NULL, " ")+1);
			int rs = atoi(strtok(NULL, " ")+1);
			int rt = atoi(strtok(NULL, " ")+1);
			result = (op <<26) + (rs<<21) + (rt<<16) +(rd<<11) + 0x23;
		}//J
		else if (!strcmp(OP, "j")) {
			int op = 2;
			
			int target = Textmem.get_addr(strtok(NULL, "\n") );
			
			result = (op << 26) + (target>>2) ;

		}
		else if (!strcmp(OP, "jal")) {
			int op = 3;
			
			int target = Textmem.get_addr(strtok(NULL, "\n") );
			result = (op << 26) + (target>>2);
		}
		else if (!strcmp(OP, "jr")) {

			int op = 0;
			int rs = atoi(strtok(NULL, " ") + 1);
			result = (op << 26) +(rs <<21)+8;
		}
		//std::cout << OP << std::endl;
		PC += 4;
		textsec[textsize] = result;
		textsize += 1;
		//printf("0x%lX\n", result);
	}


	char wfilename[128]={};
	strcpy(wfilename,argv[1]);

	char *ptr = strchr(wfilename,'.')+1;
	*ptr='o';
	FILE* file;
	file = fopen(wfilename, "wb");
	fprintf(file, "0x%x\n", textsize*4);
	fprintf(file, "0x%llx\n", (dataCounter - 0x10000000));
	for (int i = 0; i < textsize; i++) {
		fprintf(file, "0x%llx\n", textsec[i]);
	}
	//data section
	unsigned long long int dataaddr = 0x10000000;
	for (int i = 0; i < Datamem.Datacount; i++) {
		fprintf(file, "0x%llx\n",Datamem.get_data(dataaddr));
		dataaddr += 4;
	}
	fclose(file);
	return 0;
}
