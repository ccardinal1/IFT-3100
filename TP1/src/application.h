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

		ofxToggle toggleDrawLine;
		ofxToggle toggleDrawRectangle;
		ofxToggle toggleDrawCircle;
		ofxToggle toggleDrawEllipse;
		ofxToggle toggleDrawTriangle;

		ofxButton deleteButton;
		std::unordered_map<std::string, std::shared_ptr<ofxToggle>> assetsButtons;

		ofxColorSlider fillColorSlider;
		ofxColorSlider backgroundColorSlider;

		ofxIntSlider lineWidth;

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
		
		void isFilledToggleChanged(bool& value);
		void drawColorChanged(ofColor& value);

		void selectedAssetChanged(bool& value);
		
		void resetButtonPressed();
		void histogramButtonPressed();
		void deleteButtonPressed();

};
