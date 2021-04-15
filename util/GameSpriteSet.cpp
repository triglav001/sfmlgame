/*
 * GameSpriteSet.cpp
 *
 *  Created on: Dec 9, 2020
 *      Author: Domen
 */

#include "GameSpriteSet.h"

void GameSpriteSet::destroy() {
	delete[] __spriteset_sprites;
	__spriteset_sprites = NULL;
}

GameSpriteSet::GameSpriteSet(sf::Texture tex, unsigned int X, unsigned int Y,
		SpriteSplitMode mode) {
	create(tex, X, Y, mode);
}

void GameSpriteSet::create(sf::Texture tex, unsigned int param1,
		unsigned int param2, SpriteSplitMode mode) {

	int _im = param1;
	int _jm = param2;
	unsigned int w = param1;
	unsigned int h = param2;

	sf::Vector2u sz = tex.getSize();
	if (mode == SpriteSplitMode::SplitModeByCellSize) {
		_im = (sz.x / param1);
		_jm = (sz.y / param2);
	}
	if (mode == SpriteSplitMode::SplitModeByCellNumber) {
		w = (sz.x / param1);
		h = (sz.y / param2);
	}

	if (_im == 0 || _jm == 0 || w == 0 || h == 0)
		return;
	if (isValid())
		destroy();

	__spriteset_sprites = new sf::Sprite[_im * _jm];

	for (int j=0; j<_jm; j++) {
		for (int i=0; i<_im; i++) {
			__spriteset_sprites[j*_im + i].setTexture(tex);
			__spriteset_sprites[j*_im + i].setTextureRect(sf::IntRect(i*w, j*h, w, h));
			printf("spr(%i) -> {%i, %i}\n", j*_im + i, i*w, j*h);
		}
	}

	printf ("Created spriteset with %lu sprites! (w is %i, h is %i)\n", _im*_jm, w, h);

	return;
}

sf::Sprite GameSpriteSet::getSprite(unsigned int n) {
	return __spriteset_sprites[n];
}

sf::Sprite GameSpriteSet::getSpriteAndSetPosition(unsigned int n, int x,
		int y) {
	sf::Sprite clone = __spriteset_sprites[n];
	clone.setTexture(game_textures[2]);
	/*printf ("Drawing sprite %u {%i %i %i %i} at {%i %i}", n,
			clone.getTextureRect().left, clone.getTextureRect().top, clone.getTextureRect().width,
			clone.getTextureRect().height, x, y);*/
	clone.setPosition(x, y);
	return clone;
}

bool GameSpriteSet::isValid() {
	return (__spriteset_sprites != NULL);
}

GameSpriteSet::~GameSpriteSet() {
	destroy();
}
