#include "instruction.hpp"
#include "addressing_mode.hpp"

int InstructionLength(char bytes[]);
Instruction DecodeInstruction(char bytes[]);
AddressingMode DecodeAddressingMode(unsigned char * instruction_bytes);
void Dispatch(Instruction instruction, 
		AddressingMode addressing_mode, unsigned char *  operands);

