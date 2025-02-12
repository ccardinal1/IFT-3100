#include "assetManager.h"

void AssetManager::addImageAsset(const std::string& name, const std::string& path, glm::vec2 pos)
{
    Asset asset;
    asset.image.load(path);
    asset.position = pos;
    assets[name] = asset;
}

void AssetManager::draw()
{
    for (auto& [name, asset] : assets)
    {
        if (name.rfind("imported_image", 0) == 0)
        {
            asset.image.draw(asset.position.x, asset.position.y);
        }
    }
}

void AssetManager::setPosition(const std::string& name, glm::vec2 newPos)
{
    if (assets.find(name) != assets.end())
    {
        assets[name].position = newPos;
    }
}
