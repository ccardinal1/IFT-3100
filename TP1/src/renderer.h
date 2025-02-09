// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include <vector>

class Renderer
{
public:

	ofNode node;
	std::vector<ofImage> importedImages;

	void setup();
	void update();
	void draw();
};