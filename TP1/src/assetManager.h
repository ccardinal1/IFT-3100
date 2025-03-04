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
    glm::vec3 position;

    float width, height, radius, depth;
    int lineWidth;
    glm::vec3 endpoint;
    glm::vec3 p1, p2, p3;
    ofColor color;
    bool isFilled;
    bool isSelected;
};

class AssetManager {
public:
	Asset* addImage(const std::string& name, const std::string& path, glm::vec3 pos);
    Asset* addRectangle(const std::string& name, glm::vec3 pos, float width, float height, int lineWidth, ofColor color, bool isFilled);
    Asset* addCircle(const std::string& name, glm::vec3 pos, float radius, int lineWidth, ofColor color, bool isFilled);
    Asset* addEllipse(const std::string& name, glm::vec3 pos, float width, float height, int lineWidth, ofColor color, bool isFilled);
    Asset* addLine(const std::string& name, glm::vec3 start, glm::vec3 end, int lineWidth, ofColor color, bool isFilled);
    Asset* addTriangle(const std::string& name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int lineWidth, ofColor color, bool isFilled);

    Asset* addCube(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled);
    Asset* addSphere(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled);

	void draw();

    Asset* getAsset(glm::vec3 point);
	void setPosition(Asset* asset, glm::vec3 newPos);

    void rotateX(Asset* asset, float deg);
    void rotateY(Asset* asset, float deg);

    void deleteAsset(string assetName);

	std::map<std::string, Asset> assets;
    Asset boundingBox;
    bool drawBoundingBox = false;
};
