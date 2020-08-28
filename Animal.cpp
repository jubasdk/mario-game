#include "stdafx.h"
#include"Animal.h"
int Animal::length = 16;
int Animal::width = 16;
int Animal::DragonX = 0; //to be changed later*****************************************************************



Animal::Animal(std::string location , int startFromX , int startFromY , int width , int length) {
	this->velocity = 0;
	if (!this->AnimalTexture.loadFromFile(location)) {
		throw Animal::TextureProblem();
	}
	this->showingAnimalData.setTexture(this->AnimalTexture, true);
	this->showingAnimalData.setTextureRect(sf::IntRect(startFromX, startFromY,width, length));
}

Animal::Animal(Animal::AnimalType animalType) {
	this->velocity = 0;
	if (!this->AnimalTexture.loadFromFile(
		"D:\\c++\\mario game\\NES - Super Mario Bros - Enemies & Bosses.png")) {
		throw Animal::TextureProblem();
	}
	this->showingAnimalData.setTexture(this->AnimalTexture, true);
	if (animalType == Animal::AnimalType::DRAGON)
		this->showingAnimalData.setTextureRect(sf::IntRect(Animal::DragonX, 0, Animal::width, Animal::length));
	else this->showingAnimalData.setTextureRect(sf::IntRect(0, 0, Animal::width, Animal::length));
}
void Animal::setAnimalPosition(double x, double y) {this->showingAnimalData.setPosition(x, y);}
void Animal::NormallyMoveAnimal(sf::Time timeForLastFrame , bool MoveLeft , bool MoveRight) {
	if (MoveLeft == MoveRight)
		throw Animal::Error();
	else if (MoveLeft) 
		this->showingAnimalData.move(-1 * timeForLastFrame.asSeconds()* (velocity), 0);
	else if (MoveRight) 
		this->showingAnimalData.move(timeForLastFrame.asSeconds()* (velocity), 0);
		
}
void Animal::ChangeSprite(int x, int y) {
	this->showingAnimalData.setTextureRect(sf::IntRect(x, y, Animal::width, Animal::length));
}

sf::Sprite& Animal::getSprite() {
	return this->showingAnimalData;
}
void Animal::setVelocity(double val) { this->velocity = val; }
double Animal::getVelocity() { return this->velocity;}

void Animal::setAnimalScale(double x, double y) {this->showingAnimalData.setScale(x, y);}





