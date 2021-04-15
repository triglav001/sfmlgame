/*
 * GameSprite.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#include "GameSprite.h"

void GameSprite::draw() {
	window.draw(sprite);
}

void GameSprite::update(float delta) {}

void GameSprite::handleInput(sf::Keyboard::Key key) {}

sf::Sprite* GameSprite::getSprite() {
	return &sprite;
}

GameSprite::GameSprite(unsigned int texID) {
	sprite.setTexture(game_textures[texID]);
}

sf::FloatRect GameSprite::getSpriteRect() {
	return sprite.getGlobalBounds();
}

GameSprite::~GameSprite() {}

