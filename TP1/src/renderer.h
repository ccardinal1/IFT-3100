// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

	ofNode node;
	ofImage importedImage;

	void setup();
	void update();
	void draw();
};