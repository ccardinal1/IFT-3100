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
	lineWidth.addListener(this, &Application::lineWidthChanged);
	
	geometryRotateX.addListener(this, &Application::geometryRotateXChanged);
	geometryRotateY.addListener(this, &Application::geometryRotateYChanged);

	gui.add(resetButton.setup("Reinitialiser"));
	gui.add(histogramButton.setup("Histogramme"));

	groupDraw.setup("Outils de dessin");
	groupDrawOptions.setup("Options");
	groupGeometry.setup("Geometrie");
	groupGeometryOptions.setup("Options");

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

	ofParameter<ofColor> colorParam = ofParameter<ofColor>("Couleur", ofColor(255, 255, 255), ofColor(0, 0), ofColor(255, 255));

	colorParam.addListener(this, &Application::drawColorChanged);

	groupDrawOptions.add(fillColorSlider.setup(colorParam));
	groupDraw.add(&groupDrawOptions);

	toggleDrawCube.addListener(this, &Application::drawCubeToggleChanged);
	groupGeometry.add(toggleDrawCube.setup("Cube", false));

	toggleDrawSphere.addListener(this, &Application::drawSphereToggleChanged);
	groupGeometry.add(toggleDrawSphere.setup("Sphere", false));

	groupGeometryOptions.add(geometryRotateX.setup("Rotation X", 0, 0, 360));
	groupGeometryOptions.add(geometryRotateY.setup("Rotation Y", 0, 0, 360));
	groupGeometry.add(&groupGeometryOptions);

	gui.add(&groupDraw);
	gui.add(&groupGeometry);
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

	if (!toggleDrawLine && !toggleDrawRectangle && !toggleDrawCircle && !toggleDrawEllipse && !toggleDrawTriangle && !toggleDrawCube && !toggleDrawSphere)
	{
		if (selectedAssets.size() == 0)
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
				*assetsButtons[tempAsset->name] = true;

				selectedAssets.push_back(tempAsset);
			}
		}
	}
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
	if (mousePressX == x && mousePressY == y)
	{
		return;
	}

    if (toggleDrawLine)
	{
		string shapeName = "line_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addLine(shapeName, { mousePressX, mousePressY }, { x, y }, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Ligne", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawRectangle)
	{
		string shapeName = "rectangle_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addRectangle(shapeName, { mousePressX, mousePressY }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Rectangle", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawCircle)
	{
		string shapeName = "circle_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addCircle(shapeName, { mousePressX, mousePressY }, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Cercle", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawEllipse)
	{
		string shapeName = "ellipse_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addEllipse(shapeName, { mousePressX, mousePressY }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Ellipse", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawTriangle)
	{
		string shapeName = "triangle_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addTriangle(shapeName, { mousePressX, mousePressY }, { mousePressX + (x - mousePressX) / 2, y }, { mousePressX - (x - mousePressX) / 2, y }, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Triangle", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawCube)
	{
		string shapeName = "cube_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addCube(shapeName, { x, y, 0 }, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Cube", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawSphere)
	{
		string shapeName = "sphere_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addSphere(shapeName, { x, y, 0 }, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle>();
		assetsPanel.add(button.get()->setup("Sphere", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (!selectedAssets.empty())
	{
		glm::vec2 moveVec = { x - mousePressX, y - mousePressY };

		for (Asset* asset : selectedAssets)
		{
			if (asset->type == AssetType::CUBE || asset->type == AssetType::SPHERE)
			{
				assetManager.setPosition(asset, asset->position3d + glm::vec3(moveVec.x, moveVec.y, 0));
			}
			else
			{
				assetManager.setPosition(asset, asset->position2d + moveVec);
			}
		}
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
		clearSelectedAssets();
		resetToggles();
		toggleDrawLine = true;
	}
}

//--------------------------------------------------------------
void Application::drawRectangleToggleChanged(bool& value)
{
	if (toggleDrawRectangle)
	{
		clearSelectedAssets();
		resetToggles();
		toggleDrawRectangle = true;
	}
}

//--------------------------------------------------------------
void Application::drawCircleToggleChanged(bool& value)
{
	if (toggleDrawCircle)
	{
		clearSelectedAssets();
		resetToggles();
		toggleDrawCircle = true;
	}
}

//--------------------------------------------------------------
void Application::drawEllipseToggleChanged(bool& value)
{
	if (toggleDrawEllipse)
	{
		clearSelectedAssets();
		resetToggles();
		toggleDrawEllipse = true;
	}
}

//--------------------------------------------------------------
void Application::drawTriangleToggleChanged(bool& value)
{
	if (toggleDrawTriangle)
	{
		clearSelectedAssets();
		resetToggles();
		toggleDrawTriangle = true;
	}
}

//--------------------------------------------------------------
void Application::drawCubeToggleChanged(bool& value)
{
	if (toggleDrawCube)
	{
		clearSelectedAssets();
		resetToggles();
		toggleDrawCube = true;
	}
}

//--------------------------------------------------------------
void Application::drawSphereToggleChanged(bool& value)
{
	if (toggleDrawSphere)
	{
		clearSelectedAssets();
		resetToggles();
		toggleDrawSphere = true;
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

void Application::drawColorChanged(ofColor& value)
{
	for (Asset* asset : selectedAssets)
	{
		asset->color = fillColorSlider;
	}
}

//--------------------------------------------------------------
void Application::lineWidthChanged(int& value)
{
	for (Asset* asset : selectedAssets)
	{
		asset->lineWidth = lineWidth;
	}
}

//--------------------------------------------------------------
void Application::geometryRotateXChanged(int& value)
{
	for (Asset* asset : selectedAssets)
	{
		if (asset->type == AssetType::CUBE)
		{
			assetManager.rotateX(asset, value);
		}
	}
}

//--------------------------------------------------------------
void Application::geometryRotateYChanged(int& value)
{
	for (Asset* asset : selectedAssets)
	{
		if (asset->type == AssetType::CUBE)
		{
			assetManager.rotateY(asset, value);
		}
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
			Asset* asset = &assetManager.assets[key];

			if (selectedAssets.size() == 0)
			{
				toggleDrawFill = asset->isFilled;
				fillColorSlider = asset->color;
				lineWidth = asset->lineWidth;

				if (asset->geometryPrimitive.getMesh().getNumVertices() > 0)
				{
					geometryRotateX = asset->geometryPrimitive.getPitchDeg();
					geometryRotateY = asset->geometryPrimitive.getHeadingDeg();
				}
				else
				{
					geometryRotateX = 0;
					geometryRotateY = 0;
				}
			}

			selectedAssets.push_back(asset);
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
		assetsPanel.add(button.get()->setup("Image", true));
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

//--------------------------------------------------------------
void Application::resetToggles()
{
	toggleDrawLine = false;
	toggleDrawRectangle = false;
	toggleDrawEllipse = false;
	toggleDrawCircle = false;
	toggleDrawTriangle = false;

	toggleDrawCube = false;
	toggleDrawSphere = false;
}

//--------------------------------------------------------------
void Application::clearSelectedAssets()
{
	for (auto& [key, button] : assetsButtons)
	{
		*button = false;
	}

	selectedAssets.clear();
}
