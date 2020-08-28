#ifndef Game_h
#define Game_h
#include <SFML/Graphics.hpp>
#include "mario.h"
#include "Level.h"
#include <vector>
#include "Block.h"
class Game {
private:
	int startAtLevelTexture;//new
	int currentLevel;//new
	std::vector<Level> levels;
	enum Released{RIGHT , LEFT};
	Mario Hero;
	double gravityInteraction;
	sf::RenderWindow window;
	bool right, left, up , rightR , leftR;
	sf::Clock testClock;
	sf::Time testTime;
	sf::Sprite backGroundSprite;
	double sfmlCounter;
	NormalBlock* NrightBlock , NleftBlock;
	ComplexBlock* CrightBlock, CleftBlock;
private:
	void CheckChangingCurrentBlocks();
	void CheckLevelCompelet();
	void Render();
	void handlePressEvent();
	void handelReleaseEvent(sf::Event);
	void makeHeroMove(sf::Clock& afterReleaseClock, sf::Clock& hero_Animation_Clock,
		sf::Time& timePerFrame, sf::Time& hero_Animation_Time, sf::Time& afterReleaseTime,
		bool& HandlingKeyRelease, bool& rightRelesed, bool& leftReleased, bool& rightLastFrame, 
		bool& inJump, bool& maxPointIsEncuntered,int& textureNumber , double& currentJumpVelocity
	, double& prevPositionCheck);// Made to improve the game logic
	void moveHero(sf::Time  , bool ,
		bool , bool , bool, double);
private:
	class ErrorWhenCallingFunction {};
public:
	Game();
	void Run();
};
#endif