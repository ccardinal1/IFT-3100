#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
	gui.setup("Menu");

	gui.setDefaultEventsPriority(OF_EVENT_ORDER_APP);

	pointerGuiPanelElements.push_back(&gui);
	pointerGuiPanelElements.push_back(&assetsPanel);
	pointerGuiPanelElements.push_back(&cameraPanel);

	pointerGuiGroupElements.push_back(&groupDraw);
	pointerGuiGroupElements.push_back(&groupDrawOptions);
	pointerGuiGroupElements.push_back(&groupDrawBoundingBox);
	pointerGuiGroupElements.push_back(&groupGeometry);
	pointerGuiGroupElements.push_back(&groupGeometryOptions);
	pointerGuiGroupElements.push_back(&groupCamera);
	pointerGuiGroupElements.push_back(&groupCameraProjection);

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
	pointerGuiToggleElements.push_back(&togglePerspective);
	pointerGuiToggleElements.push_back(&toggleOrtho);

	pointerGuiIntSliderElements.push_back(&lineWidth);
	pointerGuiIntSliderElements.push_back(&boundingBoxLineWidth);
	pointerGuiIntSliderElements.push_back(&geometryRotateX);
	pointerGuiIntSliderElements.push_back(&geometryRotateY);

	pointerGuiColorSliderElements.push_back(&fillColorSlider);
	pointerGuiColorSliderElements.push_back(&boundingBoxColorSlider);
	pointerGuiColorSliderElements.push_back(&backgroundColorSlider);

	assetsPanel.setup("Graphe de scene");
	assetsPanel.setPosition(ofGetWindowWidth() - assetsPanel.getWidth() - 10, 10);

	cameraPanel.setup();
	cameraPanel.setName("Camera");
	cameraPanel.setPosition(assetsPanel.getPosition().x, assetsPanel.getPosition().y + assetsPanel.getHeight() + 500);

	cameraPanel.add(lblCamActive.setup("", "Camera active: 1"));

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
	groupCameraProjection.setup("Mode de projection");
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
	groupDrawOptions.add(lineWidth.setup("Epaisseur", 1, 1, 10));

	ofParameter<ofColor> colorParam = ofParameter<ofColor>("Couleur", ofColor(255, 255, 255), ofColor(0, 0), ofColor(255, 255));

	colorParam.addListener(this, &Application::drawColorChanged);

	groupDrawOptions.add(fillColorSlider.setup(colorParam));

	toggleDrawBoundingBox.addListener(this, &Application::drawBoundingBoxToggleChanged);

	groupDrawBoundingBox.add(toggleDrawBoundingBox.setup("Activer", false));

	groupDrawBoundingBox.add(boundingBoxLineWidth.setup("Epaisseur", 2, 1, 10));

	ofParameter<ofColor> boundingBoxColorParam = ofParameter<ofColor>("Couleur", ofColor(255, 0, 0), ofColor(0, 0), ofColor(255, 255));
	boundingBoxColorParam.addListener(this, &Application::boundingBoxColorChanged);
	groupDrawBoundingBox.add(boundingBoxColorSlider.setup(boundingBoxColorParam));
	groupDrawBoundingBox.minimize();

	groupDrawOptions.add(&groupDrawBoundingBox);

	groupDraw.add(&groupDrawOptions);

	toggleDrawCube.addListener(this, &Application::drawCubeToggleChanged);
	groupGeometry.add(toggleDrawCube.setup("Cube", false));

	toggleDrawSphere.addListener(this, &Application::drawSphereToggleChanged);
	groupGeometry.add(toggleDrawSphere.setup("Sphere", false));

	groupGeometryOptions.add(geometryRotateX.setup("Rotation X", 0, 0, 360));
	groupGeometryOptions.add(geometryRotateY.setup("Rotation Y", 0, 0, 360));
	groupGeometry.add(&groupGeometryOptions);
	groupGeometryOptions.minimize();

	groupCameraProjection.add(togglePerspective.setup("Perspective", true));
	groupCameraProjection.add(toggleOrtho.setup("Orthogonale", false));

	togglePerspective.addListener(this, &Application::togglePerspectiveChanged);
	toggleOrtho.addListener(this, &Application::toggleOrthoChanged);

	gui.add(&groupDraw);
	gui.add(&groupGeometry);
	gui.add(backgroundColorSlider.setup("Arriere-Plan", ofColor(100, 100, 100), ofColor(0, 0), ofColor(255, 255)));

	cameraPanel.add(&groupCameraProjection);

	assetsPanel.add(deleteButton.setup("Supprimer"));

	assetManager.assets.clear();

	for (int i = 0; i < 3; i++)
	{
		cameras.push_back(std::make_unique<ofEasyCam>());
		cameras[i]->setTarget({ ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 300 });
		cameras[i]->setDistance(300);
		cameras[i]->disableMouseMiddleButton();
		cameras[i]->disableMouseInput();
		cameras[i]->disableOrtho();
	}

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
	cameras[activeCamIndex]->begin();
	ofEnableDepthTest();

	if (cameras[activeCamIndex]->getMouseInputEnabled())
	{
		ofDrawGrid(10);
	}

	assetManager.draw();

	ofDisableDepthTest();
	cameras[activeCamIndex]->end();

	gui.draw();
	assetsPanel.draw();
	cameraPanel.draw();
}

//--------------------------------------------------------------
void Application::keyPressed(int key)
{
	if (key == 32)
	{
		cameras[activeCamIndex]->enableMouseInput();
		resetToggles();
	}
}

