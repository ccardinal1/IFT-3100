#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
	gui.setup("Menu");

	gui.setDefaultEventsPriority(OF_EVENT_ORDER_APP);

	pointerGuiPanelElements.push_back(&gui);
	pointerGuiPanelElements.push_back(&assetsPanel);

	pointerGuiGroupElements.push_back(&groupDraw);
	pointerGuiGroupElements.push_back(&groupDrawOptions);
	pointerGuiGroupElements.push_back(&groupDrawBoundingBox);
	pointerGuiGroupElements.push_back(&groupGeometry);
	pointerGuiGroupElements.push_back(&groupGeometryOptions);

	pointerGuiButtonElements.push_back(&resetButton);
	pointerGuiButtonElements.push_back(&histogramButton);
	pointerGuiButtonElements.push_back(&deleteButton);

	pointerGuiToggleElements.push_back(&toggleDrawLine);
	pointerGuiToggleElements.push_back(&toggleDrawRectangle);
	pointerGuiToggleElements.push_back(&toggleDrawCircle);
	pointerGuiToggleElements.push_back(&toggleDrawEllipse);
	pointerGuiToggleElements.push_back(&toggleDrawTriangle);
	pointerGuiToggleElements.push_back(&toggleDrawFill);
	pointerGuiToggleElements.push_back(&toggleDrawBoundingBox);
	pointerGuiToggleElements.push_back(&toggleDrawCube);
	pointerGuiToggleElements.push_back(&toggleDrawSphere);

	pointerGuiIntSliderElements.push_back(&lineWidth);
	pointerGuiIntSliderElements.push_back(&boundingBoxLineWidth);
	pointerGuiIntSliderElements.push_back(&geometryRotateX);
	pointerGuiIntSliderElements.push_back(&geometryRotateY);

	pointerGuiColorSliderElements.push_back(&fillColorSlider);
	pointerGuiColorSliderElements.push_back(&boundingBoxColorSlider);
	pointerGuiColorSliderElements.push_back(&backgroundColorSlider);

	assetsPanel.setup("Graphe de scene");
	assetsPanel.setPosition(ofGetWindowWidth() - assetsPanel.getWidth() - 10, 10);

	resetButton.addListener(this, &Application::resetButtonPressed);
	histogramButton.addListener(this, &Application::histogramButtonPressed);
	deleteButton.addListener(this, &Application::deleteButtonPressed);
	toggleDrawFill.addListener(this, &Application::isFilledToggleChanged);
	lineWidth.addListener(this, &Application::lineWidthChanged);
	boundingBoxLineWidth.addListener(this, &Application::boundingBoxLineWidthChanged);
	
	geometryRotateX.addListener(this, &Application::geometryRotateXChanged);
	geometryRotateY.addListener(this, &Application::geometryRotateYChanged);

	gui.add(resetButton.setup("Reinitialiser"));
	gui.add(histogramButton.setup("Histogramme"));

	groupDraw.setup("Outils de dessin");
	groupDrawOptions.setup("Options");
	groupGeometry.setup("Geometrie");
	groupGeometryOptions.setup("Options");
	groupDrawBoundingBox.setup("Boite de delimitation");

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
	groupDrawOptions.add(lineWidth.setup("Epaisseur", 5, 1, 10));

	ofParameter<ofColor> colorParam = ofParameter<ofColor>("Couleur", ofColor(255, 255, 255), ofColor(0, 0), ofColor(255, 255));

	colorParam.addListener(this, &Application::drawColorChanged);

	groupDrawOptions.add(fillColorSlider.setup(colorParam));

	toggleDrawBoundingBox.addListener(this, &Application::drawBoundingBoxToggleChanged);

	groupDrawBoundingBox.add(toggleDrawBoundingBox.setup("Activer", false));

	groupDrawBoundingBox.add(boundingBoxLineWidth.setup("Epaisseur", 2, 1, 10));

	ofParameter<ofColor> boundingBoxColorParam = ofParameter<ofColor>("Couleur", ofColor(255, 0, 0), ofColor(0, 0), ofColor(255, 255));
	boundingBoxColorParam.addListener(this, &Application::boundingBoxColorChanged);
	groupDrawBoundingBox.add(boundingBoxColorSlider.setup(boundingBoxColorParam));

	groupDrawOptions.add(&groupDrawBoundingBox);

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
	checkForCursor(x, y);
}

