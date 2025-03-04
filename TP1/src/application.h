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

		ofxToggle2 togglePerspective;
		ofxToggle2 toggleOrtho;

		ofxButton2 resetButton;
		ofxButton2 histogramButton;
		ofxGuiGroup groupDraw;
		ofxGuiGroup groupDrawOptions;
		ofxGuiGroup groupDrawBoundingBox;
		ofxGuiGroup groupGeometry;
		ofxGuiGroup groupGeometryOptions;
		ofxGuiGroup groupCamera;
		ofxGuiGroup groupCameraProjection;

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

		ofxIntSlider2 geometryRotateX;
		ofxIntSlider2 geometryRotateY;

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

		ofEasyCam camera;

		int mousePressX;
		int mousePressY;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
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

		void geometryRotateXChanged(int& value);
		void geometryRotateYChanged(int& value);

		void selectedAssetChanged(bool& value);

		void toggleProjectionModeChanged(bool& value);
		
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
};
