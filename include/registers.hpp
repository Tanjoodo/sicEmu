#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include "int24.hpp"
namespace reg
{
	extern bool pc_changed;
	extern int24 A, // 0
		   X,  // 1
		   L,  // 2
		   PC, // 8
		   SW, // 9
		   B,  // 3
		   S,  // 4
		   T,  // 5
		   F;  // 6

	void SetBit(int24 * reg, bool value, int bit_num);
	
	bool GetBit(int24 * reg, int bit_num);
}
#endif
