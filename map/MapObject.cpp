/*
 * MapObject.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#include "MapObject.h"
#include "../util/GameSprite.h"
#include "SceneMap.h"
#include "../map_actions/MapActionList.h"


MapObject::~MapObject() {
	delete sprite;
	if (onActionButtonPressed != NULL)
		delete onActionButtonPressed;
	if (onPlayerTouch != NULL)
		delete onPlayerTouch;
	if (onTouchPlayer != NULL)
		delete onTouchPlayer;
}

void MapObject::setReferenceScene(SceneMap* ref) {
	scene_ref = ref;
}

void MapObject::draw() {
	sprite->draw();
}

void MapObject::update(float delta) {
	sprite->update(delta);
}

void MapObject::handleInput(sf::Keyboard::Key key) {}

void MapObject::onInteract(PlayerObjectInteractMode mode) {
	printf ("ON_INTERACT: %p\n", scene_ref);
	if (mode == PlayerObjectInteractMode::ActionButtonPressed && onActionButtonPressed != NULL)
		scene_ref->setAction(onActionButtonPressed);
	if (mode == PlayerObjectInteractMode::ObjectTouchPlayer && onTouchPlayer != NULL)
		scene_ref->setAction(onTouchPlayer);
	if (mode == PlayerObjectInteractMode::PlayerTouchObject && onPlayerTouch != NULL)
		scene_ref->setAction(onPlayerTouch);
	//scene_ref->setAction((MapAction*)on_interact);
}

MapObject::MapObject(GameSprite* _sprite, MapAction* _onAction, MapAction* _onPlayer, MapAction* _onTouch) {
	sprite = _sprite;
	onActionButtonPressed = _onAction;
	onPlayerTouch = _onPlayer;
	onTouchPlayer = _onTouch;
}

sf::FloatRect MapObject::getRect() {
	return sprite->getSpriteRect();
}

bool* MapObject::getLocalVariable(char c) {
	return &local_variables[c-'A'];
}
