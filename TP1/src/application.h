#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "histogramApplication.h"
#include "assetManager.h"

class ofxToggle2 : public ofxToggle {
public:
	ofRectangle getChecboxRect()
	{
		return this->checkboxRect;
	}

	bool ofxToggle2::operator=(bool v) {
		this->value = v;
		return v;
	}

	bool isVisible()
	{
		return this->isGuiDrawing();
	}
};

class ofxButton2 : public ofxButton {
public:
	ofRectangle getChecboxRect()
	{
		return this->checkboxRect;
	}

	bool ofxButton2::operator=(bool v) {
		this->value = v;
		return v;
	}

	bool isVisible()
	{
		return this->isGuiDrawing();
	}
};

class ofxIntSlider2 : public ofxIntSlider {
public:
	bool ofxIntSlider2::operator=(bool v) {
		this->value = v;
		return v;
	}

	bool isVisible()
	{
		return this->isGuiDrawing();
	}
};

class ofxColorSlider2 : public ofxColorSlider {
public:
	ofColor ofxColorSlider2::operator=(ofColor color) {
		this->changeValue(color);

		return color;
	}

	bool isVisible()
	{
		return this->isGuiDrawing();
	}
};

class Application : public ofBaseApp {

public:
	ofxPanel gui;
	ofxPanel assetsPanel;
	ofxPanel cameraPanel;
	ofxPanel objectPanel;

	ofxToggle2 togglePerspective;
	ofxToggle2 toggleOrtho;

	ofxButton2 resetButton;
	ofxButton2 histogramButton;
	ofxGuiGroup groupDraw;
	ofxGuiGroup groupDrawOptions;
	ofxGuiGroup groupDrawBoundingBox;
	ofxGuiGroup groupGeometry;
	//ofxGuiGroup groupGeometryOptions;
	ofxGuiGroup groupCamera;
	ofxGuiGroup groupCameraProjection;
	ofxGuiGroup groupTranslation;
	ofxGuiGroup groupRotation;
	ofxGuiGroup groupScale;

	ofxToggle2 toggleDrawLine;
	ofxToggle2 toggleDrawRectangle;
	ofxToggle2 toggleDrawCircle;
	ofxToggle2 toggleDrawEllipse;
	ofxToggle2 toggleDrawTriangle;
	ofxToggle2 toggleDrawBoundingBox;

	ofxToggle2 toggleDrawCube;
	ofxToggle2 toggleDrawSphere;

	ofxButton2 deleteButton;
	std::unordered_map<std::string, std::shared_ptr<ofxToggle2>> assetsButtons;

	ofxColorSlider2 fillColorSlider;

	ofxColorSlider2 boundingBoxColorSlider;

	ofxColorSlider2 backgroundColorSlider;

	ofxIntSlider2 lineWidth;
	ofxIntSlider2 boundingBoxLineWidth;

	//ofxIntSlider2 geometryRotateX;
	//ofxIntSlider2 geometryRotateY;

	ofxFloatField translateXField;
	ofxFloatSlider translateXSlider;
	ofxFloatField translateYField;
	ofxFloatSlider translateYSlider;
	ofxFloatField translateZField;
	ofxFloatSlider translateZSlider;
	ofxFloatField rotateXField;
	ofxFloatSlider rotateXSlider;
	ofxFloatField rotateYField;
	ofxFloatSlider rotateYSlider;
	ofxFloatField rotateZField;
	ofxFloatSlider rotateZSlider;
	ofxFloatField scaleXField;
	ofxFloatSlider scaleXSlider;
	ofxFloatField scaleYField;
	ofxFloatSlider scaleYSlider;
	ofxFloatField scaleZField;
	ofxFloatSlider scaleZSlider;

	ofxToggle2 toggleDrawFill;

	HistogramApplication* histogramWindowApplication;
	std::shared_ptr<ofAppBaseWindow> histogramWindow;

	AssetManager assetManager;
	std::vector<Asset*> selectedAssets;

	std::vector<ofxPanel*> pointerGuiPanelElements;
	std::vector<ofxGuiGroup*> pointerGuiGroupElements;
	std::vector<ofxButton2*> pointerGuiButtonElements;
	std::vector<ofxToggle2*> pointerGuiToggleElements;
	std::vector<ofxIntSlider2*> pointerGuiIntSliderElements;
	std::vector<ofxColorSlider2*> pointerGuiColorSliderElements;
	std::vector<ofxFloatField*> pointerGuiFloatFieldElements;
	std::vector<ofxFloatSlider*> pointerGuiFloatSliderElements;

	std::vector<std::unique_ptr<ofEasyCam>> cameras;

	int activeCamIndex = 0;

	ofxLabel lblCamActive;

	int mousePressX;
	int mousePressY;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawLineToggleChanged(bool& value);
	void drawRectangleToggleChanged(bool& value);
	void drawCircleToggleChanged(bool& value);
	void drawEllipseToggleChanged(bool& value);
	void drawTriangleToggleChanged(bool& value);
	void drawBoundingBoxToggleChanged(bool& value);

	void drawCubeToggleChanged(bool& value);
	void drawSphereToggleChanged(bool& value);

	void isFilledToggleChanged(bool& value);
	void drawColorChanged(ofColor& value);
	void lineWidthChanged(int& value);

	void boundingBoxColorChanged(ofColor& value);
	void boundingBoxLineWidthChanged(int& value);

	//void geometryRotateXChanged(int& value);
	//void geometryRotateYChanged(int& value);

	void positionXChanged(float& value);
	void positionYChanged(float& value);
	void positionZChanged(float& value);
	void translateXChanged(float& value);
	void translateYChanged(float& value);
	void translateZChanged(float& value);
	void angleXChanged(float& value);
	void angleYChanged(float& value);
	void angleZChanged(float& value);
	void rotateXChanged(float& value);
	void rotateYChanged(float& value);
	void rotateZChanged(float& value);
	void scaleXChanged(float& value);
	void scaleYChanged(float& value);
	void scaleZChanged(float& value);
	void growthXChanged(float& value);
	void growthYChanged(float& value);
	void growthZChanged(float& value);

	void selectedAssetChanged(bool& value);

	void togglePerspectiveChanged(bool& value);
	void toggleOrthoChanged(bool& value);

	void resetButtonPressed();
	void histogramButtonPressed();
	void deleteButtonPressed();

	void resetToggles();
	void clearSelectedAssets();

	void checkForCursor(int x, int y);

	void updateBoundingBox();
	glm::vec3 getMaxPos(Asset asset);
	glm::vec3 getMinPos(Asset asset);

	bool clickedInUi = false;
	bool recording = false;
	bool screenshot = false;
	int imageIndex = 0;

	void setCameraTargetOnSelectedAssets();

	void exportImage();
};