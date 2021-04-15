/*
 * ActionMenuWindow.h
 *
 *  Created on: Dec 29, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_ACTIONMENUWINDOW_H_
#define MAP_ACTIONS_ACTIONMENUWINDOW_H_

#include "ActionSelectWindow.h"

class ActionMenuWindow : public ActionSelectWindow {

protected:
	bool updateChild(sf::Time delta);

public:
	ActionMenuWindow(GameBasicList* gbl, std::vector<GameDrawableBase*> drawables = {});
	ActionMenuWindow(GameBasicList* gbl, unsigned int w, unsigned int h, std::vector<GameDrawableBase*> drawables = {});

};

#endif /* MAP_ACTIONS_ACTIONMENUWINDOW_H_ */
