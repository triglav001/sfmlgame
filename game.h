/*
 * game.h
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#ifndef GAME_H_
#define GAME_H_

#include "gamedef.h"
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define IsInteractKey(key) (key == sf::Keyboard::Space)

class SceneBase {
public:
	virtual void drawScene() = 0;
	virtual void updateScene(float delta) = 0;
	virtual void handleSceneInput(sf::Keyboard::Key key) = 0;
	virtual ~SceneBase() {}
};

class GameDrawableBase {
public:
	virtual void draw(int x, int y) = 0;
	virtual void update(sf::Time delta) {}
	virtual void refresh() {}
	virtual ~GameDrawableBase() {}
};

/*
 *
 	DirectionUP 	= sf::Vector2f(0,-1),
	DirectionDOWN 	= sf::Vector2f(0, 1),
	DirectionLEFT 	= sf::Vector2f(-1,1),
	DirectionRIGHT 	= sf::Vector2f(1, 0)
 * */
enum GameDirection {
	DirectionUP,
	DirectionDOWN,
	DirectionLEFT,
	DirectionRIGHT
};

enum PlayerObjectInteractMode {
	ActionButtonPressed,
	PlayerTouchObject,
	ObjectTouchPlayer
};

enum WindowActionResult {
	ActionCanceled,
	ActionOK,
	ActionCloseParentWindow
};

struct TilemapHeader {
	sf::Uint32 identifier;
	sf::Uint16 width;
	sf::Uint16 height;
	sf::Uint32 tileset_id;
};

struct Tile {
	sf::Uint16 texture_id;
	sf::Uint8 passable;
	sf::Uint8 terrain_tag;
};

class MapAction;
struct BasicListItem {
	std::string item_name;
	unsigned int spriteset_id;
	unsigned int sprite_id;
	MapAction* on_select;
};


struct GameFileData {
	unsigned int currentMapID;
	int playerPosX;
	int playerPOsY;

	bool gameBooleans[4096];
	int gameIntegers[1024];
};

struct SceneKeybinding {
	std::string act_name;
	bool* condition;
};

enum BattleScope {
	ScopeOneEnemy,
	ScopeAllEnemies,
	ScopeOneRandomEnemy,
	ScopeSkillUser,
	ScopeOneAlly,
	ScopeAllAllies
};

#include "battle/BattleFormula.h"

struct GameItem {
	std::string item_name;
	std::string item_desc;
	unsigned int item_tex;
	bool is_battle_item;
	BattleScope item_scope;
	BattleFormula formula;
};

// things
// TODO SceneBattle

// FIXME Collision detection doesnt subtract overlap
// FIXME When teleported, colision does not affect player for one frame?

// TODO Scene keybindings


const sf::Vector2f CENTER_SCREEN_POINT = sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2);
const float SCREEN_CENTER_X = WINDOW_W / 2.0f;
const float SCREEN_CENTER_Y = WINDOW_H / 2.0f;

const sf::Vector2f ZERO_VECTOR_2F = sf::Vector2f(0,0);

class Tileset;
class GameMap;
class GameSpriteSet;

extern sf::RenderWindow window;
extern SceneBase* current_scene;
extern std::vector<sf::Texture> game_textures;
extern std::vector<sf::Texture> game_tilesets;
extern std::vector<Tileset*> game_maps;
extern std::vector<GameSpriteSet*> game_spritesets;
extern std::map<std::string, GameMap*> maps;
extern std::vector<GameItem> game_items;

extern sf::Font game_font;

void util_sf_vector2f_normalize(sf::Vector2f* vector);
void __game_init_all();

#endif /* GAME_H_ */
