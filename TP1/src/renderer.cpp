// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
}

void Renderer::update()
{
}

void Renderer::draw()
{
    if (importedImage.isAllocated())
    {
        int x = (ofGetWidth() - importedImage.getWidth()) / 2;
        int y = (ofGetHeight() - importedImage.getHeight()) / 2;

        importedImage.draw(x, y);
    }
}