void Application::checkForCursor(int x, int y)
{
	for (auto& panel : pointerGuiPanelElements)
	{
		const int groupButtonOptionsWidth = 50;
		const int groupButtonHeight = 20;

		ofRectangle groupButton = ofRectangle(
			panel->getPosition().x + panel->getShape().width - groupButtonOptionsWidth,
			panel->getPosition().y,
			groupButtonOptionsWidth,
			groupButtonHeight
		);

		if (groupButton.inside(x, y)) {
			SetCursor(LoadCursor(NULL, IDC_HAND));

			return;
		}
	}

	for (auto& group : pointerGuiGroupElements)
	{
		const int groupButtonHeight = 20;

		ofRectangle groupButton = ofRectangle(
			group->getPosition().x,
			group->getPosition().y,
			group->getShape().width,
			groupButtonHeight
		);

		if (groupButton.inside(x, y)) {
			SetCursor(LoadCursor(NULL, IDC_HAND));

			return;
		}
	}

	for (auto& button : pointerGuiButtonElements)
	{
		if (button->isVisible())
		{
			ofRectangle absoluteCheckboxRect = ofRectangle(
				button->getChecboxRect().x + button->getPosition().x,
				button->getChecboxRect().y + button->getPosition().y,
				button->getChecboxRect().width,
				button->getChecboxRect().height
			);

			if (absoluteCheckboxRect.inside(x, y)) {
				SetCursor(LoadCursor(NULL, IDC_HAND));

				return;
			}
		}
	}

	for (auto& button : pointerGuiToggleElements)
	{
		if (button->isVisible())
		{
			ofRectangle absoluteCheckboxRect = ofRectangle(
				button->getChecboxRect().x + button->getPosition().x,
				button->getChecboxRect().y + button->getPosition().y,
				button->getChecboxRect().width,
				button->getChecboxRect().height
			);

			if (absoluteCheckboxRect.inside(x, y)) {
				SetCursor(LoadCursor(NULL, IDC_HAND));

				return;
			}
		}
	}

	for (auto& button : pointerGuiIntSliderElements)
	{
		if (button->isVisible())
		{
			if (button->getShape().inside(x, y)) {
				SetCursor(LoadCursor(NULL, IDC_HAND));

				return;
			}
		}
	}

	for (auto& button : pointerGuiColorSliderElements)
	{
		if (button->isVisible())
		{
			if (button->getShape().inside(x, y)) {
				SetCursor(LoadCursor(NULL, IDC_HAND));

				return;
			}
		}
	}

	for (auto const& [_, button] : assetsButtons)
	{
		if (button->isVisible())
		{
			ofRectangle absoluteCheckboxRect = ofRectangle(
				button->getChecboxRect().x + button->getPosition().x,
				button->getChecboxRect().y + button->getPosition().y,
				button->getChecboxRect().width,
				button->getChecboxRect().height
			);

			if (absoluteCheckboxRect.inside(x, y)) {
				SetCursor(LoadCursor(NULL, IDC_HAND));

				return;
			}
		}
	}
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button)
{
	SetCursor(LoadCursor(NULL, IDC_SIZEALL));
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button)
{
	checkForCursor(x, y);

	mousePressX = x;
	mousePressY = y;

	if (!toggleDrawLine && !toggleDrawRectangle && !toggleDrawCircle && !toggleDrawEllipse && !toggleDrawTriangle && !toggleDrawCube && !toggleDrawSphere)
	{
		if (selectedAssets.size() == 0)
		{
			Asset* tempAsset = assetManager.getAsset({ x, y, 0 });

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
	checkForCursor(x, y);

	if (mousePressX == x && mousePressY == y)
	{
		return;
	}

    if (toggleDrawLine)
	{
		string shapeName = "line_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addLine(shapeName, { mousePressX, mousePressY, 0 }, { x, y, 0 }, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle2>();
		assetsPanel.add(button.get()->setup("Ligne", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawRectangle)
	{
		string shapeName = "rectangle_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addRectangle(shapeName, { mousePressX, mousePressY, 0 }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle2>();
		assetsPanel.add(button.get()->setup("Rectangle", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawCircle)
	{
		string shapeName = "circle_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addCircle(shapeName, { mousePressX, mousePressY, 0 }, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle2>();
		assetsPanel.add(button.get()->setup("Cercle", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawEllipse)
	{
		string shapeName = "ellipse_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addEllipse(shapeName, { mousePressX, mousePressY, 0 }, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle2>();
		assetsPanel.add(button.get()->setup("Ellipse", true));
		button->addListener(this, &Application::selectedAssetChanged);
		assetsButtons[shapeName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
	}
	else if (toggleDrawTriangle)
	{
		string shapeName = "triangle_" + std::to_string(x) + "_" + std::to_string(y);
		Asset* asset = assetManager.addTriangle(shapeName, { mousePressX, mousePressY, 0 }, { mousePressX + (x - mousePressX) * 0.5f, y, 0 }, { mousePressX - (x - mousePressX) * 0.5f, y, 0 }, lineWidth, fillColorSlider, toggleDrawFill);

		auto button = std::make_shared<ofxToggle2>();
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

		auto button = std::make_shared<ofxToggle2>();
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

		auto button = std::make_shared<ofxToggle2>();
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
				assetManager.setPosition(asset, asset->position + glm::vec3(moveVec.x, moveVec.y, 0));
			}
			else
			{
				assetManager.setPosition(asset, asset->position + moveVec);
			}
		}
	}

	updateBoundingBox();
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
void Application::boundingBoxColorChanged(ofColor& value)
{
	assetManager.boundingBox.color = boundingBoxColorSlider;
}

void Application::boundingBoxLineWidthChanged(int& value)
{
	assetManager.boundingBox.lineWidth = boundingBoxLineWidth;
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
void Application::drawBoundingBoxToggleChanged(bool& value)
{
	if (toggleDrawBoundingBox) {
		updateBoundingBox();
	}

	assetManager.drawBoundingBox = toggleDrawBoundingBox;
}

void Application::updateBoundingBox()
{
	int maxX = INT_MIN, maxY = INT_MIN, maxZ = INT_MIN;
	int minX = INT_MAX, minY = INT_MAX, minZ = INT_MAX;

	for (auto const& [_, asset] : assetManager.assets)
	{
		glm::vec3 maxPos = getMaxPos(asset);

		if (maxPos.x > maxX)
		{
			maxX = maxPos.x;
		}

		if (maxPos.y > maxY)
		{
			maxY = maxPos.y;
		}

		if (maxPos.z > maxZ)
		{
			maxZ = maxPos.z;
		}

		glm::vec3 minPos = getMinPos(asset);

		if (minPos.x < minX)
		{
			minX = minPos.x;
		}

		if (minPos.y < minY)
		{
			minY = minPos.y;
		}

		if (minPos.z < minZ)
		{
			minZ = minPos.z;
		}
	}

	Asset asset;
	asset.width = maxX - minX;
	asset.height = maxY - minY;
	asset.depth = maxZ - minZ;
	asset.position = { minX + asset.width * 0.5f, minY + asset.height * 0.5f, minZ + asset.depth * 0.5f };
	asset.color = boundingBoxColorSlider;
	asset.lineWidth = boundingBoxLineWidth;

	assetManager.boundingBox = asset;
}

glm::vec3 Application::getMaxPos(Asset asset)
{
	int maxX = asset.position.x, maxY = asset.position.y, maxZ = asset.position.z;

	switch (asset.type)
	{
		case AssetType::IMAGE:
		case AssetType::RECTANGLE:
		{
			maxX = std::max(asset.position.x, asset.position.x + asset.width);
			maxY = std::max(asset.position.y, asset.position.y + asset.height);
			maxZ = std::max(asset.position.z, asset.position.z + asset.depth);

			break;
		}
		case AssetType::ELLIPSE:
		{
			float halfWidth = std::abs(asset.width) * 0.5f;
			float halfHeight = std::abs(asset.height) * 0.5f;

			maxX = asset.position.x + halfWidth;
			maxY = asset.position.y + halfHeight;
			maxZ = asset.position.z;

			break;
		}
		case AssetType::CIRCLE:
		{
			float radius = std::abs(asset.radius);

			maxX = asset.position.x + radius;
			maxY = asset.position.y + radius;
			maxZ = asset.position.z;

			break;
		}
		case AssetType::LINE:
		{
			maxX = std::max(asset.position.x, asset.endpoint.x);
			maxY = std::max(asset.position.y, asset.endpoint.y);
			maxZ = std::max(asset.position.z, asset.endpoint.z);

			break;
		}
		case AssetType::TRIANGLE:
		{
			maxX = std::max({ asset.p1.x, asset.p2.x, asset.p3.x });
			maxY = std::max({ asset.p1.y, asset.p2.y, asset.p3.y });
			maxZ = std::max({ asset.p1.z, asset.p2.z, asset.p3.z });

			break;
		}
		case AssetType::CUBE:
		{
			float halfSizeX = std::abs(asset.width) * 0.5f;
			float halfSizeY = std::abs(asset.height) * 0.5f;
			float halfSizeZ = std::abs(asset.depth) * 0.5f;

			maxX = asset.position.x + halfSizeX;
			maxY = asset.position.y + halfSizeY;
			maxZ = asset.position.z + halfSizeZ;

			break;
		}
		case AssetType::SPHERE:
		{
			float radius = std::abs(asset.width);

			maxX = asset.position.x + radius;
			maxY = asset.position.y + radius;
			maxZ = asset.position.z + radius;

			break;
		}
	}

	return { maxX, maxY, maxZ };
}

glm::vec3 Application::getMinPos(Asset asset)
{
	int minX = asset.position.x, minY = asset.position.y, minZ = asset.position.z;

	switch (asset.type)
	{
		case AssetType::IMAGE:
		case AssetType::RECTANGLE:
		{
			minX = std::min(asset.position.x, asset.position.x + asset.width);
			minY = std::min(asset.position.y, asset.position.y + asset.height);
			minZ = std::min(asset.position.z, asset.position.z + asset.depth);

			break;
		}
		case AssetType::ELLIPSE:
		{
			float halfWidth = std::abs(asset.width) * 0.5f;
			float halfHeight = std::abs(asset.height) * 0.5f;

			minX = asset.position.x - halfWidth;
			minY = asset.position.y - halfHeight;
			minZ = asset.position.z;

			break;
		}
		case AssetType::CIRCLE:
		{
			float radius = std::abs(asset.radius);

			minX = asset.position.x - radius;
			minY = asset.position.y - radius;
			minZ = asset.position.z;

			break;
		}
		case AssetType::LINE:
		{
			minX = std::min(asset.position.x, asset.endpoint.x);
			minY = std::min(asset.position.y, asset.endpoint.y);
			minZ = std::min(asset.position.z, asset.endpoint.z);

			break;
		}
		case AssetType::TRIANGLE:
		{
			minX = std::min({ asset.p1.x, asset.p2.x, asset.p3.x });
			minY = std::min({ asset.p1.y, asset.p2.y, asset.p3.y });
			minZ = std::min({ asset.p1.z, asset.p2.z, asset.p3.z });

			break;
		}
		case AssetType::CUBE:
		{
			float halfSizeX = std::abs(asset.width) * 0.5f;
			float halfSizeY = std::abs(asset.height) * 0.5f;
			float halfSizeZ = std::abs(asset.depth) * 0.5f;

			minX = asset.position.x - halfSizeX;
			minY = asset.position.y - halfSizeY;
			minZ = asset.position.z - halfSizeZ;

			break;
		}
		case AssetType::SPHERE:
		{
			float radius = std::abs(asset.width);

			minX = asset.position.x - radius;
			minY = asset.position.y - radius;
			minZ = asset.position.z - radius;

			break;
		}
	}

	return { minX, minY, minZ };
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

	updateBoundingBox();
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

	updateBoundingBox();
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
		assetManager.addImage(imageName, dragInfo.files[i], { dragInfo.position.x, dragInfo.position.y, 0 });

		auto button = std::make_shared<ofxToggle2>();
		assetsPanel.add(button.get()->setup("Image", true));
		assetsButtons[imageName] = button;
	}
}

//--------------------------------------------------------------
void Application::resetButtonPressed()
{
	assetsPanel.clear();

	assetsButtons.clear();

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

	Asset empty;
	assetManager.boundingBox = empty;
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
