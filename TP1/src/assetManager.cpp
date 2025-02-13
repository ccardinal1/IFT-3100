#include "assetManager.h"

void AssetManager::addImage(const std::string& name, const std::string& path, glm::vec2 pos)
{
    Asset asset;
    asset.type = AssetType::IMAGE;
    if (!asset.image.load(path))
    {
        ofLogError() << "Impossible de charger l'image: " << path;
        return;
    }
    asset.position = pos;
    assets[name] = asset;
}

void AssetManager::addRectangle(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled)
{
    Asset asset;
    asset.type = AssetType::RECTANGLE;
    asset.position = pos;
    asset.width = width;
    asset.height = height;
    asset.color = color;
    asset.lineWidth = lineWidth;
    asset.isFilled = isFilled;
    assets[name] = asset;
}

void AssetManager::addCircle(const std::string& name, glm::vec2 pos, float radius, int lineWidth, ofColor color, bool isFilled)
{
    Asset asset;
    asset.type = AssetType::CIRCLE;
    asset.position = pos;
    asset.radius = radius;
    asset.color = color;
    asset.lineWidth = lineWidth;
    asset.isFilled = isFilled;
    assets[name] = asset;
}

void AssetManager::addEllipse(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled)
{
    Asset asset;
    asset.type = AssetType::ELLIPSE;
    asset.position = pos;
    asset.width = width;
    asset.height = height;
    asset.color = color;
    asset.lineWidth = lineWidth;
    asset.isFilled = isFilled;
    assets[name] = asset;
}

void AssetManager::addLine(const std::string& name, glm::vec2 start, glm::vec2 end, int lineWidth, ofColor color, bool isFilled)
{
    Asset asset;
    asset.type = AssetType::LINE;
    asset.position = start;
    asset.endpoint = end;
    asset.color = color;
    asset.lineWidth = lineWidth;
    asset.isFilled = isFilled;
    assets[name] = asset;
}

void AssetManager::addTriangle(const std::string& name, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int lineWidth, ofColor color, bool isFilled)
{
    Asset asset;
    asset.type = AssetType::TRIANGLE;
    asset.position = p1;
    asset.p1 = p1;
    asset.p2 = p2;
    asset.p3 = p3;
    asset.color = color;
    asset.lineWidth = lineWidth;
    asset.isFilled = isFilled;
    assets[name] = asset;
}

void AssetManager:: draw() 
{
    for (auto& [name, asset] : assets)
    {
        if (asset.isFilled)
            ofFill();
        else
            ofNoFill();

        switch (asset.type)
        {
            case AssetType::IMAGE:
                asset.image.draw(asset.position.x, asset.position.y);
                break;
            case AssetType::RECTANGLE:
                ofSetColor(asset.color);
                ofSetLineWidth(asset.lineWidth);
                ofDrawRectangle(asset.position.x, asset.position.y, asset.width, asset.height);
                break;
            case AssetType::CIRCLE:
                ofSetColor(asset.color);
                ofSetLineWidth(asset.lineWidth);
                ofSetCircleResolution(100);
                ofDrawCircle(asset.position.x, asset.position.y, asset.radius);
                break;
            case AssetType::ELLIPSE:
                ofSetColor(asset.color);
                ofSetLineWidth(asset.lineWidth);
                ofDrawEllipse(asset.position, asset.width, asset.height);
                break;
            case AssetType::LINE:
                ofSetColor(asset.color);
                ofSetLineWidth(asset.lineWidth);
                ofDrawLine(asset.position, asset.endpoint);
                break;
            case AssetType::TRIANGLE:
                ofSetColor(asset.color);
                ofSetLineWidth(asset.lineWidth);
                ofDrawTriangle(asset.p1, asset.p2, asset.p3);
                break;
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