/*
 * Camera.h
 *
 *  Created on: Nov 17, 2020
 *      Author: Domen
 */

#ifndef UTIL_CAMERA_H_
#define UTIL_CAMERA_H_

#include "../game.h"

class SceneMap;

class Camera {

protected:
	sf::View view;
	SceneMap* scene_ref;
	float width;
	float height;

public:
	Camera(SceneMap* ref, float w, float h);
	sf::Vector2f getCamCenterPoint();

	void updateCamera();
	void setGUIMode (bool gui_mode);

};

#endif /* UTIL_CAMERA_H_ */
