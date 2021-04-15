/*
 * Tileset.h
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#ifndef UTIL_TILESET_H_
#define UTIL_TILESET_H_

#include "../game.h"

class Tileset {

protected:
	unsigned short width;
	unsigned short height;
	unsigned int tileset_id;
	Tile** tiles;

public:
	bool loadFromFile (const char* filename);
	bool loadFromMemory (const void* memory);
	unsigned short getWidth ();
	unsigned short getHeight ();
	Tile getTile (unsigned int x, unsigned int y);
	void drawTileset (sf::RenderTarget& target);

	~Tileset();

};

#endif /* UTIL_TILESET_H_ */
