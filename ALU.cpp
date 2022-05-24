#include "ALU.h"

int ALU::func_or(int arg1, int arg2) {
	return (arg1 | arg2);
}

int ALU::func_nand(int arg1, int arg2) {
	return ~(arg1 & arg2);
}

int ALU::func_nor(int arg1, int arg2) {
	return ~(arg1 | arg2);
}

int ALU::func_and(int arg1, int arg2) {
	return (arg1 & arg2);
}

int ALU::func_add(int arg1, int arg2) {
	return (arg1 + arg2);
}

int ALU::func_sub(int arg1, int arg2) {
	return (arg1 - arg2);
}