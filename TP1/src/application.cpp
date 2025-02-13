#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
	gui.setup();

	resetButton.addListener(this, &Application::resetButtonPressed);
	histogramButton.addListener(this, &Application::histogramButtonPressed);

	gui.add(resetButton.setup("Reinitialiser"));
	gui.add(histogramButton.setup("Histogramme"));

	groupDraw.setup("Outils de dessin");
	groupDrawOptions.setup("Options");

	toggleDrawLine.addListener(this, &Application::drawLineToggleChanged);
	groupDraw.add(toggleDrawLine.setup("Ligne", false));

	toggleDrawRectangle.addListener(this, &Application::drawRectangleToggleChanged);
	groupDraw.add(toggleDrawRectangle.setup("Rectangle", false));

	toggleDrawCircle.addListener(this, &Application::drawCircleToggleChanged);
	groupDraw.add(toggleDrawCircle.setup("Cercle", false));

	toggleDrawEllipse.addListener(this, &Application::drawEllipseToggleChanged);
	groupDraw.add(toggleDrawEllipse.setup("Ellipse", false));

	toggleDrawTriangle.addListener(this, &Application::drawTriangleToggleChanged);
	groupDraw.add(toggleDrawTriangle.setup("Triangle", false));

	groupDrawOptions.add(toggleDrawFill.setup("Remplir", false));
	groupDrawOptions.add(lineWidth.setup("Epaisseur", 5, 1, 100));

	groupDrawOptions.add(fillColorSlider.setup("Couleur", ofColor(255, 255, 255), ofColor(0, 0), ofColor(255, 255)));
	groupDraw.add(&groupDrawOptions);

	gui.add(&groupDraw);

	gui.add(backgroundColorSlider.setup("Arriere-Plan", ofColor(100, 100, 100), ofColor(0, 0), ofColor(255, 255)));

	assetManager.assets.clear();
}

//--------------------------------------------------------------
void Application::update()
{
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
	ofBackground(backgroundColorSlider);
	gui.draw();
	assetManager.draw();
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
void Application::mousePressed(int x, int y, int button)
{
	mousePressX = x;
	mousePressY = y;
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
	if (toggleDrawLine)
	{
		assetManager.addLine("line_" + std::to_string(x) + "_" + std::to_string(y), { mousePressX, mousePressY }, { x, y }, lineWidth, fillColorSlider, toggleDrawFill);
	}
	else if (toggleDrawRectangle)
	{
		assetManager.addRectangle("rectangle_" + std::to_string(x) + "_" + std::to_string(y), { mousePressX, mousePressY }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);
	}
	else if (toggleDrawCircle)
	{
		assetManager.addCircle("circle_" + std::to_string(x) + "_" + std::to_string(y), { mousePressX, mousePressY }, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);
	}
	else if (toggleDrawEllipse)
	{
		assetManager.addEllipse("ellipse_" + std::to_string(x) + "_" + std::to_string(y), { mousePressX, mousePressY }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);
	}
	else if (toggleDrawTriangle)
	{
		assetManager.addTriangle("triangle_" + std::to_string(x) + "_" + std::to_string(y), { mousePressX, mousePressY }, { mousePressX + ( x - mousePressX) / 2, y }, { mousePressX - (x - mousePressX) / 2, y }, lineWidth, fillColorSlider, toggleDrawFill);
	}
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
void Application::drawLineToggleChanged(bool& value)
{
	if (toggleDrawLine)
	{
		toggleDrawRectangle = false;
		toggleDrawCircle = false;
		toggleDrawEllipse = false;
		toggleDrawTriangle = false;
	}
}

//--------------------------------------------------------------
void Application::drawRectangleToggleChanged(bool& value)
{
	if (toggleDrawRectangle)
	{
		toggleDrawLine = false;
		toggleDrawCircle = false;
		toggleDrawEllipse = false;
		toggleDrawTriangle = false;
	}
}

//--------------------------------------------------------------
void Application::drawCircleToggleChanged(bool& value)
{
	if (toggleDrawCircle)
	{
		toggleDrawLine = false;
		toggleDrawRectangle = false;
		toggleDrawEllipse = false;
		toggleDrawTriangle = false;
	}
}

//--------------------------------------------------------------
void Application::drawEllipseToggleChanged(bool& value)
{
	if (toggleDrawEllipse)
	{
		toggleDrawLine = false;
		toggleDrawRectangle = false;
		toggleDrawCircle = false;
		toggleDrawTriangle = false;
	}
}

//--------------------------------------------------------------
void Application::drawTriangleToggleChanged(bool& value)
{
	if (toggleDrawTriangle)
	{
		toggleDrawLine = false;
		toggleDrawRectangle = false;
		toggleDrawEllipse = false;
		toggleDrawCircle = false;
	}
}

//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo)
{
	int importedImageCount = assetManager.assets.size();

	for (int i = 0; i < dragInfo.files.size(); i++)
	{
		assetManager.addImage("imported_image_" + std::to_string(importedImageCount + i), dragInfo.files[i], dragInfo.position);
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
