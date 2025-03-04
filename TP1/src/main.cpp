#include "ofMain.h"
#include "application.h"
#include "histogramApplication.h"

//========================================================================
int main() {
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW;

	auto window = ofCreateWindow(settings);
	auto mainApp = make_shared<Application>();

	ofRunApp(window, mainApp);

	ofRunMainLoop();
}
