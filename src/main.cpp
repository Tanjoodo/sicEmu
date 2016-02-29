#include "../include/instruction.hpp"
#include "../include/instruction_procedures.hpp"
#include "../include/registers.hpp"
#include "../include/memory.hpp"

#include <iostream>

namespace reg
{
	bool pc_changed = false;
	int24 A, // 0
		   X,  // 1
		   L,  // 2
		   PC, // 8
		   SW, // 9
		   B,  // 3
		   S,  // 4
		   T,  // 5
		   F;  // 6
}

unsigned char mem[0x100000] = {};


int main()
{
	return 0;
}
