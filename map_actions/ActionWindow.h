/*
 * ActionWindow.h
 *
 *  Created on: Nov 15, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_ACTIONWINDOW_H_
#define MAP_ACTIONS_ACTIONWINDOW_H_

#include "MapAction.h"

#define WINDOW_OPEN_TIME 0.3f


class ActionWindow : public MapAction {

protected:
	MapAction* child_action = NULL;
	WindowActionResult WindowResult = WindowActionResult::ActionOK;

	sf::Time needed;
	sf::RectangleShape window_shape;
	float x;
	float y;
	float _curX = 0;
	float _curY = 0;
	unsigned int _curW = 0;
	unsigned int _curH = 0;
	unsigned int w;
	unsigned int h;

	int endX = 0;
	int endY = 0;

	// Is window open
	bool is_open = false;
	bool show_animaton = true;
	bool draw_on_children = false;

	void calcCurrentArea();
	virtual bool updateChild (sf::Time delta);

public:
	ActionWindow(float _x, float _y, unsigned int width, unsigned int height, bool showAnim);
	virtual bool update(sf::Time delta);
	virtual void draw();
	virtual void handleInput(sf::Keyboard::Key key);
	virtual void reset();
	virtual void onWindowOpen();

	virtual bool onOpenUpdate(sf::Time delta);
	virtual void onOpenDraw();
	virtual void onOpenHandleInput(sf::Keyboard::Key key);

	WindowActionResult getWindowResult();

	bool open();

	bool isOpen();

};

#endif /* MAP_ACTIONS_ACTIONWINDOW_H_ */
