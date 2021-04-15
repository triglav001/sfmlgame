/*
 * GameBasicList.cpp
 *
 *  Created on: Dec 10, 2020
 *      Author: Domen
 */

#include "GameBasicList.h"
#include "GameSpriteSet.h"

GameBasicList::GameBasicList() {
	drw_text.setFont(game_font);
	drw_text.setCharacterSize(16);
	drw_text.setFillColor(sf::Color::White);
}

sf::FloatRect GameBasicList::getItemRect(unsigned int item, unsigned int w) {
	calculateLineH();
	unsigned int pls = 0;
	if (!draw_icons)
		pls = 4;
	return sf::FloatRect(__lastx + padding, __lasty + (line_h * (item - nfirst)) + spacing + pls, w, line_h - spacing);
}

void GameBasicList::calculateLineH() {
	if (draw_icons)
		line_h = 24;
	else
		line_h = 16;
	line_h += spacing;
}

void GameBasicList::draw(int x, int y) {
	__lastx = x;
	__lasty = y;
	int xx = x + padding;
	int yy = y + spacing;

	calculateLineH();

	if (show_all) {
		nfirst = 0;
		nshow = list_items.size();
	}

	if (list_items.empty())
		return;

	unsigned int ntmp = nshow;
	if (nshow > list_items.size())
		nshow = list_items.size();

	for (int i=nfirst; i<nfirst+nshow; i++) {
		//printf("SPRITESET ID: %i\n", list_items[i].spriteset_id);
		if (draw_icons)
			window.draw(game_spritesets[list_items[i].spriteset_id]->getSpriteAndSetPosition(list_items[i].sprite_id, xx, yy));
		drw_text.setPosition(xx + 24 + 4, yy + 4);
		drw_text.setString(list_items[i].item_name);
		window.draw(drw_text);
		yy += line_h;
	}
	nshow = ntmp;
}

