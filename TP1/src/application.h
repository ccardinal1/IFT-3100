#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "histogramApplication.h"
#include "assetManager.h"
#include "ofxAssimpModelLoader.h"

class ofxGuiGroup2 : public ofxGuiGroup {
public:
	bool isVisible()
	{
		return this->isGuiDrawing();
	}
};

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

	void setColor(ofColor color)
	{
		this->changeValue(color);
	}

	bool isVisible()
	{
		return this->isGuiDrawing();
	}
};

class ofxFloatSlider2 : public ofxFloatSlider {
public:
	ofxFloatSlider2()
	{
		this->value = 0;
	}

	ofColor ofxFloatSlider2::operator=(float value) {
		this->value = value;

		return value;
	}

	float getValue()
	{
		return this->value;
	}

	bool isVisible()
	{
		return this->isGuiDrawing();
	}
};

class ofxFloatField2 : public ofxFloatField {
public:
	ofColor ofxFloatField2::operator=(float value) {
		this->value = value;

		return value;
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
	ofxToggle2 toggleCenterOnSelection;

	ofxButton2 resetButton;
	ofxButton2 histogramButton;

	ofxGuiGroup2 groupDraw;
	ofxGuiGroup2 groupDrawOptions;
	ofxGuiGroup2 groupDrawBoundingBox;
	ofxGuiGroup2 groupGeometry;
	//ofxGuiGroup2 groupGeometryOptions;
	ofxGuiGroup2 groupCamera;
	ofxGuiGroup2 groupCameraProjection;
	ofxGuiGroup2 groupTranslation;
	ofxGuiGroup2 groupRotation;
	ofxGuiGroup2 groupScale;
	ofxGuiGroup2 groupHSBFillColor;
	ofxGuiGroup2 groupHSBBoundingBoxColor;
	ofxGuiGroup2 groupHSBBackgroundColor;

	ofxToggle2 toggleDrawLine;
	ofxToggle2 toggleDrawRectangle;
	ofxToggle2 toggleDrawCircle;
	ofxToggle2 toggleDrawEllipse;
	ofxToggle2 toggleDrawTriangle;
	ofxToggle2 toggleDrawBoundingBox;

	ofxToggle2 toggleDrawCube;
	ofxToggle2 toggleDrawSphere;

	ofxToggle2 toggleAddModel1;
	ofxToggle2 toggleAddModel2;
	ofxToggle2 toggleAddModel3;

	ofxButton2 deleteButton;
	std::unordered_map<std::string, std::shared_ptr<ofxToggle2>> assetsButtons;

	ofxFloatSlider2 HFillColorSlider;
	ofxFloatSlider2 SFillColorSlider;
	ofxFloatSlider2 BFillColorSlider;
	ofxColorSlider2 RGBAFillColorSlider;

	ofxFloatSlider2 HBoundingBoxColorSlider;
	ofxFloatSlider2 SBoundingBoxColorSlider;
	ofxFloatSlider2 BBoundingBoxColorSlider;
	ofxColorSlider2 RGBABoundingBoxColorSlider;

	ofxFloatSlider2 HBackgroundColorSlider;
	ofxFloatSlider2 SBackgroundColorSlider;
	ofxFloatSlider2 BBackgroundColorSlider;
	ofxColorSlider2 RGBABackgroundColorSlider;

	ofxIntSlider2 lineWidth;
	ofxIntSlider2 boundingBoxLineWidth;

	//ofxIntSlider2 geometryRotateX;
	//ofxIntSlider2 geometryRotateY;

	ofxFloatField2 translateXField;
	ofxFloatSlider2 translateXSlider;
	ofxFloatField2 translateYField;
	ofxFloatSlider2 translateYSlider;
	ofxFloatField2 translateZField;
	ofxFloatSlider2 translateZSlider;
	ofxFloatField2 rotateXField;
	ofxFloatSlider2 rotateXSlider;
	ofxFloatField2 rotateYField;
	ofxFloatSlider2 rotateYSlider;
	ofxFloatField2 rotateZField;
	ofxFloatSlider2 rotateZSlider;
	ofxFloatField2 scaleXField;
	ofxFloatSlider2 scaleXSlider;
	ofxFloatField2 scaleYField;
	ofxFloatSlider2 scaleYSlider;
	ofxFloatField2 scaleZField;
	ofxFloatSlider2 scaleZSlider;

	ofxToggle2 toggleDrawFill;

	HistogramApplication* histogramWindowApplication;
	std::shared_ptr<ofAppBaseWindow> histogramWindow;

	AssetManager assetManager;
	std::vector<Asset*> selectedAssets;

	std::vector<ofxPanel*> pointerGuiPanelElements;
	std::vector<ofxGuiGroup2*> pointerGuiGroupElements;
	std::vector<ofxButton2*> pointerGuiButtonElements;
	std::vector<ofxToggle2*> pointerGuiToggleElements;
	std::vector<ofxIntSlider2*> pointerGuiIntSliderElements;
	std::vector<ofxColorSlider2*> pointerGuiColorSliderElements;
	std::vector<ofxFloatField2*> pointerGuiFloatFieldElements;
	std::vector<ofxFloatSlider2*> pointerGuiFloatSliderElements;

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

	void drawModel1ToggleChanged(bool& value);
	void drawModel2ToggleChanged(bool& value);
	void drawModel3ToggleChanged(bool& value);

	void isFilledToggleChanged(bool& value);
	void RGBADrawColorChanged(ofColor& value);
	void lineWidthChanged(int& value);
	
	void RGBABoundingBoxColorChanged(ofColor& value);
	void boundingBoxLineWidthChanged(int& value);

	void RGBABackgroundColorChanged(ofColor& value);

	void HSBDrawColorChanged(float& value);
	void HSBBoundingBoxColorChanged(float& value);
	void HSBBackgroundColorChanged(float& value);

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
	void toggleCenterOnSelectionChanged(bool& value);

	void resetButtonPressed();
	void histogramButtonPressed();
	void deleteButtonPressed();

	void resetToggles();
	void clearSelectedAssets();

	void checkForCursor(int x, int y);

	void updateBoundingBox();
	std::vector<glm::vec3> getExtremePos(Asset* asset);

	ofColor backgroundColor;

	bool clickedInUi = false;
	bool recording = false;
	bool screenshot = false;
	bool cameraMode = false;
	int imageIndex = 0;
	bool isMousePressed = false;
	glm::vec3 previousPosition;
	glm::vec3 previousRotation;
	glm::vec3 previousScale;

	bool changedColor;

	void setCameraTargetOnSelectedAssets(bool value);
	bool isDrawing();
	bool isInGui(int x, int y);

	void exportImage();

	const HCURSOR PEN = LoadCursorFromFile(L"../bin/data/cursors/aero_pen.cur");
	const HCURSOR CAM = LoadCursorFromFile(L"../bin/data/cursors/grab.cur");

	const glm::vec3 DEFAULT_CAM_POS = glm::vec3(0, 0, 779);
};