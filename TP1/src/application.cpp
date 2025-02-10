#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
	renderer.setup();
	gui.setup();

	resetButton.addListener(this, &Application::resetButtonPressed);
	histogramButton.addListener(this, &Application::histogramButtonPressed);

	gui.add(resetButton.setup("Reinitialiser"));
	gui.add(histogramButton.setup("Histogramme"));

}

//--------------------------------------------------------------
void Application::update()
{
	renderer.update();
	if (histogramWindowApplication && !histogramWindowApplication->isClosed)
	{
		ofImage img;
		img.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		histogramWindowApplication->setHistogram(img);
	}
}

//--------------------------------------------------------------
void Application::draw()
{
	renderer.draw();
	gui.draw();
}

//--------------------------------------------------------------
void Application::keyPressed(int key)
{

}

//--------------------------------------------------------------
void Application::keyReleased(int key)
{

}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void Application::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void Application::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo)
{

	for (int i = 0; i < dragInfo.files.size(); i++)
	{
		renderer.importedImages.push_back(ofImage());
		renderer.importedImages.back().load(dragInfo.files[i]);
	}
}

//--------------------------------------------------------------
void Application::resetButtonPressed()
{
	setup();
	histogramWindow.get()->setWindowShouldClose();
}

//--------------------------------------------------------------
void Application::histogramButtonPressed()
{
	ofImage img;
	img.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	if (!histogramWindowApplication || histogramWindowApplication->isClosed)
	{
		ofGLWindowSettings settings;
		settings.setSize(500, 300);
		settings.title = "Histogramme";

		histogramWindow = ofCreateWindow(settings);
		auto histogramApp = make_shared<HistogramApplication>();

		ofRunApp(histogramWindow, histogramApp);

		histogramWindowApplication = histogramApp.get();
		histogramWindowApplication->isClosed = false;
	}

	histogramWindowApplication->setHistogram(img);
}
