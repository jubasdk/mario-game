#pragma once
#ifndef COMPLEXBLOCK
#define COMPLEXBLOCK
#include <Vector>
#include "NormalBlock.h"
class ComplexBlock{
private:
	int numberRows;
	std::vector<NormalBlock> blocks;
public:
	ComplexBlock(int num, std::vector<NormalBlock> Blocks) {
		this->numberRows = num;
		this->blocks.operator=(Blocks);
	}
	void setNumberRows(int val) { this->numberRows = val; }
	void setBlocks(std::vector<NormalBlock> val) { this->blocks.operator=(val); }
	int getNumberRows() { return this->numberRows; }
	std::vector<NormalBlock>& getBlocks() {
		std::vector<NormalBlock> blocks = this->blocks;
		return blocks;
	}
	double getBlockXStart() {return this->blocks.operator[](0).getStartX();}

};
#endif