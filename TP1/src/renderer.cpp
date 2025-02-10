// Classe responsable du rendu de l'application.

#include "renderer.h"
#include <algorithm>

void Renderer::setup()
{
    importedImages.clear();
}

void Renderer::update()
{
}

void Renderer::draw()
{
    if (importedImages.size() > 0)
    {
        for (int i = 0; i < importedImages.size(); i++)
        {
            int spacing = 20;
            int columns = std::max<int>(1, ofGetWidth() / (importedImages[0].getWidth() + spacing));

            for (size_t i = 0; i < importedImages.size(); i++)
            {
                int x = (i % columns) * (importedImages[i].getWidth() + spacing);
                int y = (i / columns) * (importedImages[i].getHeight() + spacing);

                importedImages[i].draw(x, y);
            }
        }
    }
}