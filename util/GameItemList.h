/*
 * ItemList.h
 *
 *  Created on: Dec 2, 2020
 *      Author: Domen
 */

#ifndef UTIL_GAMEITEMLIST_H_
#define UTIL_GAMEITEMLIST_H_


#include "GameBasicList.h"

class Inventory;

// for inventory display
class GameItemList : public GameBasicList {

protected:
	Inventory* inventory;

public:
	GameItemList(Inventory* inv);
	virtual void refresh();

};

#endif /* UTIL_GAMEITEMLIST_H_ */
