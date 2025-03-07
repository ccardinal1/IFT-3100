#pragma once
#include <ofMain.h>
#include "ofxAssimpModelLoader.h"

enum class AssetType {
    IMAGE,
    RECTANGLE,
    CIRCLE,
    ELLIPSE,
    LINE,
    TRIANGLE,
    CUBE,
    SPHERE,
    MODEL,
    INSTANCE
};

struct Asset {
    AssetType type;
    string name;
    ofImage image;
    of3dPrimitive geometryPrimitive;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    ofxAssimpModelLoader model;
    std::map<int, Asset*> instances;
    Asset* parent;

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
    Asset* addLine(const std::string& name, glm::vec3 start, glm::vec3 end, int lineWidth, ofColor color);
    Asset* addTriangle(const std::string& name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int lineWidth, ofColor color, bool isFilled);

    Asset* addCube(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled);
    Asset* addSphere(const std::string& name, glm::vec3 pos, float size, int lineWidth, ofColor color, bool isFilled);

    Asset* add3dModel(const std::string& name, glm::vec3 pos, string path);

    Asset* addInstance(Asset& original);

	void draw();

    Asset* getAsset(glm::vec3 point);
	void setPosition(Asset* asset, glm::vec3 newPos);
    void setRotation(Asset* asset, glm::vec3 newRot);
    void setScale(Asset* asset, glm::vec3 newSca);

    void rotateX(Asset* asset, float deg);
    void rotateY(Asset* asset, float deg);
    void rotateZ(Asset* asset, float deg);

    void deleteAsset(string assetName);

	std::map<std::string, Asset> assets;
    Asset boundingBox;
    bool drawBoundingBox = false;
};
