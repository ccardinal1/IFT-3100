#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "histogramApplication.h"
#include "assetManager.h"

class Application : public ofBaseApp{

	public:
		ofxPanel gui;
		ofxPanel assetsPanel;
		ofxButton resetButton;
		ofxButton histogramButton;
		ofxGuiGroup groupDraw;
		ofxGuiGroup groupDrawOptions;
		ofxGuiGroup groupGeometry;
		ofxGuiGroup groupGeometryOptions;

		ofxToggle toggleDrawLine;
		ofxToggle toggleDrawRectangle;
		ofxToggle toggleDrawCircle;
		ofxToggle toggleDrawEllipse;
		ofxToggle toggleDrawTriangle;

		ofxToggle toggleDrawCube;
		ofxToggle toggleDrawSphere;

		ofxButton deleteButton;
		std::unordered_map<std::string, std::shared_ptr<ofxToggle>> assetsButtons;

		ofxColorSlider fillColorSlider;

		ofxColorSlider backgroundColorSlider;

		ofxIntSlider lineWidth;

		ofxIntSlider geometryRotateX;
		ofxIntSlider geometryRotateY;

		ofxToggle toggleDrawFill;

		HistogramApplication* histogramWindowApplication;
		std::shared_ptr<ofAppBaseWindow> histogramWindow;

		AssetManager assetManager;
		std::vector<Asset*> selectedAssets;

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

		void drawCubeToggleChanged(bool& value);
		void drawSphereToggleChanged(bool& value);
		
		void isFilledToggleChanged(bool& value);
		void drawColorChanged(ofColor& value);
		void lineWidthChanged(int& value);

		void geometryRotateXChanged(int& value);
		void geometryRotateYChanged(int& value);

		void selectedAssetChanged(bool& value);
		
		void resetButtonPressed();
		void histogramButtonPressed();
		void deleteButtonPressed();

		void resetToggles();
		void clearSelectedAssets();

};
