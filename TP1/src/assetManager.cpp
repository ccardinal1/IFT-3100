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

void AssetManager::draw()
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

Asset* AssetManager::getAsset(glm::vec2 point)
{
	for (auto& [name, asset] : assets)
	{
		switch (asset.type)
		{
			case AssetType::IMAGE:
			{
				if (point.x >= asset.position.x && point.x <= asset.position.x + asset.image.getWidth() &&
					point.y >= asset.position.y && point.y <= asset.position.y + asset.image.getHeight())
				{
					return &asset;
				}
				break;
			}
			case AssetType::RECTANGLE:
			{
				if (point.x >= asset.position.x && point.x <= asset.position.x + asset.width &&
					point.y >= asset.position.y && point.y <= asset.position.y + asset.height)
				{
					return &asset;
				}
				break;
			}
			case AssetType::CIRCLE:
			{
				float dist = glm::distance(point, asset.position);
				if (dist <= asset.radius)
				{
					return &asset;
				}
				break;
			}
			case AssetType::ELLIPSE:
			{
				if (point.x >= asset.position.x && point.x <= asset.position.x + asset.width &&
					point.y >= asset.position.y && point.y <= asset.position.y + asset.height)
				{
					return &asset;
				}
				break;
			}
			case AssetType::LINE:
			{
				float d = glm::distance(point, glm::mix(asset.position, asset.endpoint, glm::clamp(glm::dot(point - asset.position, asset.endpoint - asset.position) / glm::dot(asset.endpoint - asset.position, asset.endpoint - asset.position), 0.0f, 1.0f)));
				if (d < 5.0f)
				{
					return &asset;
				}
				break;				
			}
			case AssetType::TRIANGLE:
			{
				if (point.x >= std::min(asset.p2.x, asset.p3.x) && point.x <= std::max(asset.p2.x, asset.p3.x) &&
					point.y >= asset.p1.y && point.y <= asset.p2.y)
				{
					return &asset;
				}
				break;
			}
		}
	}

	return NULL;
}

void AssetManager::setPosition(Asset* asset, glm::vec2 newPos)
{
	switch (asset->type)
	{
		case AssetType::TRIANGLE:
		{
			int width = std::max(asset->p2.x, asset->p3.x) - std::min(asset->p2.x, asset->p3.x);
			int height = std::max(asset->p1.y, asset->p2.y) - std::min(asset->p1.y, asset->p2.y);

			asset->p1 = newPos;
			asset->p2 = { newPos.x - width / 2, newPos.y + height };
			asset->p3 = { newPos.x + width / 2, newPos.y + height };

			asset->position = newPos;
			break;
		}
		case AssetType::LINE:
		{
			glm::vec2 delta = asset->position - asset->endpoint;

			asset->endpoint = newPos - delta;
			asset->position = newPos;

			break;
		}
		default:
		{
			asset->position = newPos;
			break;
		}
	}	
}