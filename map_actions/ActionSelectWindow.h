/*
 * ActionSelectWindow.h
 *
 *  Created on: Dec 10, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_ACTIONSELECTWINDOW_H_
#define MAP_ACTIONS_ACTIONSELECTWINDOW_H_

#include "ActionWindow.h"

class GameBasicList;

class ActionSelectWindow : public ActionWindow {

protected:
	bool refresh_needed = false;
	unsigned int selected = 0;
	//std::vector<sf::FloatRect> choices_rect;
	std::vector<GameDrawableBase*> window_drawables;
	GameBasicList* basic_list = NULL;

	void updateListPos();

public:
	ActionSelectWindow(GameBasicList* gbl, std::vector<GameDrawableBase*> drawables = {});
	ActionSelectWindow(GameBasicList* gbl, std::vector<GameDrawableBase*> drawables, float _x, float _y, unsigned int width, unsigned int height, bool showAnim);
	virtual void reset();
	virtual void onOpenDraw();
	virtual bool onOpenUpdate(sf::Time delta);
	virtual void onOpenHandleInput(sf::Keyboard::Key key);
	virtual void onWindowOpen();

};

#endif /* MAP_ACTIONS_ACTIONSELECTWINDOW_H_ */
