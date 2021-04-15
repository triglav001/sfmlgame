/*
 * ActionMessageWindow.h
 *
 *  Created on: Nov 16, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_ACTIONMESSAGEWINDOW_H_
#define MAP_ACTIONS_ACTIONMESSAGEWINDOW_H_

#include "ActionWindow.h"

#define TEXT_CONTINUE_COOLDOWN 0.5f

class ActionMessageWindow : public ActionWindow {

protected:
	bool is_ready = false;
	sf::Text message;
	sf::Time cooldown = sf::seconds(TEXT_CONTINUE_COOLDOWN);

public:
	ActionMessageWindow(std::string msg, bool showOpeningAnimation);
	virtual void reset();
	virtual void onOpenDraw();
	virtual bool onOpenUpdate(sf::Time delta);
	virtual void onOpenHandleInput(sf::Keyboard::Key key);
	virtual void onWindowOpen();

};

#endif /* MAP_ACTIONS_ACTIONMESSAGEWINDOW_H_ */
