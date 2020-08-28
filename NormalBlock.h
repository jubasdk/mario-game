#pragma once
#ifndef NORMALBLOCK
#define NORMALBLOCK
class NormalBlock{
private:
	double startX,
		startY,endX,
		hight;
public:
	double getStartX() { return this->startX; }
	double getStartY() { return this->startY; }
	double getEndX() { return this->endX; }
	double getHight() { return this->hight; }
	void setStartX(double val) { this->startX = val; }
	void setStartY(double val) { this->startY = val; }
	void setEndX(double val) { this->endX = val; }
	void setHight(double val) { this->hight = val; }
	void ling() {}
};
#endif