#include "../include/instruction.hpp"
#include "../include/instruction_procedures.hpp"
#include "../include/registers.hpp"
#include "../include/memory.hpp"
#include "../include/decoder.hpp"

#include <iostream>
#include <fstream>

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

	bool GetBit(int24 *reg, int bit_num)
	{
		return (((int)*reg >> bit_num) & 1) > 0;
	}

	void SetBit(int24 *reg, bool value, int bit_num)
	{
		if (value == true)
		{
			*reg = int24((int)reg::SW | (1 << bit_num));
		}
		else
		{
			*reg = int24((int)reg::SW & ~(1 << bit_num));
		}
	}
}

unsigned char mem[0x100000] = {};


int main(int argc, char **argv)
{
	using namespace std;
	char *bytes;
	size_t size = 0;
	if (argc < 2)
	{
		cout << "Please enter a file name" << endl;
		return 1;
	}
	else
	{
		ifstream inFile;
		inFile.open(argv[1], ios::in | ios::binary | ios::ate);
		if (inFile.is_open())
		{
			inFile.seekg(0, ios::end);
			size = inFile.tellg();

			inFile.seekg(0, ios::beg);

			bytes = new char[size];
			inFile.read(bytes, size);
			std::copy(bytes, bytes + size, mem);

		}
		else
		{
			cout << "File input failed" << endl;
		}
	}

	int t;
	cout << "Enter number of locations you wish to change: ";
	cin >> t;

	while (t--)
	{
		int location;
		int val;
		cout << "Enter address to change at followed by the value: ";
		cin >> hex >> location;
		cin >> hex >> val;
		mem[location] = val;
	}

	reg::PC = int24(0);
	reg::pc_changed = false;

	while (true)
	{
		Instruction instruction = DecodeInstruction(&mem[(int)reg::PC]);
		if (instruction == WD)
			break;
		AddressingMode am = DecodeAddressingMode(&mem[(int)reg::PC]);
		Dispatch(instruction, am, &mem[(int)reg::PC]);
		int instruction_length = InstructionLength(&mem[(int)reg::PC]);
		if (!reg::pc_changed)
			reg::PC = int24((int)reg::PC + instruction_length);
		else
			reg::pc_changed= false;
	}

	do
	{
		int location;
		cout << "Query memory location: ";
		cin >> hex >> location;
		cin.ignore();
		cout << "0x" << hex << (int)mem[location] << endl;
	} while (true);

	return 0;
}