//--------------------------------------------------------------
void Application::keyReleased(int key)
{
	switch (key)
	{
	case 32:
		cameras[activeCamIndex]->disableMouseInput();
		break;
	case 49:
	case 50:
	case 51:
		if (key - 49 != activeCamIndex)
		{
			activeCamIndex = key - 49;

			lblCamActive = "Camera active: " + ofToString(activeCamIndex + 1);

			togglePerspective = !cameras[activeCamIndex]->getOrtho();
		}
		break;
	}
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
	if (!gui.getShape().inside(x, y) && !clickedInUi)
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
	}
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button)
{
	mousePressX = x;
	mousePressY = y;

	if (!gui.getShape().inside(x, y))
	{
		if (button != 0 || cameras[activeCamIndex]->getMouseInputEnabled())
			return;

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
	else
	{
		clickedInUi = true;
	}
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
	if (button != 0 || (mousePressX == x && mousePressY == y) || cameras[activeCamIndex]->getMouseInputEnabled())
	{
		clickedInUi = false;
		return;
	}

	if (!clickedInUi)
	{
		checkForCursor(x, y);

		Asset* asset = nullptr;
		string buttonName = "";

		if (toggleDrawLine)
		{
			string shapeName = "line_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addLine(shapeName, cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, 0 }), { x, y, 0 }, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Ligne";
		}
		else if (toggleDrawRectangle)
		{
			string shapeName = "rectangle_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addRectangle(shapeName, cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, 0 }), x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Rectangle";
		}
		else if (toggleDrawCircle)
		{
			string shapeName = "circle_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addCircle(shapeName, cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, 0 }), x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Cercle";
		}
		else if (toggleDrawEllipse)
		{
			string shapeName = "ellipse_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addEllipse(shapeName, cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, 0 }), x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Ellipse";
		}
		else if (toggleDrawTriangle)
		{
			string shapeName = "triangle_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addTriangle(shapeName, cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, 0 }), { mousePressX + (x - mousePressX) / 2, y, 0 }, { mousePressX - (x - mousePressX) / 2, y, 0 }, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Triangle";
		}
		else if (toggleDrawCube)
		{
			string shapeName = "cube_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addCube(shapeName, cameras[activeCamIndex]->screenToWorld({ x, y, 0 }), x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Cube";
		}
		else if (toggleDrawSphere)
		{
			string shapeName = "sphere_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addSphere(shapeName, cameras[activeCamIndex]->screenToWorld({ x, y, 0 }), x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Sphere";
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

		if (asset != nullptr)
		{
			auto button = std::make_shared<ofxToggle2>();
			assetsPanel.add(button.get()->setup(buttonName, true));
			button->addListener(this, &Application::selectedAssetChanged);
			assetsButtons[asset->name] = button;

			asset->isSelected = true;
			selectedAssets.push_back(asset);

			cameras[activeCamIndex]->setTarget(asset->position);
			cameras[activeCamIndex]->setDistance(300);
		}
	}
	else
	{
		clickedInUi = false;
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

void Application::setCameraTargetOnSelectedAssets()
{
	ofVec3f minBounds(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f maxBounds(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	if (selectedAssets.size() == 0)
	{
		cameras[activeCamIndex]->setTarget({ 0, 0, 0 });
		cameras[activeCamIndex]->setDistance(300);
	}
	else
	{
		for (Asset* asset : selectedAssets)
		{
			minBounds.x = std::min(minBounds.x, asset->position.x);
			minBounds.y = std::min(minBounds.y, asset->position.y);
			minBounds.z = std::min(minBounds.z, asset->position.z);

			maxBounds.x = std::max(maxBounds.x, asset->position.x);
			maxBounds.y = std::max(maxBounds.y, asset->position.y);
			maxBounds.z = std::max(maxBounds.z, asset->position.z);
		}

		ofVec3f center = (minBounds + maxBounds) * 0.5;
		float radius = (maxBounds - minBounds).length() * 0.5;

		float fov = ofDegToRad(cameras[activeCamIndex]->getFov());
		float distance = radius / std::tan(fov / 2.0);

		distance = std::max(300.0f, distance);

		ofVec3f camPos = center + ofVec3f(0, 0, distance);
		cameras[activeCamIndex]->setPosition(camPos);
		cameras[activeCamIndex]->lookAt(center);
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

			ofLog(OF_LOG_NOTICE, "selected asset pos: " + ofToString(asset->position));

			if (selectedAssets.size() == 0)
			{
				toggleDrawFill = asset->isFilled;
				fillColorSlider = asset->color;
				lineWidth = asset->lineWidth;

				if (asset->geometryPrimitive.getMesh().getNumVertices() > 0)
				{
					geometryRotateX = asset->geometryPrimitive.getPitchDeg();
					geometryRotateY = asset->geometryPrimitive.getHeadingDeg();

					cameras[activeCamIndex]->setTarget(asset->position);
					cameras[activeCamIndex]->setDistance(300);
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

	setCameraTargetOnSelectedAssets();
}

void Application::togglePerspectiveChanged(bool& value)
{
	toggleOrtho = !value;
}

void Application::toggleOrthoChanged(bool& value)
{
	if (value)
	{
		cameras[activeCamIndex]->enableOrtho();
		togglePerspective = false;
	}
	else
	{
		cameras[activeCamIndex]->disableOrtho();
		togglePerspective = true;
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
