#ifndef Mario_h
#define Mario_h
#include"Animal.h"
class Mario : public Animal {
private:
	bool mairoIsBig;
	int textureNumber;
	double jumpInitialVelocity;
public:
	Mario();
	void ChangeSprite(int, int);
	void reverseMarioSize();
	void Jump(double , sf::Time , bool , bool);
	void changeSpriteByNumber(int);
	double getJumpInitialVelocity() { return this->jumpInitialVelocity; }
public:
	static int marioSpriteFilterX ,smallRedMarioY, marioWidth,
	 smallMariolength,BigMarioLength;
};

#endif