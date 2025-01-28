// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

	ofNode node;

	void setup();
	void update();
	void draw();
};