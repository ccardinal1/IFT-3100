#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "ofxGui.h"
#include "histogramApplication.h"

class Application : public ofBaseApp{

	public:
		Renderer renderer;

		ofxPanel gui;
		ofxButton resetButton;
		ofxButton histogramButton;

		HistogramApplication* histogramWindowApplication;
		std::shared_ptr<ofAppBaseWindow> histogramWindow;

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
		
		void resetButtonPressed();
		void histogramButtonPressed();

};
