/*
 * utils.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: Domen
 */

#include "../game.h"
#include "../data/GameData.h"
#include "Tileset.h"
#include "GameSpriteSet.h"
#include "../map/GameMap.h"

std::vector<sf::Texture> game_textures;
std::vector<sf::Texture> game_tilesets;
std::vector<Tileset*> game_maps;
std::vector<GameSpriteSet*> game_spritesets;
std::map<std::string, GameMap*> maps;
sf::Font game_font;

const char *texnames[] = {
		"zelv.png",
		"person.png",
		"IconSet.png",
		"slime.png"
};

void __init_game_spritesets();

void load_game_textures () {
	sf::Texture tex;
	printf("Loading textures ...\n");
	for (unsigned int i=0; i<SIZE(texnames); i++) {
		printf("%s\t...\t", texnames[i]);
		if (tex.loadFromFile(texnames[i]))
			printf("OK\n");
		else
			printf("FAIL\n");
		game_textures.push_back(tex);
	}
	__init_game_spritesets();
}

const char *tsetnames[] = {
		"tileset1.png"
};

void load_game_tilesets () {
	sf::Texture tex;
	printf("Loading tilesets ...\n");
	for (unsigned int i=0; i<SIZE(tsetnames); i++) {
		printf("%s\t...\t", tsetnames[i]);
		if (tex.loadFromFile(tsetnames[i]))
			printf("OK\n");
		else
			printf("FAIL\n");
		game_tilesets.push_back(tex);
	}
}

const char *mapnames[] = {
		"map001.map",
		"map002.map",
		"map003.map"
};

void load_game_maps () {
	Tileset* tset = new Tileset();
	printf("Loading tilesets ...\n");
	for (unsigned int i=0; i<SIZE(mapnames); i++) {
		printf("%s\t...\t", mapnames[i]);
		if (tset->loadFromFile(mapnames[i]))
			printf("OK\n");
		else
			printf("FAIL\n");
		game_maps.push_back(tset);
		tset = new Tileset();
	}
}

void load_game_font() {
	printf ("Loading game font ...\t");
	if (game_font.loadFromFile("terminus.ttf")) printf("OK\n");
	else printf("FAIL\n");
}

void init_game_maps();
void init_game_data();
void init_game_items();

void __game_init_all() {
	load_game_font();
	load_game_textures();
	load_game_tilesets();
	load_game_maps();
	init_game_maps();
	init_game_items();
	init_game_data();
}

void util_sf_vector2f_normalize(sf::Vector2f* vector) {
    float length = sqrt((double)((vector->x * vector->x) + (vector->y * vector->y)));
    if (length != 0)
        *vector = sf::Vector2f(vector->x / length, vector->y / length);
}

void __init_game_spritesets() {
	printf("Initalizing IconSet ...\n");
	GameSpriteSet* iconset = new GameSpriteSet(game_textures[TEXTURE_ID_ICONSET], 24, 24, SpriteSplitMode::SplitModeByCellSize);
	game_spritesets.push_back(iconset);
}


#include "../map_actions/ActionChangeMap.h"
#include "../map_actions/MapActionList.h"
#include "../map_actions/ActionMessageWindow.h"
#include "../map_actions/ActionSelectWindow.h"
#include "../map_actions/ActionMenuWindow.h"
#include "GameItemList.h"
#include "../gameplay/Inventory.h"
#include "GameBasicList.h"
#include "../map/MapObject.h"
#include "GameSprite.h"

GameSprite* create_sprite_with_pos (unsigned int texID, int x, int y) {
	GameSprite* spr = new GameSprite(texID);
	spr->getSprite()->setPosition(x, y);
	return spr;
}

void add_game_map(std::string name, GameMap* map) {
	maps.insert(std::pair<std::string, GameMap*>(name, map));
}

