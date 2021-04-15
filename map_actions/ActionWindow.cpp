/*
 * ActionWindow.cpp
 *
 *  Created on: Nov 15, 2020
 *      Author: Domen
 */

#include "ActionWindow.h"

ActionWindow::ActionWindow(float _x, float _y, unsigned int width,
		unsigned int height, bool showAnim) {
	x = _x;
	y = _y;
	w = width;
	h = height;
	show_animaton = showAnim;
	needed = sf::seconds(WINDOW_OPEN_TIME);
	window_shape.setFillColor(sf::Color::Black);
	window_shape.setOutlineColor(sf::Color::White);
	window_shape.setOutlineThickness(1.0f);
}

bool ActionWindow::update(sf::Time delta) {

	if (child_action != NULL) {
		updateChild(delta);
	}

	if (is_open) {
		is_done = onOpenUpdate(delta);
		return is_done;
	}

	internal_cnt += delta;
	if (!show_animaton || internal_cnt >= needed) {
		internal_cnt = needed;
		is_open = true;
		calcCurrentArea();
		internal_cnt = sf::Time::Zero;
		endX = _curX;
		endY = _curY;
		onWindowOpen();
		return false;
	}
	calcCurrentArea();

	return false;
}


void ActionWindow::calcCurrentArea() {
	double part = internal_cnt / needed;
	_curW = part * w;
	_curH = part * h;

	// Recalc point
	_curX = x - (_curW / 2);
	_curY = y - (_curH / 2);

	window_shape.setPosition(_curX, _curY);
	window_shape.setSize(sf::Vector2f(_curW, _curH));
}

void ActionWindow::draw() {
	if (child_action != NULL && !draw_on_children) {
		child_action->draw();
		return;
	}
	window.draw(window_shape);
	if (is_open)
		onOpenDraw();
	if (child_action != NULL)
		child_action->draw();
}

void ActionWindow::handleInput(sf::Keyboard::Key key) {
	if (child_action != NULL) {
		child_action->handleInput(key);
		return;
	}
	if (is_open)
		onOpenHandleInput(key);
}

bool ActionWindow::onOpenUpdate(sf::Time delta) {
	return false;
}
void ActionWindow::onOpenDraw() {}
void ActionWindow::onOpenHandleInput(sf::Keyboard::Key key) {}


void ActionWindow::reset() {
	MapAction::reset();
	is_open = false;
	if (show_animaton) {
		internal_cnt = sf::Time::Zero;
		window_shape.setSize(sf::Vector2f(0,0));
	}
	if (child_action != NULL) {
		child_action->reset();
		child_action = NULL;
	}
}

bool ActionWindow::isOpen() {
	return is_open;
}

bool ActionWindow::open() {
	if (is_open)
		return false;
	internal_cnt = needed;
	calcCurrentArea();
	internal_cnt = sf::Time::Zero;
	is_open = true;
	endX = _curX;
	endY = _curY;
	onWindowOpen();
	return true;
}

void ActionWindow::onWindowOpen() {
}

bool ActionWindow::updateChild(sf::Time delta) {
	bool result = child_action->update(delta);
	if (result) {
		child_action->reset();
		child_action = NULL;
		return true;
	}
	return false;
}

WindowActionResult ActionWindow::getWindowResult() {
	return WindowResult;
}
