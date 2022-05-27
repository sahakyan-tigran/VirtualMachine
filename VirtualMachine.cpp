#include <iostream>
#include <fstream>
#include <string>
#include "ALU.h"
#include "Cond.h"
#include <bitset>
#include <vector>
#include <cmath>

int registers[16]{}, ram[1024]{}, counter{}, base_reg{};

typedef std::bitset<32> Instruction;

void writeInDestination(int number, int destination) {
    if (destination >= 2 && destination <= 17) {
        registers[destination - 2] = number;
        return;
    }
    switch (destination) {
    case 0: //(ram)
        ram[base_reg] = number;
        break;
    case 1: //(base register)
        base_reg = number;
        break;
    
    case 19: //out
        std::cout << number << std::endl;
        break;
    default:
        throw std::exception("Wrong destination");
        break;
    }
}

void doingALU(int arg1, int arg2, int operation, int destination) {
    int result;
    ALU obj;
    switch (operation) {
    case 0: //OR
        result = obj.func_or(arg1, arg2);
        break;
    case 1: //NAND
        result = obj.func_nand(arg1, arg2);
        break;
    case 2: //NOR
        result = obj.func_nor(arg1, arg2);
        break;
    case 3: //AND
        result = obj.func_and(arg1, arg2);
        break;
    case 4: //ADD
        result = obj.func_add(arg1, arg2);
        break;
    case 5: //SUB
        result = obj.func_sub(arg1, arg2);
        break;
    default:
        throw std::exception("undefined operation");
        break;
    }
    writeInDestination(result, destination);
}

void doingCond(int arg1, int arg2, int operation, int destination) {
    int result{};
    Cond obj;
    switch (operation) {
    case 0: //NEVER
        result = obj.never(arg1, arg2);
        break;
    case 1: //=
        result = obj.equal(arg1, arg2);
        break;
    case 2: //<
        result = obj.less(arg1, arg2);
        break;
    case 3: //<=
        result = obj.lessOrEqual(arg1, arg2);
        break;
    case 4: //always
        result = obj.always(arg1, arg2);
        break;
    case 5: //!=
        result = obj.notEqual(arg1, arg2);
        break;
    case 6: //>=
        result = obj.bigOrEqual(arg1, arg2);
        break;
    case 7: //>
        result = obj.big(arg1, arg2);
        break;
    }
    writeInDestination(result, destination);
}

int detectSource(int source) {
    if (source >= 2 && source <= 17) {
        return registers[source - 2];
    }
    switch (source) {
    case 0: //(ram)
        return ram[base_reg];
    case 1: //(base register)
        return base_reg;
    case 18: //in
        std::cout << "WRITE NUMBER" << std::endl;
        int returnValue;
        std::cin >> returnValue;
        return returnValue;
    default:
        throw std::exception("Wrong source");
        break;
    }
}


void doingInstruction(const Instruction& bitset) {
    ++counter;

    std::bitset<8> first(bitset.to_ullong() >> 24);
    std::bitset<8> second(bitset.to_ullong() >> 16);
    std::bitset<8> third(bitset.to_ullong() >> 8);
    std::bitset<8> fourth(bitset.to_ullong());
   
    int arg1{}, arg2{}, operation{}, destination{};

    for (int i = 0; i < 3; ++i) {
        if (first[i]) {
            operation += 1 << i;
        }
    }
    
    if (first[7]) {
        for (int i = 0; i < 8; ++i) {
            if (second[i]) {
                arg1 += (1 << i);
            }
        }
    }
    else {
        int src1{};
        for (int i = 0; i < 5; ++i) {
            if (second[i]) {
                src1 += 1 << i;
            }
        }
        arg1 = detectSource(src1);
    }
    if (first[6]) {
        for (int i = 0; i < 8; ++i) {
            if (third[i]) {
                arg2 += (1 << i);
            }
        }
    }
    else {
        int src2{};
        for (int i = 0; i < 5; ++i) {
            if (third[i]) {
                src2 += (1 << i);
            }
        }
        arg2 = detectSource(src2);
    }
    for (int i = 0; i < 5; ++i) {
        if (fourth[i]) {
            destination += (1 << i);
        }
    }
    if (first[3]) { doingALU(arg1, arg2, operation, destination); }
    else { doingCond(arg1, arg2, operation, destination); }
        
}

std::vector<Instruction> readInstructionsFromFile(std::string fileName) {
    int size = std::ifstream(fileName, std::ios::binary | std::ios::ate).tellg();
    std::ifstream myfile(fileName, std::ios::binary);
    typedef unsigned char byte;
    byte* buffer = new byte[size];
    myfile.read((char*)buffer, size);
    std::vector<Instruction> instructions;
    for (int i = 0; i < size; i += 4) {
        uint32_t number = buffer[i];
        for (int j = i + 1; j < i + 4; ++j) {
            number <<= 8;
            number += buffer[j];
        }
        instructions.emplace_back(number);
    }
    delete[] buffer;
    return instructions;
}


int main()
{
    std::string fileName{};
    std::cout << "Enter full path of your binary file" << std::endl;
    std::cin >> fileName;
    fileName = "C:\\Users\\Gor\\abcd.bin";
    auto instructions = readInstructionsFromFile(fileName);
    for (const Instruction& instruction : instructions) {
        doingInstruction(instruction);
    }
    std::cout << ram[0];
    return 0;
}
