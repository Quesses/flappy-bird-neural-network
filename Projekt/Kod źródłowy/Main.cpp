
#include<allegro5\allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include<windows.h>
#include <vector>
#include "Config.h"
#include "Game.h"
int main()
{
	srand(time(NULL));
	bool theGame = true;
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);
	int num = 0;
	while (num < 10 || num > 100) {
		cout << "Wprowadz wielkosc polulacji [10 - 100] :" << endl;
		cin >> num;
		if (num < 10 || num > 100)cout << "Nie poprawna liczba!" << endl;
	}
	Config::setBirdsNumber(num);
	

	ALLEGRO_DISPLAY* display;

	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_reserve_samples(5);
	ALLEGRO_BITMAP* birdImage = al_load_bitmap("bird.png");
	ALLEGRO_BITMAP* backgroundImage = al_load_bitmap("background.png");
	ALLEGRO_BITMAP* groundImage = al_load_bitmap("ground.png");
	ALLEGRO_BITMAP* bottomObstacleImage = al_load_bitmap("bottomobstacle.png");
	ALLEGRO_BITMAP* topObstacleImage = al_load_bitmap("topobstacle.png");
	ALLEGRO_SAMPLE* dieSoundEffect = al_load_sample("sfx_die.wav");
	ALLEGRO_SAMPLE* hitSoundEffect = al_load_sample("sfx_hit.wav");
	ALLEGRO_SAMPLE* pointSoundEffect = al_load_sample("sfx_point.wav");
	ALLEGRO_SAMPLE* swooshingSoundEffect = al_load_sample("sfx_swooshing.wav");
	ALLEGRO_SAMPLE* wingSoundEffect = al_load_sample("sfx_wing.wav");
	ALLEGRO_FONT* font30 = al_load_font("arial.ttf", 30, 0);

	//set config*********************
	if (font30 == NULL)cout << 0;
	Config::setFont30(font30);
	Config::setBgImage(backgroundImage);
	Config::setGroundImage(groundImage);
	Config::setBirdImage(birdImage);
	Config::setBottomObstacleImage(bottomObstacleImage);
	Config::setTopObstacleImage(topObstacleImage);
	Config::setDieSoundEffect(dieSoundEffect);
	Config::setHitSoundEffect(hitSoundEffect);
	Config::setPointSoundEffect(pointSoundEffect);
	Config::setSwooshingSoundEffect(swooshingSoundEffect);
	Config::setWingSoundEffect(wingSoundEffect);

	//*******************************

	display = al_create_display(Config::getWinWidth(), Config::getWinHeight());

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Kolejka zdarzeñ
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / Config::getFPS()); //Zegarek
	al_install_keyboard();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_STATE keyState;
	
	Game g;
	
	
	
	ShowWindow(hWnd, SW_HIDE);
	
	while (theGame) {
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			exit(0);

		al_get_keyboard_state(&keyState);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
				if (Config::getOption() > 1)Config::setOption(Config::getOption() - 1);
				else Config::setOption(3);
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
				if (Config::getOption() < 3)Config::setOption(Config::getOption() + 1);
				else Config::setOption(1);
			}
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
			switch (Config::getOption()) {
			case 1:
				Config::decreaseCrossoverRate();
				break;
			case 2:
				Config::decreaseMutationRate();
				break;
			case 3:
				Config::decreaseFPS();
				al_set_timer_speed(timer, 1.0 / Config::getFPS());
				break;
			}
			
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
			switch (Config::getOption()) {
			case 1:
				Config::enlargeCrossoverRate();
				break;
			case 2:
				Config::enlargeMutationRate();
				break;
			case 3:
				Config::enlargeFPS();
				al_set_timer_speed(timer, 1.0 / Config::getFPS());
				break;
			}

		}
		


		if (event.type == ALLEGRO_EVENT_TIMER) {

			g.tick();
			g.render();
			al_flip_display();
		}
	}



	return 0;
}