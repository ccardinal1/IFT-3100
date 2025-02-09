#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
	renderer.setup();
	gui.setup();

	resetButton.addListener(this, &Application::resetButtonPressed);

	gui.add(resetButton.setup("Reinitialiser"));

}

//--------------------------------------------------------------
void Application::update()
{
	renderer.update();
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

void Application::resetButtonPressed()
{
	renderer.importedImages.clear();
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
