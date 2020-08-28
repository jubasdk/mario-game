#ifndef animal_h
#define animal_h
#include <SFML/Graphics.hpp>
#include <string>

class Animal {
private:
	sf::Texture AnimalTexture;
	double velocity;
protected:
	sf::Sprite showingAnimalData;
public:
	static enum AnimalType;
public:
	Animal(Animal::AnimalType);
	Animal(std::string , int , int , int , int );
	class Error {};
	class TextureProblem {};
	void NormallyMoveAnimal(sf::Time, bool, bool);
	void ChangeSprite(int , int );
	sf::Sprite& getSprite();
	void setVelocity(double);
	double getVelocity();
	void setAnimalScale(double, double);
	void setAnimalPosition(double, double);
public:
	static int length, width , DragonX;
	static enum AnimalType {MACHROM , DRAGON};

};
#endif