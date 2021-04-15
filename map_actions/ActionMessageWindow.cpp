/*
 * ActionMessageWindow.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: Domen
 */

#include "ActionMessageWindow.h"

ActionMessageWindow::ActionMessageWindow(std::string msg, bool showOpeningAnimation)
	: ActionWindow(SCREEN_CENTER_X, 350, 444, 100, showOpeningAnimation) {
	message.setFont(game_font);
	message.setFillColor(sf::Color::White);
	message.setCharacterSize(16);
	message.setString(sf::String::fromUtf8(msg.begin(), msg.end()));

	/*if (!showOpeningAnimation)
		open();*/
}

void ActionMessageWindow::reset() {
	ActionWindow::reset();
	if (show_animaton)
		window_shape.setSize(sf::Vector2f(0,0));
	is_ready = false;
}

void ActionMessageWindow::onOpenDraw() {
	window.draw(message);
}

bool ActionMessageWindow::onOpenUpdate(sf::Time delta) {
	internal_cnt += delta;
	if (internal_cnt >= cooldown) {
		internal_cnt = sf::Time::Zero;
		is_ready = true;
	}
	return is_done;
}

void ActionMessageWindow::onOpenHandleInput(sf::Keyboard::Key key) {
	if (is_ready && IsInteractKey(key)) {
		is_done = true;
	}
}

void ActionMessageWindow::onWindowOpen() {
	message.setPosition(endX + 5, endY + 5);
}
