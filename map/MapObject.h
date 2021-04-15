/*
 * MapObject.h
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#ifndef MAP_MAPOBJECT_H_
#define MAP_MAPOBJECT_H_

#include "../game.h"


class GameSprite;
class Player;
class SceneMap;
class MapAction;

class MapObject {

protected:
	//MapActionList* on_interact;
	MapAction* onActionButtonPressed;
	MapAction* onPlayerTouch;
	MapAction* onTouchPlayer;

	GameSprite* sprite;
	SceneMap* scene_ref = NULL;

	bool local_variables[4];

public:
	MapObject(GameSprite* _sprite, MapAction* _onAction = NULL, MapAction* _onPlayer = NULL, MapAction* _onTouch = NULL);
	virtual ~MapObject();

	void setReferenceScene(SceneMap* ref);

	virtual void draw();
	virtual void update(float delta);
	virtual void handleInput(sf::Keyboard::Key key);
	virtual void onInteract(PlayerObjectInteractMode mode);

	bool* getLocalVariable(char c);

	sf::FloatRect getRect();

};

#endif /* MAP_MAPOBJECT_H_ */
