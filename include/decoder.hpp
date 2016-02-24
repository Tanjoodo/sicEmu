#include "instruction.hpp"
#include "addressing_mode.hpp"

int InstructionLength(unsigned char bytes[]);
Instruction DecodeInstruction(unsigned char bytes[]);
AddressingMode DecodeAddressingMode(unsigned char * bytes);
void Dispatch(Instruction instruction, 
		AddressingMode addressing_mode, unsigned char *  operands);

