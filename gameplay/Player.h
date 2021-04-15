/*
 * Player.h
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#ifndef GAMEPLAY_PLAYER_H_
#define GAMEPLAY_PLAYER_H_

#include "../game.h"

class SceneMap;
class GameSprite;

class Player {
protected:
	SceneMap* scene = NULL;
	GameSprite* player_sprite;

	// Coords
	float pos_x = 0;
	float pos_y = 0;

	float player_speed = 0;

public:

	Player(GameSprite* sprite);
	virtual ~Player();

	virtual void draw();
	virtual void update(float delta);
	virtual void handleInput(sf::Keyboard::Key key);
	void move(sf::Vector2f direction, float delta);

	void setSceneReference(SceneMap* ref);
	sf::FloatRect getPlayerRect();

	// get/set
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f pos);
	float getSpeed();
	sf::Vector2f getPosition();
	sf::Vector2f getCenterPoint();
	void setSpeed(float speed);
};

#endif /* GAMEPLAY_PLAYER_H_ */
