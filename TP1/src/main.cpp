#include "ofMain.h"
#include "application.h"
#include "histogramApplication.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);
	auto mainApp = make_shared<Application>();

	ofRunApp(window, mainApp);

	ofRunMainLoop();

}
