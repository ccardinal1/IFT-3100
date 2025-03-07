#include "assetManager.h"

Asset* AssetManager::addImage(const std::string& name, const std::string& path, glm::vec3 pos)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::IMAGE;

	if (!asset.image.load(path))
	{
		ofLogError() << "Impossible de charger l'image: " << path;
		return nullptr;
	}

	asset.position = pos;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.width = asset.image.getWidth();
	asset.height = asset.image.getHeight();
	asset.depth = 0;

	return &asset;
}

Asset* AssetManager::addRectangle(const std::string& name, glm::vec3 pos, float width, float height, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::RECTANGLE;
	asset.position = pos;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.width = width;
	asset.height = height;
	asset.depth = 0;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addCircle(const std::string& name, glm::vec3 pos, float radius, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::CIRCLE;
	asset.position = pos;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.radius = radius;
	asset.width = radius * 2;
	asset.height = radius * 2;
	asset.depth = 0;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addEllipse(const std::string& name, glm::vec3 pos, float width, float height, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::ELLIPSE;
	asset.position = pos;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.width = width;
	asset.height = height;
	asset.depth = 0;
	asset.color = color;
	asset.lineWidth = lineWidth;
	asset.isFilled = isFilled;

	return &asset;
}

Asset* AssetManager::addLine(const std::string& name, glm::vec3 start, glm::vec3 end, int lineWidth, ofColor color)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::LINE;
	asset.position = start;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.endpoint = end;
	asset.width = asset.endpoint.x - asset.position.x;
	asset.height = asset.endpoint.y - asset.position.y;
	asset.depth = asset.endpoint.z - asset.position.z;
	asset.color = color;
	asset.lineWidth = lineWidth;

	return &asset;
}

Asset* AssetManager::addTriangle(const std::string& name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::TRIANGLE;
	asset.position = p1;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.p1 = p1;
	asset.p2 = p2;
	asset.p3 = p3;
	asset.width = p2.x - p3.x;
	asset.height = p1.y - p2.y;
	asset.depth = 0;
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
	asset.position = pos;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.width = size;
	asset.height = size;
	asset.depth = size;
	asset.lineWidth = lineWidth;
	asset.color = color;
	asset.isFilled = isFilled;

	ofBoxPrimitive cube = ofBoxPrimitive(size, size, size);

	cube.set(size);
	cube.setPosition(pos);

	asset.geometryPrimitive = cube;

	return &asset;
}

Asset* AssetManager::addSphere(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::SPHERE;
	asset.position = pos;
	asset.rotation = glm::vec3(0, 0, 0);
	asset.scale = glm::vec3(1, 1, 1);
	asset.width = size;
	asset.height = size;
	asset.depth = size;
	asset.lineWidth = lineWidth;
	asset.color = color;
	asset.isFilled = isFilled;

	ofSpherePrimitive sphere = ofSpherePrimitive(size, 10);

	sphere.setPosition(pos);

	asset.geometryPrimitive = sphere;

	return &asset;
}

Asset* AssetManager::add3dModel(const std::string& name, glm::vec3 pos, string path)
{
	Asset& asset = assets[name];
	asset.name = name;
	asset.type = AssetType::MODEL;
	asset.position = pos;
	asset.rotation = glm::vec3(180, 0, 0);
	asset.model.setRotation(0, 180, 1, 0, 0);
	asset.model.setRotation(1, 0, 0, 1, 0);
	asset.model.setRotation(2, 0, 0, 0, 1);
	asset.scale = glm::vec3(1, 1, 1);
	asset.model.loadModel(path);
	asset.model.enableMaterials();

	asset.model.setPosition(pos.x, pos.y, pos.z);

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
			asset.image.draw(asset.position.x, asset.position.y, asset.position.z);
			break;
		case AssetType::RECTANGLE:
			ofDrawRectangle(asset.position.x, asset.position.y, asset.position.z, asset.width, asset.height);
			break;
		case AssetType::CIRCLE:
			ofSetCircleResolution(100);
			ofDrawCircle(asset.position.x, asset.position.y, asset.position.z, asset.radius);
			break;
		case AssetType::ELLIPSE:
			ofDrawEllipse(asset.position, asset.width, asset.height);
			break;
		case AssetType::LINE:
			ofDrawLine(asset.position, asset.endpoint);
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
		case AssetType::MODEL:
			asset.model.setPosition(asset.position.x, asset.position.y, asset.position.z);
			asset.model.drawFaces();
		}
	}

	if (drawBoundingBox)
	{
		ofNoFill();
		ofSetColor(boundingBox.color);
		ofSetLineWidth(boundingBox.lineWidth);
		ofDrawBox(boundingBox.position.x, boundingBox.position.y, boundingBox.position.z, boundingBox.width, boundingBox.height, boundingBox.depth);
	}
}

Asset* AssetManager::getAsset(glm::vec3 point)
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
			case AssetType::CUBE:
			case AssetType::SPHERE:
			{
				ofVec3f point3d = point;

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

void AssetManager::setPosition(Asset* asset, glm::vec3 newPos)
{
	switch (asset->type)
	{
		case AssetType::TRIANGLE:
		{
			int width = std::max(asset->p2.x, asset->p3.x) - std::min(asset->p2.x, asset->p3.x);
			int height = std::max(asset->p1.y, asset->p2.y) - std::min(asset->p1.y, asset->p2.y);
			int depth = 0;

			asset->p1 = newPos;
			asset->p2 = { newPos.x - width * 0.5f, newPos.y + height, depth };
			asset->p3 = { newPos.x + width * 0.5f, newPos.y + height, depth };

			asset->position = newPos;
			break;
		}
		case AssetType::LINE:
		{
			glm::vec3 delta = asset->position - asset->endpoint;

			asset->endpoint = newPos - delta;
			asset->position = newPos;

			break;
		}
		case AssetType::CUBE:
		case AssetType::SPHERE:
		{
			asset->position = newPos;
			asset->geometryPrimitive.setPosition(newPos);
			break;
		}
		default:
		{
			asset->position = newPos;
			break;
		}
	}	
}

void AssetManager::setRotation(Asset* asset, glm::vec3 newRot) {
	switch (asset->type) {
	case AssetType::MODEL:
		if (newRot.x != asset->rotation.x) {
			asset->model.setRotation(0, newRot.x, 1, 0, 0);
			asset->rotation.x = newRot.x;
		}
		if (newRot.y != asset->rotation.y) {
			asset->model.setRotation(1, newRot.y, 0, 1, 0);
			asset->rotation.y = newRot.y;
		}
		if (newRot.z != asset->rotation.z) {
			asset->model.setRotation(2, newRot.z, 0, 0, 1);
			asset->rotation.z = newRot.z;
		}
		break;
	case AssetType::CUBE:
	case AssetType::SPHERE:
		asset->geometryPrimitive.setOrientation(newRot);
		asset->rotation = newRot;
		break;
	}
}

void AssetManager::setScale(Asset* asset, glm::vec3 newSca) {
	//TODO
}

void AssetManager::rotateX(Asset* asset, float deg)
{
	asset->geometryPrimitive.rotateDeg(deg, asset->geometryPrimitive.getXAxis());
}

void AssetManager::rotateY(Asset* asset, float deg)
{
	asset->geometryPrimitive.rotateDeg(deg, asset->geometryPrimitive.getYAxis());
}

void AssetManager::rotateZ(Asset* asset, float deg) {
	asset->geometryPrimitive.rotateDeg(deg, asset->geometryPrimitive.getZAxis());
}

void AssetManager::deleteAsset(string assetName)
{
	assets.erase(assetName);
}
