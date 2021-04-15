/*
 * SceneMap.h
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#ifndef MAP_SCENEMAP_H_
#define MAP_SCENEMAP_H_

#include "../game.h"

class MapAction;
class Player;
class GameMap;
class MapObject;
class Camera;

class SceneMap : public SceneBase {
protected:
	Player* player;
	GameMap* current_map = NULL;
	MapAction* current_action = NULL;
	MapObject* caller = NULL;
	Camera* scene_camera = NULL;

	std::map<sf::Keyboard::Key, SceneKeybinding> keybindings;

public:
	SceneMap();

	bool anyAction();
	void setMap(GameMap* map, int x = -1, int y = -1);

	void setAction(MapAction* act, MapObject* _caller = NULL);

	Player* getPlayer();

	// Get caller
	MapObject* getCaller();

	// Overrides
	virtual void drawScene();
	virtual void updateScene(float delta);
	virtual void handleSceneInput(sf::Keyboard::Key key);
	GameMap* getCurrentMap();
};

#endif /* MAP_SCENEMAP_H_ */
