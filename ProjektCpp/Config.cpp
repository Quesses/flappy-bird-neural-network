#include "Config.h"

/*DISPLAY , GRAPHICS*/
unsigned Config::FPS = 60;
unsigned Config::option = 1;
const unsigned Config::windowHeight = 800;
const unsigned Config::windowWidth = 900;
ALLEGRO_FONT* Config::font30 = NULL;
ALLEGRO_BITMAP* Config::birdImage = NULL; //wczytane w mainie
ALLEGRO_BITMAP* Config::backgroundImage = NULL;
ALLEGRO_BITMAP* Config::groundImage = NULL;
ALLEGRO_BITMAP* Config::bottomObstacleImage = NULL;
ALLEGRO_BITMAP* Config::topObstacleImage = NULL;
ALLEGRO_SAMPLE* Config::dieSoundEffect = NULL;
ALLEGRO_SAMPLE* Config::hitSoundEffect = NULL;
ALLEGRO_SAMPLE* Config::pointSoundEffect = NULL;
ALLEGRO_SAMPLE* Config::swooshingSoundEffect = NULL;
ALLEGRO_SAMPLE* Config::wingSoundEffect = NULL;

/*INPUTS*/
bool Config::spacePressed = true;

/*DEFAULT GAME SETTINGS*/
const double Config::startingObstaclePositionX = 700.0;
const unsigned Config::defaultBirdStartingPositionX = 200;
const unsigned Config::defaultBirdStartingPositionY = 200;
const unsigned Config::spaceBetweenObstlaces = 350;
const int Config::obstacleWidth = 100;
const unsigned Config::obstacleCount = windowWidth / spaceBetweenObstlaces + 1;

unsigned Config::birdsNumber = 100;
double Config::crossoverRate = 0.03;
double Config::mutationRate = 0.003;

const unsigned Config::obstacleHoleSize = 150;
const double Config::birdVelocityX = 300.0 / 60;
const double Config::birdVelocityY = 0.0 / 60;
const double Config::maxBirdVelocityY = 20.0;
const double Config::gravityForce = 25.0 / 60; // przyspieszenie x pikseli na sekunde

