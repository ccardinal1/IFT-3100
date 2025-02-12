#pragma once
#include <ofMain.h>

struct Asset {
	ofImage image;
	glm::vec2 position;
};

class AssetManager {
public:
	void addImageAsset(const std::string& name, const std::string& path, glm::vec2 pos);
	void draw();
	void setPosition(const std::string& name, glm::vec2 newPos);
	std::map<std::string, Asset> assets;
};
