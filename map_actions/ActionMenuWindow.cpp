/*
 * ActionMenuWindow.cpp
 *
 *  Created on: Dec 29, 2020
 *      Author: Domen
 */

#include "ActionMenuWindow.h"

/*
bool ActionWindow::updateChild(sf::Time delta) {
	bool result = child_action->update(delta);
	if (result) {
		child_action->reset();
		child_action = NULL;
		return true;
	}
	return false;
}

 * */

bool ActionMenuWindow::updateChild(sf::Time delta) {
	bool result = child_action->update(delta);
	if (result) {
		WindowActionResult winResult = ((ActionWindow*) child_action)->getWindowResult();
		child_action->reset();
		child_action = NULL;
		if (winResult == WindowActionResult::ActionCloseParentWindow) {
			WindowResult = WindowActionResult::ActionOK;
			return true;
		}
		if (winResult == WindowActionResult::ActionOK)
			refresh_needed = true;
		return false;
	}
	return false;
}

ActionMenuWindow::ActionMenuWindow(GameBasicList* gbl,
		std::vector<GameDrawableBase*> drawables) : ActionSelectWindow(gbl, drawables) {
	draw_on_children = true;
}

ActionMenuWindow::ActionMenuWindow(GameBasicList* gbl, unsigned int w,
		unsigned int h, std::vector<GameDrawableBase*> drawables)
		: ActionSelectWindow(gbl, drawables, CENTER_SCREEN_POINT.x, CENTER_SCREEN_POINT.y, w, h, true) {
	draw_on_children = true;
}
