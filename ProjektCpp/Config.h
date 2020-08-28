#pragma once
#include<allegro5\allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class Config
{
private:
	/*DISPLAY , GRAPHICS, SOUND EFFECTS*/
	static ALLEGRO_FONT* font30;
	static ALLEGRO_BITMAP* birdImage;
	static ALLEGRO_BITMAP* backgroundImage;
	static ALLEGRO_BITMAP* groundImage;
	static ALLEGRO_BITMAP* bottomObstacleImage;
	static ALLEGRO_BITMAP* topObstacleImage;
	static ALLEGRO_SAMPLE* dieSoundEffect;
	static ALLEGRO_SAMPLE* hitSoundEffect;
	static ALLEGRO_SAMPLE* pointSoundEffect;
	static ALLEGRO_SAMPLE* swooshingSoundEffect;
	static ALLEGRO_SAMPLE* wingSoundEffect;
	const static unsigned windowHeight, windowWidth;
	static unsigned FPS;
	static unsigned option;
	static double crossoverRate;
	static double mutationRate;

	/*INPUTS*/
	static bool spacePressed;

	/*GAME SETTINGS*/
	const static double startingObstaclePositionX;
	const static unsigned defaultBirdStartingPositionX;
	const static unsigned defaultBirdStartingPositionY;
	const static unsigned spaceBetweenObstlaces;
	static unsigned birdsNumber;
	const static unsigned obstacleHoleSize;
	const static int obstacleWidth;
	const static unsigned obstacleCount;
	const static double birdVelocityX;
	const static double birdVelocityY;
	const static double maxBirdVelocityY;
	const static double gravityForce;

public:
	/*GETTERS & SETTERS*/
	const static double getStartingObstaclePositionX() { return startingObstaclePositionX; }
	const static unsigned getDefaultBirdStartingPositionX() { return defaultBirdStartingPositionX; }
	const static unsigned getDefaultBirdStartingPositionY() { return defaultBirdStartingPositionY; }
	const static unsigned getObstacleCount() { return obstacleCount; }
	const static double getBirdVelocityX() { return birdVelocityX; }
	const static double getBirdVelocityY() { return birdVelocityY; }
	const static double getMaxBirdVelocityY() { return maxBirdVelocityY; }
	const static double getGravityForce() { return gravityForce; }
	const static unsigned getObstacleHoleSize() { return obstacleHoleSize; }
	const static int getObstacleWidth() { return obstacleWidth; }
	const static unsigned getSpaceBetweenObstacles() { return spaceBetweenObstlaces; }
	const static unsigned getBirdsNumber() { return birdsNumber; }
	static bool isSpacePressed() { return spacePressed; }
	static void setSpacePressed(bool val) { spacePressed = val; }
	const static unsigned getWinWidth() { return windowWidth; }
	const static unsigned getWinHeight() { return windowHeight; }
	static ALLEGRO_BITMAP* getBirdImage() { return birdImage; }
	static ALLEGRO_BITMAP* getBgImage() { return backgroundImage; }
	static ALLEGRO_BITMAP* getGroundImage() { return groundImage; }
	static ALLEGRO_BITMAP* getBottomObstacleImage() { return bottomObstacleImage; }
	static ALLEGRO_BITMAP* getTopObstacleImage() { return topObstacleImage; }
	static void setBirdImage(ALLEGRO_BITMAP* im) { birdImage = im; }
	static void setBgImage(ALLEGRO_BITMAP* im) { backgroundImage = im; }
	static void setGroundImage(ALLEGRO_BITMAP* im) { groundImage = im; }
	static void setBottomObstacleImage(ALLEGRO_BITMAP* im) { bottomObstacleImage = im; }
	static void setTopObstacleImage(ALLEGRO_BITMAP* im) { topObstacleImage = im; }
	static ALLEGRO_SAMPLE* getDieSoundEffect() { return dieSoundEffect; }
	static ALLEGRO_SAMPLE* getHitSoundEffec() { return hitSoundEffect; }
	static ALLEGRO_SAMPLE* getPointSoundEffect() { return pointSoundEffect; }
	static ALLEGRO_SAMPLE* getSwooshingSoundEffect() { return swooshingSoundEffect; }
	static ALLEGRO_SAMPLE* getWingSoundEffect() { return wingSoundEffect; }
	static ALLEGRO_FONT* getFont30() { return font30; }
	static void setFont30(ALLEGRO_FONT* val) { font30 = val; }
	static void setDieSoundEffect(ALLEGRO_SAMPLE* val) { dieSoundEffect = val; }
	static void setHitSoundEffect(ALLEGRO_SAMPLE* val) { hitSoundEffect = val; }
	static void setPointSoundEffect(ALLEGRO_SAMPLE* val) { pointSoundEffect = val; }
	static void setSwooshingSoundEffect(ALLEGRO_SAMPLE* val) { swooshingSoundEffect = val; }
	static void setWingSoundEffect(ALLEGRO_SAMPLE* val) { wingSoundEffect = val; }

	static double getCrossoverRate() { return crossoverRate; }
	static void enlargeCrossoverRate() { if(crossoverRate < 0.5) crossoverRate +=0.002; }
	static void decreaseCrossoverRate() { if (crossoverRate > 0.01) crossoverRate -= 0.002; }
	
	static double getMutationRate() { return mutationRate; }
	static void enlargeMutationRate() { if (mutationRate < 0.09) mutationRate += 0.0002; }
	static void decreaseMutationRate() { if (mutationRate > 0.001) mutationRate -= 0.0002; }


	
	static unsigned getFPS() { return FPS; }
	static void enlargeFPS() { if(FPS < 600)FPS++; }
	static void decreaseFPS() { if(FPS > 5)FPS--; }
	static void setBirdsNumber(int num) { birdsNumber = num; }
	static unsigned getOption() { return option; }
	static void setOption(int num) { option = num; }
};

