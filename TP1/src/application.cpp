#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
	gui.setup();
	assetsPanel.setup();
	assetsPanel.setName("Graphe de scene");
	assetsPanel.setPosition(ofGetWindowWidth() - assetsPanel.getWidth() - 10, 10);

	resetButton.addListener(this, &Application::resetButtonPressed);
	histogramButton.addListener(this, &Application::histogramButtonPressed);
	deleteButton.addListener(this, &Application::deleteButtonPressed);
	toggleDrawFill.addListener(this, &Application::isFilledToggleChanged);

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

	assetsPanel.add(deleteButton.setup("Supprimer"));

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

	for (Asset* asset : selectedAssets)
	{
		asset->color = fillColorSlider;
	}
}

//--------------------------------------------------------------
void Application::draw()
{
	ofBackground(backgroundColorSlider);
	assetManager.draw();
	gui.draw();
	assetsPanel.draw();
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
void Application::mouseMoved(int x, int y)
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

	if (!toggleDrawLine && !toggleDrawRectangle && !toggleDrawCircle && !toggleDrawEllipse && !toggleDrawTriangle)
	{
		Asset* tempAsset = assetManager.getAsset({ x, y });

		if (tempAsset == NULL)
		{
			if (!selectedAssets.empty())
			{
				selectedAssets[0]->isSelected = false;
				selectedAssets.clear();
			}
		}
		else if (!selectedAssets.empty())
		{
			for (Asset* asset : selectedAssets)
			{
				asset->isSelected = false;
				*assetsButtons[asset->name] = false;
			}

			selectedAssets.clear();

			tempAsset->isSelected = true;
			selectedAssets.push_back(tempAsset);
			*assetsButtons[tempAsset->name] = true;
		}
		else if (selectedAssets.empty() || tempAsset != selectedAssets[0])
		{
			if (!selectedAssets.empty())
			{
				selectedAssets[0]->isSelected = false;
			}
			tempAsset->isSelected = true;

			selectedAssets.push_back(tempAsset);
		}
	}
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
	if (!selectedAssets.empty())
	{
		assetManager.setPosition(selectedAssets[0], {x, y});
	}
	else if (toggleDrawLine)
	{
		string shapeName = "line_" + std::to_string(x) + "_" + std::to_string(y);
		assetManager.addLine(shapeName, { mousePressX, mousePressY }, { x, y }, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Ligne", false));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;
	}
	else if (toggleDrawRectangle)
	{
		string shapeName = "rectangle_" + std::to_string(x) + "_" + std::to_string(y);
		assetManager.addRectangle(shapeName, { mousePressX, mousePressY }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Rectangle", false));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;
	}
	else if (toggleDrawCircle)
	{
		string shapeName = "circle_" + std::to_string(x) + "_" + std::to_string(y);
		assetManager.addCircle(shapeName, { mousePressX, mousePressY }, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Cercle", false));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;
	}
	else if (toggleDrawEllipse)
	{
		string shapeName = "ellipse_" + std::to_string(x) + "_" + std::to_string(y);
		assetManager.addEllipse(shapeName, { mousePressX, mousePressY }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Ellipse", false));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;
	}
	else if (toggleDrawTriangle)
	{
		string shapeName = "triangle_" + std::to_string(x) + "_" + std::to_string(y);
		assetManager.addTriangle(shapeName, { mousePressX, mousePressY }, { mousePressX + (x - mousePressX) / 2, y }, { mousePressX - (x - mousePressX) / 2, y }, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Triangle", false));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;
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
		selectedAssets.clear();
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
		selectedAssets.clear();
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
		selectedAssets.clear();
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
		selectedAssets.clear();
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
		selectedAssets.clear();
		toggleDrawLine = false;
		toggleDrawRectangle = false;
		toggleDrawEllipse = false;
		toggleDrawCircle = false;
	}
}

//--------------------------------------------------------------
void Application::isFilledToggleChanged(bool& value)
{
	for (Asset* asset : selectedAssets)
	{
		asset->isFilled = value;
	}
}

//--------------------------------------------------------------
void Application::selectedAssetChanged(bool& value)
{
	selectedAssets.clear();
	for (auto& [key, button] : assetsButtons)
	{
		if (button && *button)
		{
			selectedAssets.push_back(&assetManager.assets[key]);
		}
	}
}

//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo)
{
	int importedImageCount = assetManager.assets.size();

	for (int i = 0; i < dragInfo.files.size(); i++)
	{
		string imageName = "imported_image_" + std::to_string(importedImageCount + i);
		assetManager.addImage(imageName, dragInfo.files[i], dragInfo.position);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Image", false));
		assetsButtons[imageName] = button;
	}
}

//--------------------------------------------------------------
void Application::resetButtonPressed()
{
	assetsPanel.clear();

	std::vector<std::string> buttonsToRemove;

	for (auto& [key, button] : assetsButtons)
	{
		buttonsToRemove.push_back(key);
	}

	for (auto& name : buttonsToRemove)
	{
		assetsButtons.erase(name);
	}

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

//--------------------------------------------------------------
void Application::deleteButtonPressed()
{
	std::vector<std::string> buttonsToRemove;
	assetsPanel.clear();
	assetsPanel.add(&deleteButton);

	for (auto& [key, button] : assetsButtons) 
	{

		if (button && *button)
		{
			assetManager.deleteAsset(key);
			buttonsToRemove.push_back(key);
		}
		else
		{
			assetsPanel.add(button.get());
		}
	}


	for (const auto& name : buttonsToRemove)
	{
		assetsButtons.erase(name);
	}
}
