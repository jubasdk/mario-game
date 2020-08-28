#include "stdafx.h"
#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() {
	this->right = false; this->left = false;
	this->up = false; this->rightR = true;
	this->leftR = false; 
	this->currentLevel = 1;
	this->levels.push_back(*(new Level(std::string("D:\\c++\\mario game\\NES - Super Mario Bros - World 1-1.jpg"), 1)));
	this->levels.operator[](this->currentLevel-1).connectWithTexture(this->backGroundSprite);
	this->startAtLevelTexture = 0;
	this->backGroundSprite.setTextureRect(sf::IntRect(startAtLevelTexture, startAtLevelTexture+9, 270, 210));
	this->backGroundSprite.setScale(3.7 , 2.4);
	this->Hero.setVelocity(100);
	this->gravityInteraction = 40;//5 sfml/second^2 of accelration towards the surface of the ground
	this->sfmlCounter = 0;
}

void Game::moveHero(sf::Time timePerFrame,  bool rDirection , 
	bool lDirection, bool uDirection = false, bool dDirection = false, double velocity = 0 /*will not be used*/) {
	if (rDirection || lDirection) {
		if (this->Hero.getSprite().getPosition().x >= 600 && 
			rDirection && this->startAtLevelTexture!=this->levels.operator[](this->currentLevel-1).getTextureSize().x-270) {
			if (this->sfmlCounter < 0)
				this->sfmlCounter = 0;
			this->sfmlCounter += this->Hero.getVelocity()*timePerFrame.asSeconds();
			if (this->sfmlCounter > 3.6) {
				this->startAtLevelTexture++;
				this->sfmlCounter = 0;
			}
			this->backGroundSprite.setTextureRect(sf::IntRect(this->startAtLevelTexture , 9 , 270, 210));
		}
		else if (this->startAtLevelTexture > 0 && lDirection && this->Hero.getSprite().getPosition().x <=600) {
			if (this->sfmlCounter > 0)
				this->sfmlCounter = 0;
			this->sfmlCounter -= this->Hero.getVelocity()*timePerFrame.asSeconds();
			if (this->sfmlCounter < -3.6) {
				this->startAtLevelTexture--;
				this->sfmlCounter = 0;
			}
			this->backGroundSprite.setTextureRect(sf::IntRect(this->startAtLevelTexture, 9, 270, 210));
		}
		else {
			try {/*check for block before movment*/ 
				this->Hero.NormallyMoveAnimal(sf::Time(timePerFrame), lDirection, rDirection); }
			catch (Animal::Error exception) { throw Game::ErrorWhenCallingFunction(); }
		}
	}
	if (uDirection || dDirection) {//currently not used
		try { this->Hero.Jump(velocity, sf::Time(timePerFrame), uDirection, dDirection); }
		catch (Animal::Error exception) { throw Game::ErrorWhenCallingFunction(); }
	}
	if (!(rDirection || lDirection || uDirection || dDirection)) throw Game::ErrorWhenCallingFunction();
}


void Game::Run() {
	sf::Event event; bool rightLastFrame = false , leftLastFrame = false;
	sf::Clock clock , hero_Animation_Clock , afterReleaseClock; 
	sf::Time timePerFrame = sf::Time::Zero, 
		hero_Animation_Time = sf::Time::Zero, 
		afterReleaseTime = sf::Time::Zero;
	int textureNumber = 0; bool maxPointIsEncuntered = false; double currentJumpVelocity = 0;
	double prevPositionCheck = 0;
	bool HandlingKeyRelease = false , rightRelesed = false, leftReleased = false ,  inJump = false;
	this->window.create(sf::VideoMode(1000, 500), "Super Mario Bros Gamo");
	while (this->window.isOpen()) {
		timePerFrame.operator=(clock.restart());
		this->right = false; this->left = false;
		this->up = false; this->rightR = false;
		this->leftR = false;
		while (this->window.pollEvent(event)) {
			if ((event.type == sf::Event::KeyReleased) && !inJump) {
				if (event.key.code == sf::Keyboard::Right)
					this->rightR = true;
				else if (event.key.code == sf::Keyboard::Left)
					this->leftR = true;
			}
			if (event.type == sf::Event::Closed)
				this->window.close();
		}
		this->handlePressEvent();
		this->CheckChangingCurrentBlocks();
		this->makeHeroMove(afterReleaseClock, hero_Animation_Clock,
			timePerFrame,hero_Animation_Time, afterReleaseTime,
			HandlingKeyRelease,rightRelesed, leftReleased, rightLastFrame, 
			inJump , maxPointIsEncuntered,textureNumber ,currentJumpVelocity , prevPositionCheck);

		this->CheckLevelCompelet();

		this->Render();
	}
}



