/*
 * GameMap.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#include "GameMap.h"
#include "../util/Tileset.h"
#include "MapObject.h"
#include "SceneMap.h"
#include "../gameplay/Player.h"

void GameMap::draw() {
	window.draw(tilemap_sprite);
	for (MapObject* obj : map_objects) {
		obj->draw();
	}
}

void GameMap::update(float delta) {
	for (MapObject* obj : map_objects) {
		obj->update(delta);
	}
}

void GameMap::handleInput(sf::Keyboard::Key key) {
	for (MapObject* obj : map_objects) {
		obj->handleInput(key);
	}
}

GameMap::GameMap(unsigned int mapID, std::vector<MapObject*> objs) {
	tileset = game_maps[mapID];
	map_objects = objs;

	printf("Creating ...\n");
	if (!tileset_as_texture.create(tileset->getWidth() * 32, tileset->getHeight() * 32))
		printf("Creating failed!\n");
	printf("Drawing...\n");
	tileset_as_texture.clear();
	tileset->drawTileset(tileset_as_texture);
	printf("Drawing done!\n");
	tileset_as_texture.display();
	//tileset_as_texture.getTexture().copyToImage().saveToFile("tset.png");
	tilemap_sprite.setTexture(tileset_as_texture.getTexture());
	tilemap_sprite.setPosition(0,0);
}

int GameMap::getWidth() {
	return tileset->getWidth() * 32;
}

int GameMap::getHeight() {
	return tileset->getHeight() * 32;
}


bool GameMap::getTileFromPoint(int x, int y, int* tileCoordX, int* tileCoordY, bool drCorner) {
	if (x < 0 || y < 0 || x > getWidth() || y > getHeight())
		return false;
	*tileCoordX = x / 32;
	*tileCoordY = y / 32;
	if (drCorner && (x%32 == 0))
		*tileCoordX = (x/32)-1;
	if (drCorner && (y%32 == 0))
		*tileCoordY = (y/32)-1;
	return true;
}

// Return true if collision
bool GameMap::checkCollision() {
	sf::FloatRect p_rect = ((SceneMap*) current_scene)->getPlayer()->getPlayerRect();

	// Check map parts
	float X1 = p_rect.left, X2 = p_rect.left + p_rect.width, Y1 = p_rect.top, Y2 = p_rect.top + p_rect.height;
	X2 = getWidth() - X2;
	Y2 = getHeight() - Y2;

	// left
	if (X1 < 0 && X1 < Y1) {
		if (touchLeft != NULL)
		((SceneMap*) current_scene)->setAction(touchLeft);
		return true;
	}
	// up
	if (Y1 < 0 && Y1 < X1) {
		if (touchUp != NULL)
		((SceneMap*) current_scene)->setAction(touchUp);
		return true;
	}
	// right
	if (X2 < 0 && X2 < Y2) {
		if (touchRight != NULL)
			((SceneMap*) current_scene)->setAction(touchRight);
		return true;
	}
	// down
	if (Y2 < 0 && Y2 < X2) {
		if (touchDown != NULL)
			((SceneMap*) current_scene)->setAction(touchDown);
		return true;
	}

	X2 = getWidth() - X2;
	Y2 = getHeight() - Y2;

	int startX, startY, endX, endY;
	// Get tiles to check
	getTileFromPoint(X1, Y1, &startX, &startY);
	getTileFromPoint(X2, Y2, &endX, &endY, true);

	for (int i=startX; i<=endX; i++) {
		for (int j=startY; j<=endY; j++) {
			if (!tileset->getTile(i, j).passable)
				return true;
		}
	}
	return false;
}

void GameMap::setTouchDown(MapAction* touchDown) {
	this->touchDown = touchDown;
}

void GameMap::setTouchLeft(MapAction* touchLeft) {
	this->touchLeft = touchLeft;
}

void GameMap::setTouchRight(MapAction* touchRight) {
	this->touchRight = touchRight;
}

void GameMap::setTouchUp(MapAction* touchUp) {
	this->touchUp = touchUp;
}

GameMap::~GameMap() {}

void GameMap::onInteraction(PlayerObjectInteractMode mode) {
	//printf("on interact\n");
	SceneMap* ref = ((SceneMap*) current_scene);
	for (MapObject* obj : map_objects) {
		// Check for collision
		//printf("checking for collision with obj %p ...\n", obj);
		if (ref->getPlayer()->getPlayerRect().intersects(obj->getRect())) {
			obj->onInteract(mode);
			return;
		}
	}
	return;
}

void GameMap::setReferenceScene(SceneMap* _ref) {
	ref = _ref;
	for (MapObject* obj : map_objects) {
		obj->setReferenceScene(_ref);
	}
}
