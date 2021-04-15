/*
 * GameSpriteSet.h
 *
 *  Created on: Dec 9, 2020
 *      Author: Domen
 */

#ifndef UTIL_GAMESPRITESET_H_
#define UTIL_GAMESPRITESET_H_

#include "../game.h"

enum SpriteSplitMode {
	SplitModeByCellNumber,
	SplitModeByCellSize
};



class GameSpriteSet {

protected:
	sf::Sprite* __spriteset_sprites = NULL;
	void destroy();

public:
	GameSpriteSet(sf::Texture tex, unsigned int X, unsigned int Y, SpriteSplitMode mode = SpriteSplitMode::SplitModeByCellSize);
	void create(sf::Texture tex, unsigned int param1, unsigned int param2, SpriteSplitMode mode);

	sf::Sprite getSprite(unsigned int n);
	sf::Sprite getSpriteAndSetPosition(unsigned int n, int x, int y);
	bool isValid();

	~GameSpriteSet();

};

#endif /* UTIL_GAMESPRITESET_H_ */
