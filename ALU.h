#pragma once

class ALU {

public:
	ALU() : m_data(0){}
	
	int func_or(int arg1, int arg2);
	int func_nand(int arg1, int arg2);
	int func_nor(int arg1, int arg2);
	int func_and(int arg1, int arg2);
	int func_add(int arg1, int arg2);
	int func_sub(int arg1, int arg2);

private:
	int m_data;
};
