#include "ofMain.h"
#include "application.h"
#include "histogramApplication.h"

//========================================================================
int main() {
	ofGLWindowSettings settings;
	settings.setSize(1440, 900);
	settings.windowMode = OF_WINDOW;
	settings.setGLVersion(3, 3);
	settings.title = "IFT-3100 - Hiver 2025 - Equipe 08 - TP1";

	auto window = ofCreateWindow(settings);
	auto mainApp = make_shared<Application>();

	ofRunApp(window, mainApp);

	ofRunMainLoop();
}
