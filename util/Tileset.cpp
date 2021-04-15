/*
 * Tileset.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#include "Tileset.h"


bool tileset_to_sprite (unsigned int tileset_id, unsigned short tile_id, sf::Sprite* _out) {
	// error check
	if (tileset_id >= game_tilesets.size()) return false;
	//printf ("1");
	sf::Vector2u tex_size = game_tilesets[tileset_id].getSize();
	//printf ("Calc %i %i...\n", (tex_size.x), tex_size.y);
	//printf ("2");
	if ((tex_size.x % 32) != 0 || (tex_size.y % 32) != 0) return false;
	//printf ("3\n");
	if (((tex_size.x/32) * (tex_size.y/32)) <= (unsigned int) tile_id) return false;

	//printf("4\n");

	// calc
	unsigned int x = tile_id % (tex_size.x / 32);

	//printf("5\n");

	unsigned int y = tile_id / (tex_size.x / 32);

	//printf("6\n");

	_out->setTexture (game_tilesets[tileset_id]);

	//printf("7\n");

	_out->setTextureRect (sf::IntRect (x*32, y*32, 32, 32));

	//printf("8\n");

	return true;

}


bool Tileset::loadFromFile (const char* filename) {
	FILE* fp = fopen (filename, "rb");
	if (fp == NULL) return false;
	printf ("Opened file: %s\n", filename);
	fseek (fp, 0, SEEK_END);
	size_t fsize = ftell (fp);
	rewind (fp);

	printf ("Got filesize: %u\n", (unsigned int)fsize);

	void* memory = (void*) malloc (fsize);
	if (memory == NULL) {
		fclose (fp);
		return false;
	}
	if (fread (memory, 1, fsize, fp) < fsize) {
		free ((void*) memory);
		fclose (fp);
		return false;
	}
	fclose (fp);

	printf ("Calling this->loadFromMemory ...\n");
	bool result = loadFromMemory (memory);
	printf ("Done!\n");
	free ((void*) memory);
	return result;
}

bool Tileset::loadFromMemory (const void* memory) {
	TilemapHeader* header = (TilemapHeader*) memory;
	if (header->identifier != (sf::Uint32)'PAMT') return false;// Invalid FOURCC
	width = header->width;
	height = header->height;
	tileset_id = 0;//header->tileset_id;
	tiles = (Tile**) malloc (width * sizeof (Tile*));

	printf("Got tilemap with size (%i, %i)\n", width, height);

	if (tiles == NULL) return false;
	unsigned char* data_ptr = (unsigned char*)memory + sizeof (TilemapHeader);
	unsigned int row_size = (height * sizeof (Tile));
	for (int i=0; i<width; i++) {
		tiles[i] = (Tile*) malloc (row_size);
		memcpy (tiles[i], data_ptr, row_size);
		data_ptr += row_size;
	}
	return true;
}


Tile Tileset::getTile (unsigned int x, unsigned int y) {
	if (x < width || y < height) {
		return tiles[x][y];
	}
	Tile t;
	return t;
}

// Free allocated memory
Tileset::~Tileset () {
	for (int i=0; i<height; i++) {
		if (tiles[i] != NULL) free ((void*) tiles[i]);
	}
	free ((void*) tiles);
}

/*
		unsigned short getWidth ();
		unsigned short getHeight ();
*/
unsigned short Tileset::getWidth () { return width; }
unsigned short Tileset::getHeight () { return height; }

void Tileset::drawTileset (sf::RenderTarget& target) {
	sf::Sprite spr;
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			//printf ("DRAWING TILE %i %i ...\n", i, j);
			//printf ("Tile: %i %i: %hu\n", i, j, tiles[i][j].texture_id);
			spr.setPosition (i*32, j*32);
			if (tileset_to_sprite (tileset_id, tiles[i][j].texture_id, &spr)) target.draw (spr);
		}
	}
	return;
}
