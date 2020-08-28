#include "stdafx.h"
#include "mario.h"
int Mario::marioSpriteFilterX = 80;
int Mario::smallRedMarioY = 16;
int Mario::smallMariolength = 16;
int Mario::BigMarioLength = 33;
int Mario::marioWidth = 16;
void Mario::ChangeSprite(int x, int y) {
	if(this->mairoIsBig)
		this->showingAnimalData.setTextureRect(sf::IntRect(x+Mario::marioSpriteFilterX, y , 
			Mario::marioWidth , Mario::BigMarioLength));

	else this->showingAnimalData.setTextureRect(sf::IntRect(x + Mario::marioSpriteFilterX, y,
		Mario::marioWidth, Mario::smallMariolength));
}

void Mario::reverseMarioSize() {
	if (this->mairoIsBig)
		this->ChangeSprite(this->textureNumber*(Mario::marioWidth+1) , Mario::BigMarioLength);
	else this->ChangeSprite(0, 0);
	this->mairoIsBig = !this->mairoIsBig;
}
void Mario::changeSpriteByNumber(int number) {
	this->textureNumber = number;
	if (this->mairoIsBig)
		this->showingAnimalData.setTextureRect(sf::IntRect(number*(Mario::marioWidth+1) + Mario::marioSpriteFilterX, 0,
			Mario::marioWidth, Mario::BigMarioLength));

	else this->showingAnimalData.setTextureRect(sf::IntRect(number*(Mario::marioWidth+1) + Mario::marioSpriteFilterX, Mario::BigMarioLength+1,
		Mario::marioWidth, Mario::smallMariolength));
}

void Mario::Jump(double velocity, sf::Time timeFromAppearingInLastFrame , bool up , bool down) {
	if ((up&&down) || (velocity == 0))
		throw Animal::Error();
	else if(down)
		this->getSprite().move(0, velocity*timeFromAppearingInLastFrame.asSeconds());
	else if(up)
		this->getSprite().move(0,-1*velocity*timeFromAppearingInLastFrame.asSeconds());
}
Mario::Mario() :Animal("D:\\c++\\mario game\\NES - Super Mario Bros - Mario & Luigi.png",
	Mario::marioSpriteFilterX, Mario::BigMarioLength + 1, Mario::marioWidth, Mario::smallMariolength) {
	this->setAnimalScale(3,3);
	this->mairoIsBig = false;
	this->getSprite().setOrigin(8 , 8);
	this->setAnimalPosition(20, 431);
	this->jumpInitialVelocity = 1600;
}