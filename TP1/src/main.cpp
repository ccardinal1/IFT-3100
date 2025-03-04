#include "ofMain.h"
#include "application.h"
#include "histogramApplication.h"

//========================================================================
int main() {
	ofGLWindowSettings settings;
	settings.setSize(1440, 900);
	settings.windowMode = OF_WINDOW;

	auto window = ofCreateWindow(settings);
	auto mainApp = make_shared<Application>();

	ofRunApp(window, mainApp);

	ofRunMainLoop();
}
