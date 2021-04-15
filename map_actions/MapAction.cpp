/*
 * MapAction.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#include "MapAction.h"

void MapAction::draw() {}

bool MapAction::update(sf::Time delta) {
	return true;
}

bool MapAction::isDone() {
	return is_done;
}

void MapAction::reset() {
	is_done = false;
	internal_cnt = sf::Time::Zero;
}

void MapAction::setReferenceScene(SceneMap* _ref) {
	scene_ref = _ref;
}

void MapAction::handleInput(sf::Keyboard::Key key) {}

MapAction::~MapAction() {}