// GameMap(unsigned int mapID, std::vector<MapObject*> objs);
void init_game_maps() {

	GameBasicList* gbl = new GameBasicList();
	gbl->draw_icons = true;
	gbl->list_items.push_back({"CHOICE 1", 0, 1});
	gbl->list_items.push_back({"CHOICE 2", 0, 2});
	gbl->list_items.push_back({"CHOICE 3", 0, 3});
	gbl->list_items.push_back({"CHOICE 4", 0, 4});
	gbl->list_items.push_back({"CHOICE 5", 0, 5});
	gbl->list_items.push_back({"CHOICE 6", 0, 6});
	gbl->list_items.push_back({"CHOICE 7", 0, 7});
	gbl->list_items.push_back({"CHOICE 8", 0, 8});
	gbl->list_items.push_back({"CHOICE 9", 0, 9});

	MapObject* obj = new MapObject(create_sprite_with_pos(1, 200, 200), new MapActionList({
				new ActionMessageWindow("Tukaj pri zahodnem zidu se redko kaj zgodi.", true),
				new ActionMessageWindow("Če želiš početi kaj bolj zanimivega, obišči mesto.\nJe vzhodno od tukaj.", false),
				new ActionMessageWindow("Veliko sreče!", false),
				new ActionSelectWindow(gbl)
	}));
	MapObject* slm = new MapObject(create_sprite_with_pos(3, 50, 100), new MapActionList({
				new ActionMessageWindow("Zdi se mi, kot da obstajam samo za dekorativen namen", true),
				new ActionMessageWindow(".....", false)
	}));

	GameMap* map001 = new GameMap(0, {obj, slm});
	map001->setTouchRight(new ActionChangeMap("map003", 0, 5*32));
	map001->setTouchLeft(new ActionMessageWindow("Tam ni nič, zato ni poante iti tja.", true));
	maps.insert(std::pair<std::string, GameMap*>("begin_area", map001));


	GameMap* map002 = new GameMap(1, {});
	map002->setTouchLeft(new ActionChangeMap("map003", 19*32, 5*32));
	map002->setTouchDown(new ActionChangeMap("begin_area", 0, 0));
	MapActionList* test_msgs = new MapActionList({
		new ActionMessageWindow("This is a test message ...", true),
		new ActionMessageWindow("This is a next message made for testing ...", false)
	});

	map002->setTouchDown(test_msgs);
	maps.insert(std::pair<std::string, GameMap*>("map002", map002));

	GameMap* map003 = new GameMap(2, {});
	map003->setTouchLeft(new ActionChangeMap("begin_area", 16*32, 6*32));
	map003->setTouchDown(new ActionChangeMap("map002", 0, 0));
	add_game_map("map003", map003);
}

std::vector<GameItem> game_items;
GameData game_data;

void add_global_action(std::string name, MapAction* act) {
	game_data.global_actions.insert(std::pair<std::string, MapAction*>(name, act));
}

void init_game_data () {
	GameBasicList* esc_list = new GameBasicList();
	GameItemList* inv_show = new GameItemList(&game_data.player_inventory);
	esc_list->list_items.push_back({"Items", 0, 0, (MapAction*) new ActionMenuWindow(inv_show, 300, 300)});
	esc_list->list_items.push_back({"Status", 0, 0, (MapAction*) new ActionMessageWindow("Not yet implemented!", true)});
	esc_list->list_items.push_back({"Equip", 0, 0, (MapAction*) new ActionMessageWindow("Not yet implemented!", true)});
	esc_list->list_items.push_back({"Game End", 0, 0, (MapAction*) new ActionMessageWindow("Not yet implemented!", true)});
	ActionMenuWindow* esc_menu = new ActionMenuWindow(esc_list);
	add_global_action("open_game_menu", esc_menu);
}

/*
struct GameItem {
	std::string item_name;
	std::string item_desc;
	bool is_battle_item;
	BattleScope item_scope;
	BattleFormula formula;
};
*/

void init_game_items () {
	BattleFormula standard_formula;
	standard_formula.use_multipliers = false;
	standard_formula.damage_base = -300;
	game_items.push_back({"Nek napoj", "desc ...", 0, false, BattleScope::ScopeSkillUser, standard_formula});
	game_items.push_back({"Nek drug napoj", "desc ...", 6, false, BattleScope::ScopeSkillUser, standard_formula});
	game_items.push_back({"Rastlina", "desc ...", 9, false, BattleScope::ScopeSkillUser, standard_formula});
	game_data.player_inventory = Inventory();
	game_data.player_inventory.addItem(0, 4);
	game_data.player_inventory.addItem(1, 1);
	game_data.player_inventory.addItem(2, 63);
}
