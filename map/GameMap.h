/*
 * GameMap.h
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#ifndef MAP_GAMEMAP_H_
#define MAP_GAMEMAP_H_

#include "../game.h"

class Tileset;
class MapObject;
class MapAction;
class SceneMap;

class GameMap {
protected:
	Tileset* tileset;
	std::vector<MapObject*> map_objects;
	sf::RenderTexture tileset_as_texture;
	sf::Sprite tilemap_sprite;
	SceneMap* ref = NULL;

public:

	MapAction* touchLeft = NULL;
	MapAction* touchRight = NULL;
	MapAction* touchUp = NULL;
	MapAction* touchDown = NULL;


	int getWidth();
	int getHeight();

	bool checkCollision();
	void onInteraction (PlayerObjectInteractMode mode);
	bool getTileFromPoint(int x, int y, int* tileCoordX, int* tileCoordY, bool drCorner = false);

	void setReferenceScene(SceneMap* _ref);

	virtual void draw();
	virtual void update(float delta);
	virtual void handleInput(sf::Keyboard::Key key);

	GameMap(unsigned int mapID, std::vector<MapObject*> objs);
	virtual ~GameMap();
	void setTouchDown(MapAction* touchDown);
	void setTouchLeft(MapAction* touchLeft);
	void setTouchRight(MapAction* touchRight);
	void setTouchUp(MapAction* touchUp);
};

#endif /* MAP_GAMEMAP_H_ */
