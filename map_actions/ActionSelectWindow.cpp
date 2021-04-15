/*
 * ActionSelectWindow.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: Domen
 */

#include "ActionSelectWindow.h"
#include "../util/GameBasicList.h"
#include "ActionWindow.h"

void ActionSelectWindow::reset() {
	ActionWindow::reset();
	selected = 0;
	basic_list->nfirst = 0;
	printf("RESET CALLED\n");
	//refresh_needed = true;
}

void ActionSelectWindow::onOpenDraw() {
	for (GameDrawableBase* gdb : window_drawables) {
		gdb->draw(x, y);
	}
	basic_list->draw(x - w / 2, y - h / 2);
	sf::FloatRect rct = basic_list->getItemRect(selected,
			w - basic_list->padding * 2);
	sf::RectangleShape shape;
	shape.setPosition(rct.left, rct.top);
	shape.setSize(sf::Vector2f(rct.width, rct.height));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f);
	shape.setFillColor(sf::Color::Transparent);
	window.draw(shape);
	return;
}

bool ActionSelectWindow::onOpenUpdate(sf::Time delta) {
	if (is_done)
		return true;
	if (refresh_needed) {
		for (GameDrawableBase* gdb : window_drawables) {
			gdb->refresh();
		}
		basic_list->refresh();
		refresh_needed = false;
	}
	for (GameDrawableBase* gdb : window_drawables) {
		gdb->update(delta);
	}
	basic_list->update(delta);
	return false;
}

void ActionSelectWindow::onOpenHandleInput(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Up) {
		selected = (selected + basic_list->list_items.size() - 1)
				% basic_list->list_items.size();
		updateListPos();
	} else if (key == sf::Keyboard::Down) {
		selected = (selected + 1) % basic_list->list_items.size();
		updateListPos();
	} else if (IsInteractKey(key)) {
		if (basic_list->callback) {
			basic_list->callback(selected);
			is_done = true;
			WindowResult = WindowActionResult::ActionOK;
			return;
		}
		if (basic_list->list_items[selected].on_select == NULL) {
			is_done = true;
			WindowResult = WindowActionResult::ActionOK;
		}
		child_action = basic_list->list_items[selected].on_select;
	} else if (key == sf::Keyboard::Escape) {
		is_done = true;
		WindowResult = WindowActionResult::ActionCanceled;
	}
}

ActionSelectWindow::ActionSelectWindow(GameBasicList* gbl,
		std::vector<GameDrawableBase*> drawables) :
		ActionWindow(CENTER_SCREEN_POINT.x, CENTER_SCREEN_POINT.y, 200, 200,
				true) {
	basic_list = gbl;
	window_drawables = drawables;
}

void ActionSelectWindow::updateListPos() {
	if (basic_list->nfirst + basic_list->nshow <= selected) {
		basic_list->nfirst = selected + 1 - basic_list->nshow;
	} else if (basic_list->nfirst > selected) {
		basic_list->nfirst = selected;
	}
}

void ActionSelectWindow::onWindowOpen() {
	for (GameDrawableBase* gdb : window_drawables) {
		gdb->refresh();
	}
	basic_list->refresh();
}

ActionSelectWindow::ActionSelectWindow(GameBasicList* gbl,
		std::vector<GameDrawableBase*> drawables, float _x, float _y,
		unsigned int width, unsigned int height, bool showAnim) :
		ActionWindow(_x, _y, width, height, showAnim) {
	basic_list = gbl;
	window_drawables = drawables;
}
