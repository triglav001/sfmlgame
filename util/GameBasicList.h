/*
 * GameBasicList.h
 *
 *  Created on: Dec 10, 2020
 *      Author: Domen
 */

#ifndef UTIL_GAMEBASICLIST_H_
#define UTIL_GAMEBASICLIST_H_

#include "../game.h"

class GameBasicList : public GameDrawableBase {

protected:
	int __lastx = 0;
	int __lasty = 0;
	sf::Text drw_text;
	unsigned int line_h = 16;
	void calculateLineH();

public:
	//MapAction** set_act = NULL;
	std::function<void(unsigned int)> callback = nullptr;

	GameBasicList();

	unsigned int nshow = 4;
	unsigned int nfirst = 0;

	unsigned int spriteset_id = 0;
	int spacing = 8;
	int padding = 5;
	bool draw_icons = false;
	bool show_all = false;

	sf::FloatRect getItemRect(unsigned int item, unsigned int w);
	std::vector<BasicListItem> list_items;
	virtual void draw(int x, int y);
};

#endif /* UTIL_GAMEBASICLIST_H_ */
