#pragma once
#include <ofMain.h>

enum class AssetType {
    IMAGE,
    RECTANGLE,
    CIRCLE,
    ELLIPSE,
    LINE,
    TRIANGLE
};

struct Asset {
    AssetType type;
    ofImage image;
    glm::vec2 position;

    float width, height, radius;
    int lineWidth;
    glm::vec2 endpoint;
    glm::vec2 p1, p2, p3;
    ofColor color;
    bool isFilled;
    bool isSelected;
};

class AssetManager {
public:
	void addImage(const std::string& name, const std::string& path, glm::vec2 pos);
    void addRectangle(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled);
    void addCircle(const std::string& name, glm::vec2 pos, float radius, int lineWidth, ofColor color, bool isFilled);
    void addEllipse(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled);
    void addLine(const std::string& name, glm::vec2 start, glm::vec2 end, int lineWidth, ofColor color, bool isFilled);
    void addTriangle(const std::string& name, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int lineWidth, ofColor color, bool isFilled);

	void draw();

    Asset* getAsset(glm::vec2 point);
	void setPosition(Asset* asset, glm::vec2 newPos);

	std::map<std::string, Asset> assets;
};
