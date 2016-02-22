#include "instruction.hpp"

int InstructionLength(char bytes[]);
Instruction Decode(char bytes[]);
void Dispatch(Instruction instruction, 
		AddressingMode addressing_mode, unsigned char *  operands);
