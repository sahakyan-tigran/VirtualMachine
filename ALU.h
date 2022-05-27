#pragma once
#include <cstdint>

class ALU {

public:
	ALU() {}
	
	static uint8_t func_or(uint8_t arg1, uint8_t arg2);
	static uint8_t func_nand(uint8_t arg1, uint8_t arg2);
	static uint8_t func_nor(uint8_t arg1, uint8_t arg2);
	static uint8_t func_and(uint8_t arg1, uint8_t arg2);
	static uint8_t func_add(uint8_t arg1, uint8_t arg2);
	static uint8_t func_sub(uint8_t arg1, uint8_t arg2);
};
