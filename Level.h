#pragma once
#ifndef Level_H
#define Level_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ComplexBlock.h"
class Level {
private:
	sf::Texture BackGroundTexture;
	int levelNumber;
	
public:
	Level(std::string location, int number) {
		this->BackGroundTexture.loadFromFile(std::string(location));
		this->levelNumber = number;
	}
	sf::Vector2u getTextureSize() { return this->BackGroundTexture.getSize(); }
	void connectWithTexture(sf::Sprite& spriteToConnect) {
		spriteToConnect.setTexture(this->BackGroundTexture , true);
	}
	
};
#endif