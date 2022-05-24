#include <iostream>
#include <fstream>
#include <string>
#include "ALU.h"
#include "Cond.h"
#include <bitset>
#include <cmath>

int registers[16]{}, ram[1024]{}, counter{}, base_reg{};

void writeInDestination(int number,int destination) {
    switch (destination) {
    case 0: //(ram)
        ram[base_reg] = number;
        break;
    case 1: //(base register)
        base_reg = number;
        break;
    case 2: //r0
        registers[0] = number;
        break;
    case 3: //r1
        registers[1] = number;
        break;
    case 4: //r2
        registers[2] = number;
        break;
    case 5: //r3
        registers[3] = number;
        break;
    case 6: //r4
        registers[4] = number;
        break;
    case 7: //r5
        registers[5] = number;
        break;
    case 8: //r6
        registers[6] = number;
        break;
    case 9: //r7
        registers[7] = number;
        break;
    case 10: //r8
        registers[8] = number;
        break;
    case 11: //r9
        registers[9] = number;
        break;
    case 12: //r10
        registers[10] = number;
        break;
    case 13: //r11
        registers[11] = number;
        break;
    case 14: //r12
        registers[12] = number;
        break;
    case 15: //r13
        registers[13] = number;
        break;
    case 16: //r14
        registers[14] = number;
        break;
    case 17: //r15
        registers[15] = number;
        break;
    case 19: //out
        ///////////
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
        writeInDestination(result, destination);
        break;
    case 1: //NAND
        result = obj.func_nand(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 2: //NOR
        result = obj.func_nor(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 3: //AND
        result = obj.func_and(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 4: //ADD
        result = obj.func_add(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 5: //SUB
        result = obj.func_sub(arg1, arg2);
        writeInDestination(result, destination);
        break;
    default:
        throw std::exception("undefined operation");
        break;
    }
}

void doingCond(int arg1, int arg2, int operation, int destination) {
    int result{};
    Cond obj;
    switch (operation) {
    case 0: //NEVER
        result = obj.never(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 1: //=
        result = obj.equal(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 2: //<
        result = obj.less(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 3: //<=
        result = obj.lessOrEqual(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 4: //always
        result = obj.always(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 5: //!=
        result = obj.notEqual(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 6: //>=
        result = obj.bigOrEqual(arg1, arg2);
        writeInDestination(result, destination);
        break;
    case 7: //>
        result = obj.big(arg1, arg2);
        writeInDestination(result, destination);
        break;
    }
}

int detectingSource(int source) {
    int returnValue{};
    switch (source) {
    case 0: //(ram)
        returnValue = ram[base_reg];
        break;
    case 1: //(base register)
        returnValue = base_reg;
        break;
    case 2: //r0
        returnValue = registers[0];
        break;
    case 3: //r1
        returnValue = registers[1];
        break;
    case 4: //r2
        returnValue = registers[2];
        break;
    case 5: //r3
        returnValue = registers[3];
        break;
    case 6: //r4
        returnValue = registers[4];
        break;
    case 7: //r5
        returnValue = registers[5];
        break;
    case 8: //r6
        returnValue = registers[6];
        break;
    case 9: //r7
        returnValue = registers[7];
        break;
    case 10: //r8
        returnValue = registers[8];
        break;
    case 11: //r9
        returnValue = registers[9];
        break;
    case 12: //r10
        returnValue = registers[10];
        break;
    case 13: //r11
        returnValue = registers[11];
        break;
    case 14: //r12
        returnValue = registers[12];
        break;
    case 15: //r13
        returnValue = registers[13];
        break;
    case 16: //r14
        returnValue = registers[14];
        break;
    case 17: //r15
        returnValue = registers[15];
        break;
    case 18: //in
        std::cout << "WRITE NUMBER" << std::endl;
        std::cin >> returnValue;
        break;
    default:
        throw std::exception("Wrong source");
        break;
    }
    return returnValue;
}


void doingInstruction(std::bitset<32>& bitset) {
    ++counter;

    std::string first{}, second{}, third{}, fourth{};
    for (int j = 31; j > 23; --j) {
        first += (bitset[j] + '0');
    }
    for (int j = 23; j > 15; --j) {
        second += (bitset[j] + '0');
    }
    for (int j = 15; j > 7; --j) {
        third += (bitset[j] + '0');
    }
    for (int j = 7; j >= 0; --j) {
        fourth += (bitset[j] + '0');
    }
   
    int arg1{}, arg2{}, operation{}, destination{};

    for (int i = 7, j = 0; i >= 5; --i, ++j) {
        if (first[i] - '0' == 1) {
            operation += pow(2, j);
        }
    }
    
    if (first[0] == '1') {
        for (int i = 7, j = 0; i >= 0; --i, ++j) {
            if (second[i] - '0' == 1) {
                arg1 += pow(2, j);
            }
        }
    }
    else {
        int src1{};
        for (int i = 7, j = 0; i >= 3; --i, ++j) {
            if (second[i] - '0' == 1) {
                src1 += pow(2, j);
            }
        }
        arg1 = detectingSource(src1);
    }
    if (first[1] == '1') {
        for (int i = 7, j = 0; i >= 0; --i, ++j) {
            if (third[i] - '0' == 1) {
                arg2 += pow(2, j);
            }
        }
    }
    else {
        int src2{};
        for (int i = 7, j = 0; i >= 3; --i, ++j) {
            if (third[i] - '0' == 1) {
                src2 += pow(2, j);
            }
        }
        arg2 = detectingSource(src2);
    }
    for (int i = 7, j = 0; i >= 3; --i, ++j) {
        if (fourth[i] - '0' == 1) {
            destination += pow(2, j);
        }
    }
    if (first[4] - '0' == 1) { doingALU(arg1, arg2, operation, destination); }
    if (first[4] - '0' == 0) { doingCond(arg1, arg2, operation, destination); }
        
}

void readFromFile(std::string fileName) {
    int size = std::ifstream(fileName, std::ios::binary | std::ios::ate).tellg();
    std::ifstream myfile(fileName, std::ios::binary);
    typedef unsigned char byte;
    byte* buffer = new byte[size];
    myfile.read((char*)buffer, size);
    for (int i = 0; i < size; i += 4) {
        uint32_t number = buffer[i];
        for (int j = i + 1; j < i + 4; ++j) {
            number <<= 8;
            number += buffer[j];
        }
        std::bitset<32> bitset(number);
        doingInstruction(bitset);
    }
    delete[] buffer;
}


int main()
{
    std::string fileName{};
    std::cout << "Enter full path of your binary file" << std::endl;
    std::cin >> fileName;
    readFromFile(fileName);
    std::cout << ram[0];
    return 0;
}
