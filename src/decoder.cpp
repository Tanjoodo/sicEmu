#include "../include/instruction.hpp"
#include "../include/decoder.hpp"

bool _getBit(unsigned char byte, int bit_number)
{
	byte >>= bit_number;
	return byte & 1;
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

Instruction Decode(unsigned char bytes[])
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

	// format 2 and 4, zero out last two bits
    return	(Instruction)(bytes[0] & 0b11111100);
}
