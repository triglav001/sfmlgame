/*
 * Player.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#define DEF_PLAYER_SPEED 220

#include "Player.h"
#include "../util/GameSprite.h"
#include "../map/GameMap.h"
#include "../map/SceneMap.h"


Player::Player(GameSprite* sprite) {
	player_sprite = sprite;
	player_speed = DEF_PLAYER_SPEED;
}

Player::~Player() {
	delete player_sprite;
}

void Player::draw() {
	player_sprite->draw();
}

void Player::update(float delta) {
	player_sprite->update(delta);
}

void Player::setPosition(float x, float y) {
	pos_x = x;
	pos_y = y;
	player_sprite->getSprite()->setPosition(x, y);
}

float Player::getSpeed() {
	return player_speed;
}


void Player::move(sf::Vector2f direction, float delta) {
	//printf("Bigin MOVE\n");
	float _s = player_speed * delta;
	sf::Vector2f mov = direction * _s;
	sf::Vector2f prev = player_sprite->getSprite()->getPosition();
	setPosition(prev + mov);
	if (scene->getCurrentMap()->checkCollision())
		setPosition(prev);
	//printf("END move\n");
}

void Player::setPosition(sf::Vector2f pos) {
	pos_x = pos.x;
	pos_y = pos.y;
	player_sprite->getSprite()->setPosition(pos);
}

void Player::setSceneReference(SceneMap* ref) {
	scene = ref;
}

void Player::handleInput(sf::Keyboard::Key key) {
	if (IsInteractKey(key)) {
		scene->getCurrentMap()->onInteraction(PlayerObjectInteractMode::ActionButtonPressed);
	}
}

sf::Vector2f Player::getCenterPoint() {
	float x = player_sprite->getSprite()->getPosition().x + (player_sprite->getSprite()->getGlobalBounds().width / 2);
	float y = player_sprite->getSprite()->getPosition().y + (player_sprite->getSprite()->getGlobalBounds().height / 2);
	return sf::Vector2f(x, y);
}

void Player::setSpeed(float speed) {
	player_speed = speed;
}

sf::FloatRect Player::getPlayerRect() {
	return player_sprite->getSpriteRect();
}

sf::Vector2f Player::getPosition() {
	return sf::Vector2f(pos_x, pos_y);
}
