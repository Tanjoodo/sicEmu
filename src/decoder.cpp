#include "../include/instruction.hpp"
#include "../include/instruction_procedures.hpp"
#include "../include/decoder.hpp"

bool _getBit(unsigned char byte, int bit_number)
{
	byte >>= bit_number;
	return byte & 1;
}

AddressingMode DecodeAddressingMode(unsigned char * bytes)
{
	if (InstructionLength(bytes) < 3)
		return UnknownAM; // addressing modes are a format 3 and 4 feature.
	unsigned char res = 0;
	res |= (bytes[0] << 6);
	res |= (bytes[1] >> 2);
	return (AddressingMode)res;
}

int InstructionLength(unsigned char bytes[])
{
	switch (bytes[0])
	{
		// format 1 -> 1 byte
		case FIX:
		case FLOAT:
		case HIO:
		case NORM:
		case SIO:
		case TIO:
			return 1;

		// format 2 -> 2 bytes
		case ADDR:
		case CLEAR:
		case COMPR:
		case DIVR:
		case MULR:
		case RMO:
		case SHIFTL:
		case SHIFTR:
		case SUBR:
		case SVC:
		case TIXR:
			return 2;

		default:
			if (_getBit(bytes[1], 4))
				return 4; //format 4 -> 4 bytes
			else
				return 3; //format 3 -> 3 bytes

	}


}

Instruction DecodeInstruction(unsigned char bytes[])
{
	// format 1 and 2, just return the first byte.
	switch(bytes[0])
	{
		case FIX:
		case FLOAT:
		case HIO:
		case NORM:
		case SIO:
		case TIO:
		case ADDR:
		case CLEAR:
		case COMPR:
		case DIVR:
		case MULR:
		case RMO:
		case SHIFTL:
		case SHIFTR:
		case SUBR:
		case SVC:
		case TIXR:
			return (Instruction)bytes[0];
	 	
	}

	// format 3 and 4, zero out last two bits
    return	(Instruction)(bytes[0] & 0b11111100);
}

void Dispatch(Instruction instruction,
		AddressingMode addressing_mode, unsigned char *  operands)
{
	switch(instruction)
	{
		case ADD:
			procADD(operands, addressing_mode);
			break;

		case ADDF:
			procADDF(operands, addressing_mode);
			break;

		case ADDR:
			procADDR(operands, addressing_mode);
			break;

		case AND:
			procAND(operands, addressing_mode);
			break;

		case CLEAR:
			procCLEAR(operands, addressing_mode);
			break;

		case COMP:
			procCOMP(operands, addressing_mode);
			break;

		case COMPF:
			procCOMPF(operands, addressing_mode);
			break;

		case COMPR:
			procCOMPR(operands, addressing_mode);
			break;

		case DIV:
			procDIV(operands, addressing_mode);
			break;

		case DIVF:
			procDIVF(operands, addressing_mode);
			break;

		case DIVR:
			procDIVR(operands, addressing_mode);
			break;

		case FIX:
			procFIX(operands, addressing_mode);
			break;

		case FLOAT:
			procFLOAT(operands, addressing_mode);
			break;

		case HIO:
			procHIO(operands, addressing_mode);
			break;

		case J:
			procJ(operands, addressing_mode);
			break;

		case JEQ:
			procJEQ(operands, addressing_mode);
			break;

		case JGT:
			procJGT(operands, addressing_mode);
			break;

		case JLT:
			procJLT(operands, addressing_mode);
			break;

		case JSUB:
			procJSUB(operands, addressing_mode);
			break;

		case LDA:
			procLDA(operands, addressing_mode);
			break;

		case LDB:
			procLDB(operands, addressing_mode);
			break;

		case LDCH:
			procLDCH(operands, addressing_mode);
			break;

		case LDF:
			procLDF(operands, addressing_mode);
			break;

		case LDL:
			procLDL(operands, addressing_mode);
			break;

		case LDS:
			procLDS(operands, addressing_mode);
			break;

		case LDT:
			procLDT(operands, addressing_mode);
			break;

		case LDX:
			procLDX(operands, addressing_mode);
			break;

		case LPS:
			procLPS(operands, addressing_mode);
			break;

		case MUL:
			procMUL(operands, addressing_mode);
			break;

		case MULF:
			procMULF(operands, addressing_mode);
			break;

		case MULR:
			procMULR(operands, addressing_mode);
			break;

		case NORM:
			procNORM(operands, addressing_mode);
			break;

		case OR:
			procOR(operands, addressing_mode);
			break;

		case RD:
			procRD(operands, addressing_mode);
			break;

		case RMO:
			procRMO(operands, addressing_mode);
			break;

		case RSUB:
			procRSUB(operands, addressing_mode);
			break;

		case SHIFTL:
			procSHIFTL(operands, addressing_mode);
			break;

		case SHIFTR:
			procSHIFTR(operands, addressing_mode);
			break;

		case SIO:
			procSIO(operands, addressing_mode);
			break;

		case SSK:
			procSSK(operands, addressing_mode);
			break;

		case STA:
			procSTA(operands, addressing_mode);
			break;

		case STB:
			procSTB(operands, addressing_mode);
			break;

		case STCH:
			procSTCH(operands, addressing_mode);
			break;

		case STF:
			procSTF(operands, addressing_mode);
			break;

		case STI:
			procSTI(operands, addressing_mode);
			break;

		case STL:
			procSTL(operands, addressing_mode);
			break;

		case STS:
			procSTS(operands, addressing_mode);
			break;

		case STSW:
			procSTSW(operands, addressing_mode);
			break;

		case STT:
			procSTT(operands, addressing_mode);
			break;

		case SUB:
			procSUB(operands, addressing_mode);
			break;

		case SUBF:
			procSUBF(operands, addressing_mode);
			break;

		case SUBR:
			procSUBR(operands, addressing_mode);
			break;

		case SVC:
			procSVC(operands, addressing_mode);
			break;

		case TD:
			procTD(operands, addressing_mode);
			break;

		case TIO:
			procTIO(operands, addressing_mode);
			break;

		case TIX:
			procTIX(operands, addressing_mode);
			break;

		case TIXR:
			procTIXR(operands, addressing_mode);
			break;

		case WD:
			procWD(operands, addressing_mode);
			break;
	}
}
