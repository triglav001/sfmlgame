/*
 * Camera.cpp
 *
 *  Created on: Nov 17, 2020
 *      Author: Domen
 */

#include "Camera.h"
#include "../map/SceneMap.h"
#include "../gameplay/Player.h"
#include "../map/GameMap.h"

Camera::Camera(SceneMap* ref, float w, float h) {
	scene_ref = ref;
	width = w;
	height = h;
	view.setSize(w, h);
}

sf::Vector2f Camera::getCamCenterPoint() {
	sf::Vector2f centerPoint = scene_ref->getPlayer()->getCenterPoint();
	float mapW = scene_ref->getCurrentMap()->getWidth();
	float mapH = scene_ref->getCurrentMap()->getHeight();

	if (mapW <= width)
		centerPoint.x = mapW / 2.0f;
	else {
		float lx = centerPoint.x - width / 2.0f;
		if (lx < 0.0f)
			centerPoint.x = width / 2.0f;
		if (lx + width > mapW)
			centerPoint.x = mapW - width / 2.0f;
	}
	if (mapH <= height)
		centerPoint.y = mapH / 2.0f;
	else {
		float ty = centerPoint.y - height / 2.0f;
		if (ty < 0.0f)
			centerPoint.y = height / 2.0f;
		if (ty + height > mapW)
			centerPoint.y = mapH - height / 2.0f;
	}
	return centerPoint;
}

void Camera::updateCamera() {
	view.setCenter(getCamCenterPoint());
	window.setView(view);
}

void Camera::setGUIMode(bool gui_mode) {
	if (gui_mode)
		window.setView(window.getDefaultView());
	else
		window.setView(view);
}
