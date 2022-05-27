#include "ALU.h"

uint8_t ALU::func_or(uint8_t arg1, uint8_t arg2) {
	return (arg1 | arg2);
}

uint8_t ALU::func_nand(uint8_t arg1, uint8_t arg2) {
	return ~(arg1 & arg2);
}

uint8_t ALU::func_nor(uint8_t arg1, uint8_t arg2) {
	return ~(arg1 | arg2);
}

uint8_t ALU::func_and(uint8_t arg1, uint8_t arg2) {
	return (arg1 & arg2);
}

uint8_t ALU::func_add(uint8_t arg1, uint8_t arg2) {
	return (arg1 + arg2);
}

uint8_t ALU::func_sub(uint8_t arg1, uint8_t arg2) {
	return (arg1 - arg2);
}