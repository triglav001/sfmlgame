/*
 * GameSprite.h
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#ifndef UTIL_GAMESPRITE_H_
#define UTIL_GAMESPRITE_H_

#include "../game.h"

class GameSprite {

protected:
	sf::Sprite sprite;

public:

	virtual void draw();
	virtual void update(float delta);
	virtual void handleInput(sf::Keyboard::Key key);

	sf::Sprite* getSprite();
	sf::FloatRect getSpriteRect();

	GameSprite(unsigned int texID);
	virtual ~GameSprite();
};

#endif /* UTIL_GAMESPRITE_H_ */
