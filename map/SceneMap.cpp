/*
 * SceneMap.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#include "../game.h"
#include "SceneMap.h"
#include "GameMap.h"
#include "../util/GameSprite.h"
#include "../gameplay/Player.h"
#include "../map_actions/MapAction.h"
#include "MapObject.h"
#include "../util/Camera.h"
#include "../data/GameData.h"

SceneMap::SceneMap() {
	player = new Player(new GameSprite(0));
	player->setSceneReference(this);
	scene_camera = new Camera(this, (float)WINDOW_W, (float)WINDOW_H);
	keybindings.insert(std::make_pair<sf::Keyboard::Key, SceneKeybinding>(sf::Keyboard::Escape, {"open_game_menu", &game_data.menuEnabled}));
}

bool SceneMap::anyAction() {
	return (current_action != NULL);
}

void SceneMap::drawScene() {
	if (current_map != NULL)
		current_map->draw();
	player->draw();
	if (anyAction()) {
		scene_camera->setGUIMode(true);
		current_action->draw();
		scene_camera->setGUIMode(false);
	}
}

void SceneMap::updateScene(float delta) {
	//bool _act = anyAction();

	if (!anyAction()) {
		sf::Vector2f dir = ZERO_VECTOR_2F;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			dir += sf::Vector2f(-1,0);
			//player->move(GameDirection::DirectionLEFT, delta);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			dir += sf::Vector2f(1, 0);
			//player->move(GameDirection::DirectionRIGHT, delta);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			dir += sf::Vector2f(0,-1);
			//player->move(GameDirection::DirectionUP, delta);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			dir += sf::Vector2f(0, 1);
			//player->move(GameDirection::DirectionDOWN, delta);
		if (dir != ZERO_VECTOR_2F) {
			util_sf_vector2f_normalize(&dir);
			player->move(dir, delta);
			if (current_map != NULL)
				scene_camera->updateCamera();
		}
		player->update(delta);
		if (current_map != NULL)
			current_map->update(delta);
	}

	if (anyAction()) {
		if (current_action->update(sf::seconds(delta))) {
			current_action->reset();
			current_action = NULL;
		}
	}
}

void SceneMap::setMap(GameMap* map, int x, int y) {
	current_map = map;
	sf::Vector2f pos = player->getPosition();
	if (x != -1)
		pos.x = x;
	if (y != -1)
		pos.y = y;
	player->setPosition(pos);
	current_map->setReferenceScene(this);
	scene_camera->updateCamera();
}

void SceneMap::setAction(MapAction* act, MapObject* _caller) {
	if (current_action != NULL)
		return;
	if (act != NULL)
		act->setReferenceScene(this);
	current_action = act;
	caller = _caller;
}

Player* SceneMap::getPlayer() {
	return player;
}

GameMap* SceneMap::getCurrentMap() {
	return current_map;
}

void SceneMap::handleSceneInput(sf::Keyboard::Key key) {
	if (anyAction()) {
		current_action->handleInput(key);
		return;
	}

	if (keybindings.count(key) > 0 && (*keybindings[key].condition) == true
			&& game_data.global_actions.count(keybindings[key].act_name) > 0) {
		setAction(game_data.global_actions[keybindings[key].act_name]);
		return;
	}
	if (current_map != NULL)
		current_map->handleInput(key);
	if (player != NULL)
		player->handleInput(key);
}

MapObject* SceneMap::getCaller() {
	if (!anyAction())
		return NULL;
	return caller;
}
