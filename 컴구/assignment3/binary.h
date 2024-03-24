#ifndef BINARY_H
#define BINARY_H

unsigned int extend(short int X, bool sign_extend=true);

unsigned int cut(unsigned int X, int lcut, int rcut);

unsigned int char2int(char* word);

template<typename J>
J mux(J X, J Y, bool signal){
	if(signal){
		return X;
	}
	return Y;
};


#endif