void Game::makeHeroMove(sf::Clock& afterReleaseClock , sf::Clock& hero_Animation_Clock , 
	sf::Time& timePerFrame,sf::Time& hero_Animation_Time , sf::Time& afterReleaseTime,
	bool& HandlingKeyRelease, bool& rightRelesed, bool& leftReleased , bool& rightLastFrame , 
	bool& inJump , bool& maxPointIsEncuntered , int& textureNumber , double& currentJumpVelocity , double& prevPositionCheck) {
	double deltaY = 431-this->Hero.getSprite().getPosition().y;
	int y = 0;
	if (inJump) {
		//what will happens in the vetical movment
		if (deltaY >= 200/*200 is the jump max distance*/)
			maxPointIsEncuntered = true;
		y = prevPositionCheck - this->Hero.getSprite().getPosition().y;
		if (!maxPointIsEncuntered) {
			try {
				this->Hero.Jump(currentJumpVelocity , timePerFrame, true , false);
			}
			catch (Animal::Error) {
				//to be handeled later
				cout << "error in values sent to the function jump" << endl;
			}
			if (y >= 5) {
				currentJumpVelocity -= this->gravityInteraction; /*have error in execution due to approiximation error*/
				prevPositionCheck = this->Hero.getSprite().getPosition().y;
			}
		}
		else {
			try {
				this->Hero.Jump(currentJumpVelocity, timePerFrame, false, true);
			}
			catch (Animal::Error) {
				//to be handeled later
				cout << "error in values sent to the function jump" << endl;
			}
			if (y <= -5) {
				currentJumpVelocity += this->gravityInteraction; /*have error in execution due to approiximation error*/
				prevPositionCheck = this->Hero.getSprite().getPosition().y;
			}
			deltaY = 431 - this->Hero.getSprite().getPosition().y;
			if (deltaY <= 0) {
				inJump = false;//jump ended
				this->Hero.setAnimalPosition(this->Hero.getSprite().getPosition().x, 431);
			}
		}
	}
	else if (this->up && !HandlingKeyRelease) {
		inJump = true;
		this->Hero.changeSpriteByNumber(5);
		maxPointIsEncuntered = false;
		currentJumpVelocity = this->Hero.getJumpInitialVelocity();
		prevPositionCheck = this->Hero.getSprite().getPosition().y;
	}
	if (!HandlingKeyRelease) {
		if (this->right == true || this->left == true) {
			if ((this->rightR || this->leftR) && !inJump) {//what will happens when releasing  right arrow key and pressing the left arrow
				afterReleaseClock.restart();
				HandlingKeyRelease = true;
				rightRelesed = this->rightR;
				leftReleased = this->leftR;
				this->Hero.changeSpriteByNumber(4);
			}
			if (!HandlingKeyRelease) {
				try { this->moveHero(sf::Time(timePerFrame), this->right, this->left, false); }
				catch (Game::ErrorWhenCallingFunction& obj) {/* ****************To be Handeld later***********/
					cout << "error when calling move hero function" << endl;
				}
				if (this->right)
					this->Hero.setAnimalScale(3, 3);
				else this->Hero.setAnimalScale(-3, 3);
				if (!inJump) {
					hero_Animation_Time.operator=(hero_Animation_Clock.getElapsedTime());
					if (hero_Animation_Time.asSeconds() > 0.1) {
						if (textureNumber == 3)
							textureNumber = 0;
						this->Hero.changeSpriteByNumber(++textureNumber);
						hero_Animation_Clock.restart();
					}
					rightLastFrame = this->right;
				}
			}
		}
		else {
			this->sfmlCounter = 0;
			if(!inJump)
				this->Hero.changeSpriteByNumber(0); 
		}
	}
	else {
		if (rightRelesed)
			this->Hero.setAnimalScale(3, 3);
		else this->Hero.setAnimalScale(-3, 3);
		try { this->moveHero(sf::Time(timePerFrame), rightRelesed, leftReleased); }
		catch (Game::ErrorWhenCallingFunction& obj) {/* ****************To be Handeld later***********/
			cout << "error when calling move hero function" << endl;
		}
		afterReleaseTime.operator=(afterReleaseClock.getElapsedTime());
		if (afterReleaseTime.asSeconds() > 0.1) {
			HandlingKeyRelease = false;
			this->sfmlCounter = 0;
		}
	}
}


void Game::handlePressEvent() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		(this->Hero.getSprite().getPosition().x < 1000-5))
		this->right = true;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (this->Hero.getSprite().getPosition().x > 5))
		this->left = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->up = true;
}



void Game::Render() {
	this->window.clear();
	this->window.draw(this->backGroundSprite);
	this->window.draw(this->Hero.getSprite());
	this->window.display();
}
