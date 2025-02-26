#pragma once
#include <ofMain.h>

enum class AssetType {
    IMAGE,
    RECTANGLE,
    CIRCLE,
    ELLIPSE,
    LINE,
    TRIANGLE,
    CUBE,
    SPHERE
};

struct Asset {
    AssetType type;
    string name;
    ofImage image;
    of3dPrimitive geometryPrimitive;
    glm::vec2 position2d;
    glm::vec3 position3d;

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
	Asset* addImage(const std::string& name, const std::string& path, glm::vec2 pos);
    Asset* addRectangle(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled);
    Asset* addCircle(const std::string& name, glm::vec2 pos, float radius, int lineWidth, ofColor color, bool isFilled);
    Asset* addEllipse(const std::string& name, glm::vec2 pos, float width, float height, int lineWidth, ofColor color, bool isFilled);
    Asset* addLine(const std::string& name, glm::vec2 start, glm::vec2 end, int lineWidth, ofColor color, bool isFilled);
    Asset* addTriangle(const std::string& name, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int lineWidth, ofColor color, bool isFilled);

    Asset* addCube(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled);
    Asset* addSphere(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled);

	void draw();

    Asset* getAsset(glm::vec2 point);
	void setPosition(Asset* asset, glm::vec2 newPos);
    void setPosition(Asset* asset, glm::vec3 newPos);

    void rotateX(Asset* asset, float deg);
    void rotateY(Asset* asset, float deg);

    void deleteAsset(string assetName);

	std::map<std::string, Asset> assets;
};
