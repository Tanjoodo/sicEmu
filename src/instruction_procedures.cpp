#ifndef INSTRUCTION_PROCEDURES_HPP
#define INSTRUCTION_PROCEDURES_HPP

#include "../include/instruction_procedures.hpp"
#include "../include/addressing_mode.hpp"
#include "../include/registers.hpp"
#include "../include/memory.hpp"
#include "../include/int24.hpp"

// Also use for Immediate
int _get_f3_disp(unsigned char * operands)
{
	int result = 0;
	result |= operands[1] << 6;
	result |= operands[2] >> 2;

	return result;	
}

// Also use for ImmediateExtended
int _get_f4_addr(unsigned char * operands)
{
	int result = 0;
	result |= operands[1] << 4;
	result |= operands[2] >> 4;

	return result;

}

int _get_simple_addr(unsigned char * operands)
{
	int result = 0;
	result |= operands[1] << 1;
	return result;
}

// Don't use with Immediate, ImmediateExtended, ImmediatePlusPC or ImmediatePlusBase
unsigned char * _fetch_operand(unsigned char * operands, AddressingMode addressing_mode)
{
	switch (addressing_mode)
	{
	case Direct:
		return &mem[_get_f3_disp(operands)];
	case DirectExtended:
		return &mem[_get_f4_addr(operands)];
	case RelativePC:
		return &mem[reg::PC + _get_f3_disp(operands)];
	case RelativeBase:
		return &mem[reg::B + _get_f3_disp(operands)];
	case Indexed:
		return &mem[reg::X + _get_f3_disp(operands)];
	case IndexedExtended:
		return &mem[reg::X + _get_f4_addr(operands)];
	case IndexedPC:
		return &mem[reg::PC + _get_f3_disp(operands) + reg::X];
	case IndexedBase:
		return &mem[reg::B + _get_f3_disp(operands) + reg::X];
	case Simple:
		return &mem[_get_simple_addr(operands)];
	case SimpleIndexed:
		return &mem[reg::X + _get_simple_addr(operands)];
	case Indirect:
		return &mem[mem[_get_f3_disp(operands)]];
	case IndirectExtended:
		return &mem[mem[_get_f4_addr(operands)]];
	case IndirectPC:
		return &mem[mem[_get_f3_disp(operands) + reg::PC]];
	case IndirectBase:
		return &mem[mem[_get_f3_disp(operands) + reg::B]];
	}
	return 0;
}

void procADD(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procADDF(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procADDR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procAND(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procCLEAR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procCOMP(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procCOMPF(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procCOMPR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procDIV(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procDIVF(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procDIVR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procFIX(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procFLOAT(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procHIO(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procJ(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procJEQ(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procJGT(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procJLT(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procJSUB(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDA(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDB(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDCH(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDF(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDL(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDS(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDT(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLDX(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procLPS(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procMUL(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procMULF(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procMULR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procNORM(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procOR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procRD(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procRMO(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procRSUB(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSHIFTL(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSHIFTR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSIO(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSSK(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTA(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTB(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTCH(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTF(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTI(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTL(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTS(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTSW(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSTT(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSUB(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSUBF(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSUBR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procSVC(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procTD(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procTIO(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procTIX(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procTIXR(unsigned char * operands, AddressingMode addressing_mode)
{
}
void procWD(unsigned char * operands, AddressingMode addressing_mode)
{
}
#endif
