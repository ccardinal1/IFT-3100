#include "assetManager.h"

Asset* AssetManager::addImage(const std::string& name, const std::string& path, glm::vec2 pos)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::IMAGE;
	if (!asset.image.load(path))
	{
		ofLogError() << "Impossible de charger l'image: " << path;
		return nullptr;
	}
	asset.position2d = pos;

	return &asset;
}

Asset* AssetManager::addRectangle(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::RECTANGLE;
	asset.position2d = pos;
	asset.width = width;
	asset.height = height;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addCircle(const std::string& name, glm::vec2 pos, float radius, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::CIRCLE;
	asset.position2d = pos;
	asset.radius = radius;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addEllipse(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::ELLIPSE;
	asset.position2d = pos;
	asset.width = width;
	asset.height = height;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addLine(const std::string& name, glm::vec2 start, glm::vec2 end, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::LINE;
	asset.position2d = start;
	asset.endpoint = end;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addTriangle(const std::string& name, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::TRIANGLE;
	asset.position2d = p1;
	asset.p1 = p1;
	asset.p2 = p2;
	asset.p3 = p3;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addCube(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::CUBE;
	asset.position3d = pos;
	asset.width = size;
	asset.height = size;
	asset.lineWidth = lineWidth;
	asset.color = color;
	asset.isFilled = isFilled;

	ofBoxPrimitive cube = ofBoxPrimitive(size, size, size);

	cube.set(size);
	cube.setPosition(pos);

	cube.setSideColor(cube.SIDE_TOP, ofColor::yellow);
	cube.setSideColor(cube.SIDE_FRONT, ofColor::green);
	cube.setSideColor(cube.SIDE_LEFT, ofColor::red);
	cube.setSideColor(cube.SIDE_RIGHT, ofColor::blue);

	asset.geometryPrimitive = cube;

	return &asset;
}

Asset* AssetManager::addSphere(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::SPHERE;
	asset.position3d = pos;
	asset.width = size;
	asset.height = size;
	asset.lineWidth = lineWidth;
	asset.color = color;
	asset.isFilled = isFilled;

	ofSpherePrimitive sphere = ofSpherePrimitive(size, 10);

	sphere.setPosition(pos);

	asset.geometryPrimitive = sphere;

	return &asset;
}

void AssetManager::draw()
{
	for (auto& [name, asset] : assets)
	{
		if (asset.isFilled)
			ofFill();
		else
			ofNoFill();

		ofSetColor(asset.color);
		ofSetLineWidth(asset.lineWidth);

		switch (asset.type)
		{
		case AssetType::IMAGE:
			asset.image.draw(asset.position2d.x, asset.position2d.y);
			break;
		case AssetType::RECTANGLE:
			ofDrawRectangle(asset.position2d.x, asset.position2d.y, asset.width, asset.height);
			break;
		case AssetType::CIRCLE:
			ofSetCircleResolution(100);
			ofDrawCircle(asset.position2d.x, asset.position2d.y, asset.radius);
			break;
		case AssetType::ELLIPSE:
			ofDrawEllipse(asset.position2d, asset.width, asset.height);
			break;
		case AssetType::LINE:
			ofDrawLine(asset.position2d, asset.endpoint);
			break;
		case AssetType::TRIANGLE:
			ofDrawTriangle(asset.p1, asset.p2, asset.p3);
			break;
		case AssetType::CUBE:
		case AssetType::SPHERE:
			if (asset.isFilled)
			{
				asset.geometryPrimitive.drawFaces();
			}
			else
			{
				asset.geometryPrimitive.drawWireframe();
			}
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
				if (point.x >= asset.position2d.x && point.x <= asset.position2d.x + asset.image.getWidth() &&
					point.y >= asset.position2d.y && point.y <= asset.position2d.y + asset.image.getHeight())
				{
					return &asset;
				}
				break;
			}
			case AssetType::RECTANGLE:
			{
				if (point.x >= asset.position2d.x && point.x <= asset.position2d.x + asset.width &&
					point.y >= asset.position2d.y && point.y <= asset.position2d.y + asset.height)
				{
					return &asset;
				}
				break;
			}
			case AssetType::CIRCLE:
			{
				float dist = glm::distance(point, asset.position2d);
				if (dist <= asset.radius)
				{
					return &asset;
				}
				break;
			}
			case AssetType::ELLIPSE:
			{
				if (point.x >= asset.position2d.x && point.x <= asset.position2d.x + asset.width &&
					point.y >= asset.position2d.y && point.y <= asset.position2d.y + asset.height)
				{
					return &asset;
				}
				break;
			}
			case AssetType::LINE:
			{
				float d = glm::distance(point, glm::mix(asset.position2d, asset.endpoint, glm::clamp(glm::dot(point - asset.position2d, asset.endpoint - asset.position2d) / glm::dot(asset.endpoint - asset.position2d, asset.endpoint - asset.position2d), 0.0f, 1.0f)));
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
			case AssetType::CUBE:
			case AssetType::SPHERE:
			{
				ofVec3f point3d = ofVec3f(point.x, point.y, 0);

				ofVec3f boxPos = asset.geometryPrimitive.getPosition();

				ofVec3f halfSize(asset.width * 0.5f, asset.width * 0.5f, asset.width * 0.5f);

				ofVec3f minBound = boxPos - halfSize;
				ofVec3f maxBound = boxPos + halfSize;

				if (point3d.x >= minBound.x && point3d.x <= maxBound.x &&
					point3d.y >= minBound.y && point3d.y <= maxBound.y &&
					point3d.z >= minBound.z && point3d.z <= maxBound.z)
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

			asset->position2d = newPos;
			break;
		}
		case AssetType::LINE:
		{
			glm::vec2 delta = asset->position2d - asset->endpoint;

			asset->endpoint = newPos - delta;
			asset->position2d = newPos;

			break;
		}
		default:
		{
			asset->position2d = newPos;
			break;
		}
	}	
}

void AssetManager::setPosition(Asset* asset, glm::vec3 newPos)
{
	switch (asset->type)
	{
		case AssetType::CUBE:
		case AssetType::SPHERE:
		{
			asset->position3d = newPos;
			asset->geometryPrimitive.setPosition(newPos);
			break;
		}
		default:
		{
			setPosition(asset, { newPos.x, newPos.y });
			break;
		}
	}
}

void AssetManager::rotateX(Asset* asset, float deg)
{
	asset->geometryPrimitive.rotateDeg(deg, asset->geometryPrimitive.getXAxis());
}

void AssetManager::rotateY(Asset* asset, float deg)
{
	asset->geometryPrimitive.rotateDeg(deg, asset->geometryPrimitive.getYAxis());
}

void AssetManager::deleteAsset(string assetName)
{
	assets.erase(assetName);
}
