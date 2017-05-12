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
	result |= operands[1] << 12;
	result |= operands[2];

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
	default: 
		return 0;
	}
}

int24 _get_final_operand(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 operand;
	switch (addressing_mode)
	{
		case Immediate:
			operand = int24(_get_f3_disp(operands));
			break;
		case ImmediateExtended:
			operand = int24(_get_f4_addr(operands));
			break;
		case ImmediatePlusPC:
			operand = int24(_get_f3_disp(operands) + reg::PC);
			break;
		case ImmediatePlusBase:
			operand = int24(_get_f3_disp(operands) + reg::B);
			break;

		default:
			unsigned char * loc = _fetch_operand(operands, addressing_mode);
			operand = int24(loc[0], loc[1], loc[2]);
	}
	return operand;
}

int24 * _get_register(unsigned char * operands, int register_index)
{
	int reg_id = operands[1] >> (register_index * 4);
	reg_id &= 0x0F; // zero out higher 4 bits

	switch (reg_id)
	{
		case 0:
			return &reg::A;
		case 1:
			return &reg::X;
		case 2:
			return &reg::L;
		case 3:
			return &reg::B;
		case 4:
			return &reg::S;
		case 5:
			return &reg::T;
		case 6:
			return &reg::F;
		case 8:
			return &reg::PC;
		case 9:
			return &reg::SW;
		default:
			return 0;
	}
}


void _compare(int24 o1, int24 o2)
{
	if ((int)o1 > (int)o2)
	{
		reg::SetBit(&reg::SW, true, 0);
	}
	else
	{
		reg::SetBit(&reg::SW, false, 0);
	}

	if ((int)o1 == (int)o2)
	{
		reg::SetBit(&reg::SW, true, 1);
	}
	else
	{
		reg::SetBit(&reg::SW, false, 1);
	}
}

void procADD(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 operand = _get_final_operand(operands, addressing_mode);	

	reg::A = reg::A + operand;
}

void procADDF(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procADDR(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 *reg1 = _get_register(operands, 0),
		  *reg2 = _get_register(operands, 1);
	*reg1 = *reg1 +  *reg2;
}

void procAND(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procCLEAR(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 *reg = _get_register(operands, 0);
	*reg = 0;
}

void procCOMP(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 operand =  _get_final_operand(operands, addressing_mode);
	_compare(reg::A, operand);	
}

void procCOMPF(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procCOMPR(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procDIV(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 operand = _get_final_operand(operands, addressing_mode);
	reg::A = int24((int)reg::A / (int)operand);
}

void procDIVF(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procDIVR(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 *reg1 = _get_register(operands, 0),
		  *reg2 = _get_register(operands, 1);
	*reg1 = *reg1 /  *reg2;
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
	int24 operand = _get_final_operand(operands, addressing_mode);
	reg::PC = operand;
	reg::pc_changed = true;
}

void procJEQ(unsigned char * operands, AddressingMode addressing_mode)
{
	if (reg::GetBit(&reg::SW, 1))
	{
		reg::PC = _get_final_operand(operands, addressing_mode);
		reg::pc_changed = true;
	}
}

void procJGT(unsigned char * operands, AddressingMode addressing_mode)
{
	if (reg::GetBit(&reg::SW, 0))
	{
		reg::PC = _get_final_operand(operands, addressing_mode);
		reg::pc_changed = true;
	}
}

void procJLT(unsigned char * operands, AddressingMode addressing_mode)
{
	if (!reg::GetBit(&reg::SW, 0))
	{
		reg::PC = _get_final_operand(operands, addressing_mode);
		reg::pc_changed = true;
	}
}

void procJSUB(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::L = reg::PC;
	reg::PC = _get_final_operand(operands, addressing_mode);
	reg::pc_changed = true;
}

void procLDA(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::A = _get_final_operand(operands, addressing_mode);
}

void procLDB(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::B = _get_final_operand(operands, addressing_mode);
}

void procLDCH(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procLDF(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::F = _get_final_operand(operands, addressing_mode);
}

void procLDL(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::L = _get_final_operand(operands, addressing_mode);
}

void procLDS(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::S = _get_final_operand(operands, addressing_mode);
}

void procLDT(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::T = _get_final_operand(operands, addressing_mode);
}

void procLDX(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::X = _get_final_operand(operands, addressing_mode);
}

void procLPS(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procMUL(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::A = int24((int)reg::A * (int)_get_final_operand(operands, addressing_mode));
}

void procMULF(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procMULR(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 *reg1 = _get_register(operands, 0),
		  *reg2 = _get_register(operands, 1);
	*reg1 = *reg1 *  *reg2;
}

void procNORM(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procOR(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::A = int24((int)reg::A | (int)_get_final_operand(operands, addressing_mode));
}

void procRD(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procRMO(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 *reg1 = _get_register(operands, 0),
		  *reg2 = _get_register(operands, 1);
	*reg1 = *reg2;
}

void procRSUB(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::PC = reg::L;
	reg::pc_changed = true;
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
	reg::A.store_into(_fetch_operand(operands, addressing_mode));
}

void procSTB(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::B.store_into(_fetch_operand(operands, addressing_mode));
}

void procSTCH(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procSTF(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::F.store_into(_fetch_operand(operands, addressing_mode));
}

void procSTI(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procSTL(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::L.store_into(_fetch_operand(operands, addressing_mode));
}

void procSTS(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::S.store_into(_fetch_operand(operands, addressing_mode));
}

void procSTSW(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::SW.store_into(_fetch_operand(operands, addressing_mode));
}

void procSTT(unsigned char * operands, AddressingMode addressing_mode)
{
	reg::T.store_into(_fetch_operand(operands, addressing_mode));
}

void procSUB(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 operand = _get_final_operand(operands, addressing_mode);
	reg::A = int24((int)reg::A - (int)operand);
}

void procSUBF(unsigned char * operands, AddressingMode addressing_mode)
{
}

void procSUBR(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 *reg1 = _get_register(operands, 0),
		  *reg2 = _get_register(operands, 1);
	*reg1 = *reg1 - *reg2;
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
	int24 operand = _get_final_operand(operands, addressing_mode);
	reg::X = int24((int)reg::X + 1);
	_compare(reg::X, operand);

}

void procTIXR(unsigned char * operands, AddressingMode addressing_mode)
{
	int24 * reg = _get_register(operands, 0);
	reg::X = int24((int)reg::X + 1);
	_compare(reg::X, *reg);
}

void procWD(unsigned char * operands, AddressingMode addressing_mode)
{
}
#endif
