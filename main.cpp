/*
 * main.cpp
 *
 *  Created on: Nov 10, 2020
 *      Author: Domen
 */
#include "game.h"
#include "map/SceneMap.h"
#include "map/GameMap.h"

sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "__game");
SceneBase* current_scene = NULL;

int main () {

	__game_init_all();

	SceneMap* mapscene = new SceneMap();
	mapscene->setMap(maps["begin_area"]);
	current_scene = mapscene;

	// Max 60 FPS
	window.setFramerateLimit(60);


	sf::Event event;
	sf::Clock clock;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				continue;
			}
			if (event.type == sf::Event::KeyPressed) {
				current_scene->handleSceneInput(event.key.code);
				continue;
			}
		}

		current_scene->updateScene(clock.restart().asSeconds());
		window.clear();
		current_scene->drawScene();
		window.display();

	}


	return 0;
}

