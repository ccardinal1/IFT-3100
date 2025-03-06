#include "application.h"

//--------------------------------------------------------------
void Application::setup()
{
	gui.setup("Menu");

	gui.setDefaultEventsPriority(OF_EVENT_ORDER_APP);

	pointerGuiPanelElements.push_back(&gui);
	pointerGuiPanelElements.push_back(&assetsPanel);
	pointerGuiPanelElements.push_back(&cameraPanel);
	pointerGuiPanelElements.push_back(&objectPanel);

	pointerGuiGroupElements.push_back(&groupDraw);
	pointerGuiGroupElements.push_back(&groupDrawOptions);
	pointerGuiGroupElements.push_back(&groupDrawBoundingBox);
	pointerGuiGroupElements.push_back(&groupGeometry);
	//pointerGuiGroupElements.push_back(&groupGeometryOptions);
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
	//pointerGuiIntSliderElements.push_back(&geometryRotateX);
	//pointerGuiIntSliderElements.push_back(&geometryRotateY);

	pointerGuiColorSliderElements.push_back(&fillColorSlider);
	pointerGuiColorSliderElements.push_back(&boundingBoxColorSlider);
	pointerGuiColorSliderElements.push_back(&backgroundColorSlider);

	pointerGuiFloatFieldElements.push_back(&translateXField);
	pointerGuiFloatFieldElements.push_back(&translateYField);
	pointerGuiFloatFieldElements.push_back(&translateZField);
	pointerGuiFloatFieldElements.push_back(&rotateXField);
	pointerGuiFloatFieldElements.push_back(&rotateYField);
	pointerGuiFloatFieldElements.push_back(&rotateZField);
	pointerGuiFloatFieldElements.push_back(&scaleXField);
	pointerGuiFloatFieldElements.push_back(&scaleYField);
	pointerGuiFloatFieldElements.push_back(&scaleZField);

	pointerGuiFloatSliderElements.push_back(&translateXSlider);
	pointerGuiFloatSliderElements.push_back(&translateYSlider);
	pointerGuiFloatSliderElements.push_back(&translateZSlider);
	pointerGuiFloatSliderElements.push_back(&rotateXSlider);
	pointerGuiFloatSliderElements.push_back(&rotateYSlider);
	pointerGuiFloatSliderElements.push_back(&rotateZSlider);
	pointerGuiFloatSliderElements.push_back(&scaleXSlider);
	pointerGuiFloatSliderElements.push_back(&scaleYSlider);
	pointerGuiFloatSliderElements.push_back(&scaleZSlider);

	assetsPanel.setup("Graphe de scene");
	assetsPanel.setPosition(ofGetWindowWidth() - assetsPanel.getWidth() - 10, 10);

	cameraPanel.setup();
	cameraPanel.setName("Camera");
	cameraPanel.setWidthElements(220);
	cameraPanel.setPosition(ofGetWindowWidth() - cameraPanel.getWidth() - 10, assetsPanel.getPosition().y + assetsPanel.getHeight() + 500);

	objectPanel.setup("Item(s) selectionne(s)");
	objectPanel.setPosition(assetsPanel.getPosition().x - assetsPanel.getWidth() - 10, assetsPanel.getPosition().y);

	cameraPanel.add(lblCamActive.setup("", "Camera active: 1"));

	resetButton.addListener(this, &Application::resetButtonPressed);
	histogramButton.addListener(this, &Application::histogramButtonPressed);
	deleteButton.addListener(this, &Application::deleteButtonPressed);
	toggleDrawFill.addListener(this, &Application::isFilledToggleChanged);
	lineWidth.addListener(this, &Application::lineWidthChanged);
	boundingBoxLineWidth.addListener(this, &Application::boundingBoxLineWidthChanged);

	//geometryRotateX.addListener(this, &Application::geometryRotateXChanged);
	//geometryRotateY.addListener(this, &Application::geometryRotateYChanged);

	translateXField.addListener(this, &Application::positionXChanged);
	translateXSlider.addListener(this, &Application::translateXChanged);
	translateYField.addListener(this, &Application::positionYChanged);
	translateYSlider.addListener(this, &Application::translateYChanged);
	translateZField.addListener(this, &Application::positionZChanged);
	translateZSlider.addListener(this, &Application::translateZChanged);
	rotateXField.addListener(this, &Application::angleXChanged);
	rotateXSlider.addListener(this, &Application::rotateXChanged);
	rotateYField.addListener(this, &Application::angleYChanged);
	rotateYSlider.addListener(this, &Application::rotateYChanged);
	rotateZField.addListener(this, &Application::angleZChanged);
	rotateZSlider.addListener(this, &Application::rotateZChanged);
	scaleXField.addListener(this, &Application::scaleXChanged);
	scaleXSlider.addListener(this, &Application::growthXChanged);
	scaleYField.addListener(this, &Application::scaleYChanged);
	scaleYSlider.addListener(this, &Application::growthYChanged);
	scaleZField.addListener(this, &Application::scaleZChanged);
	scaleZSlider.addListener(this, &Application::growthZChanged);

	gui.add(resetButton.setup("Reinitialiser"));
	gui.add(histogramButton.setup("Histogramme"));

	groupDraw.setup("Outils de dessin");
	groupDrawOptions.setup("Options");
	groupGeometry.setup("Geometrie");
	//groupGeometryOptions.setup("Options");
	groupCameraProjection.setup("Mode de projection");
	groupDrawBoundingBox.setup("Boite de delimitation");
	groupTranslation.setup("Translation");
	groupRotation.setup("Rotation");
	groupScale.setup("Echelle");

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

	toggleAddModel1.addListener(this, &Application::drawModel1ToggleChanged);
	groupGeometry.add(toggleAddModel1.setup("Modele 1", false));

	toggleAddModel2.addListener(this, &Application::drawModel2ToggleChanged);
	groupGeometry.add(toggleAddModel2.setup("Modele 2", false));

	toggleAddModel3.addListener(this, &Application::drawModel3ToggleChanged);
	groupGeometry.add(toggleAddModel3.setup("Modele 3", false));

	//groupGeometryOptions.add(geometryRotateX.setup("Rotation X", 0, 0, 360));
	//groupGeometryOptions.add(geometryRotateY.setup("Rotation Y", 0, 0, 360));
	//groupGeometry.add(&groupGeometryOptions);
	//groupGeometryOptions.minimize();

	groupCameraProjection.add(togglePerspective.setup("Perspective", true));
	groupCameraProjection.add(toggleOrtho.setup("Orthogonale", false));

	groupTranslation.add(translateXField.setup("Position X", 0.0f, -10000000.0f, 10000000.0f));
	groupTranslation.add(translateYField.setup("Position Y", 0.0f, -10000000.0f, 10000000.0f));
	groupTranslation.add(translateZField.setup("Position Z", 0.0f, -10000000.0f, 10000000.0f));
	groupTranslation.add(translateXSlider.setup("Translation X", 0.0f, -30.0f, 30.0f));
	groupTranslation.add(translateYSlider.setup("Translation Y", 0.0f, -30.0f, 30.0f));
	groupTranslation.add(translateZSlider.setup("Translation Z", 0.0f, -30.0f, 30.0f));
	groupRotation.add(rotateXField.setup("Angle X", 0.0f, 0.0f, 360.0f));
	groupRotation.add(rotateYField.setup("Angle Y", 0.0f, 0.0f, 360.0f));
	groupRotation.add(rotateZField.setup("Angle Z", 0.0f, 0.0f, 360.0f));
	groupRotation.add(rotateXSlider.setup("Rotation X", 0.0f, -180.0f, 180.0f));
	groupRotation.add(rotateYSlider.setup("Rotation Y", 0.0f, -180.0f, 180.0f));
	groupRotation.add(rotateZSlider.setup("Rotation Z", 0.0f, -180.0f, 180.0f));
	groupScale.add(scaleXField.setup("Echelle X", 1.0f, -30.0f, 30.0f));
	groupScale.add(scaleYField.setup("Echelle Y", 1.0f, -30.0f, 30.0f));
	groupScale.add(scaleZField.setup("Echelle Z", 1.0f, -30.0f, 30.0f));
	groupScale.add(scaleXSlider.setup("Agrand. X", 0.0f, -10.0f, 10.0f));
	groupScale.add(scaleYSlider.setup("Agrand. Y", 0.0f, -10.0f, 10.0f));
	groupScale.add(scaleZSlider.setup("Agrand. Z", 0.0f, -10.0f, 10.0f));

	togglePerspective.addListener(this, &Application::togglePerspectiveChanged);
	toggleOrtho.addListener(this, &Application::toggleOrthoChanged);
	toggleCenterOnSelection.addListener(this, &Application::toggleCenterOnSelectionChanged);

	gui.add(&groupDraw);
	gui.add(&groupGeometry);
	gui.add(backgroundColorSlider.setup("Arriere-Plan", ofColor(100, 100, 100), ofColor(0, 0), ofColor(255, 255)));

	cameraPanel.add(toggleCenterOnSelection.setup("Centrer sur la selection", false));
	cameraPanel.add(&groupCameraProjection);

	assetsPanel.add(deleteButton.setup("Supprimer"));

	objectPanel.add(&groupTranslation);
	objectPanel.add(&groupRotation);
	objectPanel.add(&groupScale);

	objectPanel.minimize();

	assetManager.assets.clear();

	for (int i = 0; i < 3; i++)
	{
		cameras.push_back(std::make_unique<ofEasyCam>());
		cameras[i]->disableMouseMiddleButton();
		cameras[i]->disableMouseInput();
		cameras[i]->disableOrtho();
		cameras[i]->setPosition(0, 0, 779);
	}

	ofSetFrameRate(60);
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
		ofDrawGrid(10, 20, true);
	}

	assetManager.draw();
	if (recording || screenshot) {
		exportImage();
		if (screenshot) screenshot = false;
	}

	ofDisableDepthTest();

	cameras[activeCamIndex]->end();

	gui.draw();
	assetsPanel.draw();
	cameraPanel.draw();
	if (selectedAssets.size() == 1) objectPanel.draw();
	if (recording) {
		ofSetColor(255, 0, 0);
		ofFill();
		ofDrawCircle(18, 18, 16);
	}
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
	case 111:
		recording = !recording;
		if (recording) {
			ofSetFrameRate(6);
			imageIndex = 0;
		}
		else ofSetFrameRate(60);
		break;
	case 112:
		screenshot = true;
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

	for (auto& button : pointerGuiFloatFieldElements) {
		if (button->getShape().inside(x, y)) {
			SetCursor(LoadCursor(NULL, IDC_IBEAM));

			return;
		}
	}

	for (auto& button : pointerGuiFloatSliderElements) {
		if (button->getShape().inside(x, y)) {
			SetCursor(LoadCursor(NULL, IDC_HAND));

			return;
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
	if (button != 0 || ((mousePressX == x && mousePressY == y) && !(toggleAddModel1 || toggleAddModel2 || toggleAddModel3)) || cameras[activeCamIndex]->getMouseInputEnabled())
	{
		clickedInUi = false;
		return;
	}

	if (!clickedInUi)
	{
		checkForCursor(x, y);

		Asset* asset = nullptr;
		string buttonName = "";
		glm::vec3 screenZero = cameras[activeCamIndex]->worldToScreen(glm::vec3(0, 0, 0));
		glm::vec3 assetPosition = cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, screenZero.z });

		if (toggleDrawLine)
		{
			string shapeName = "line_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addLine(shapeName, assetPosition, cameras[activeCamIndex]->screenToWorld({ x, y, screenZero.z }), lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Ligne";
		}
		else if (toggleDrawRectangle)
		{
			string shapeName = "rectangle_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addRectangle(shapeName, assetPosition, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Rectangle";
		}
		else if (toggleDrawCircle)
		{
			string shapeName = "circle_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addCircle(shapeName, assetPosition, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Cercle";
		}
		else if (toggleDrawEllipse)
		{
			string shapeName = "ellipse_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addEllipse(shapeName, assetPosition, x - mousePressX, y - mousePressY, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Ellipse";
		}
		else if (toggleDrawTriangle)
		{
			string shapeName = "triangle_" + std::to_string(x) + "_" + std::to_string(y);

			glm::vec3 p1 = cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, screenZero.z });
			glm::vec3 p2 = cameras[activeCamIndex]->screenToWorld({ mousePressX + (x - mousePressX) / 2, y, screenZero.z });
			glm::vec3 p3 = cameras[activeCamIndex]->screenToWorld({ mousePressX - (x - mousePressX) / 2, y, screenZero.z });

			asset = assetManager.addTriangle(shapeName, p1, p2, p3, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Triangle";
		}
		else if (toggleDrawCube)
		{
			string shapeName = "cube_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addCube(shapeName, assetPosition, x - mousePressX, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Cube";
		}
		else if (toggleDrawSphere)
		{
			string shapeName = "sphere_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addSphere(shapeName, assetPosition, (x - mousePressX) / 2, lineWidth, fillColorSlider, toggleDrawFill);

			buttonName = "Sphere";
		}
		else if (toggleAddModel1)
		{
			string shapeName = "model1_" + std::to_string(x) + "_" + std::to_string(y);

			asset = assetManager.add3dModel(shapeName, assetPosition, "set-of-plants-3d-model\\Little plant\\littlePlant.obj");

			asset->model.setScale(0.25, 0.25, 0.25);
			asset->model.setRotation(0, 180, 1, 0, 0);

			buttonName = "Plante 1";
		}
		else if (toggleAddModel2)
		{
			string shapeName = "model2_" + std::to_string(x) + "_" + std::to_string(y);

			asset = assetManager.add3dModel(shapeName, assetPosition, "set-of-plants-3d-model\\Yucca\\yuccaPlant.obj");

			asset->model.setRotation(0, 180, 1, 0, 0);

			buttonName = "Plante 2";
		}
		else if (toggleAddModel3)
		{
			string shapeName = "model3_" + std::to_string(x) + "_" + std::to_string(y);

			asset = assetManager.add3dModel(shapeName, assetPosition, "set-of-plants-3d-model\\eb_house_plant_02\\eb_house_plant_02.obj");

			asset->model.setScale(0.5, 0.5, 0.5);
			asset->model.setRotation(0, 180, 1, 0, 0);

			buttonName = "Plante 3";
		}
		else if (!selectedAssets.empty())
		{
			glm::vec3 moveVec = cameras[activeCamIndex]->screenToWorld({ x, y, screenZero.z }) - assetPosition;

			for (Asset* asset : selectedAssets)
			{
				assetManager.setPosition(asset, asset->position + moveVec);
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
			bool tmp = true;
			selectedAssets.push_back(asset);
			selectedAssetChanged(tmp);

			resetToggles();
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

void Application::drawModel1ToggleChanged(bool& value)
{
	if (toggleAddModel1)
	{
		clearSelectedAssets();
		resetToggles();
		toggleAddModel1 = true;
	}
}

void Application::drawModel2ToggleChanged(bool& value)
{
	if (toggleAddModel2)
	{
		clearSelectedAssets();
		resetToggles();
		toggleAddModel2 = true;
	}
}

void Application::drawModel3ToggleChanged(bool& value)
{
	if (toggleAddModel3)
	{
		clearSelectedAssets();
		resetToggles();
		toggleAddModel3 = true;
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

	for (auto& [_, asset] : assetManager.assets)
	{
		glm::vec3 maxPos = getMaxPos(&asset);

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

		glm::vec3 minPos = getMinPos(&asset);

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

	assetManager.boundingBox.width = maxX - minX;
	assetManager.boundingBox.height = maxY - minY;
	assetManager.boundingBox.depth = maxZ - minZ;
	assetManager.boundingBox.position = { minX + assetManager.boundingBox.width * 0.5f, minY + assetManager.boundingBox.width * 0.5f, minZ + assetManager.boundingBox.width * 0.5f };
	assetManager.boundingBox.color = boundingBoxColorSlider;
	assetManager.boundingBox.lineWidth = boundingBoxLineWidth;

}

glm::vec3 Application::getMaxPos(Asset* asset)
{
	int maxX = asset->position.x, maxY = asset->position.y, maxZ = asset->position.z;

	switch (asset->type)
	{
	case AssetType::IMAGE:
	case AssetType::RECTANGLE:
	{
		maxX = std::max(asset->position.x, asset->position.x + asset->width);
		maxY = std::max(asset->position.y, asset->position.y + asset->height);
		maxZ = std::max(asset->position.z, asset->position.z + asset->depth);

		break;
	}
	case AssetType::ELLIPSE:
	{
		float halfWidth = std::abs(asset->width) * 0.5f;
		float halfHeight = std::abs(asset->height) * 0.5f;

		maxX = asset->position.x + halfWidth;
		maxY = asset->position.y + halfHeight;
		maxZ = asset->position.z;

		break;
	}
	case AssetType::CIRCLE:
	{
		float radius = std::abs(asset->radius);

		maxX = asset->position.x + radius;
		maxY = asset->position.y + radius;
		maxZ = asset->position.z;

		break;
	}
	case AssetType::LINE:
	{
		maxX = std::max(asset->position.x, asset->endpoint.x);
		maxY = std::max(asset->position.y, asset->endpoint.y);
		maxZ = std::max(asset->position.z, asset->endpoint.z);

		break;
	}
	case AssetType::TRIANGLE:
	{
		maxX = std::max({ asset->p1.x, asset->p2.x, asset->p3.x });
		maxY = std::max({ asset->p1.y, asset->p2.y, asset->p3.y });
		maxZ = std::max({ asset->p1.z, asset->p2.z, asset->p3.z });

		break;
	}
	case AssetType::CUBE:
	{
		float halfSizeX = std::abs(asset->width) * 0.5f;
		float halfSizeY = std::abs(asset->height) * 0.5f;
		float halfSizeZ = std::abs(asset->depth) * 0.5f;

		maxX = asset->position.x + halfSizeX;
		maxY = asset->position.y + halfSizeY;
		maxZ = asset->position.z + halfSizeZ;

		break;
	}
	case AssetType::SPHERE:
	{
		float radius = std::abs(asset->width);

		maxX = asset->position.x + radius;
		maxY = asset->position.y + radius;
		maxZ = asset->position.z + radius;

		break;
	}
	}

	return { maxX, maxY, maxZ };
}

glm::vec3 Application::getMinPos(Asset* asset)
{
	int minX = asset->position.x, minY = asset->position.y, minZ = asset->position.z;

	switch (asset->type)
	{
	case AssetType::IMAGE:
	case AssetType::RECTANGLE:
	{
		minX = std::min(asset->position.x, asset->position.x + asset->width);
		minY = std::min(asset->position.y, asset->position.y + asset->height);
		minZ = std::min(asset->position.z, asset->position.z + asset->depth);

		break;
	}
	case AssetType::ELLIPSE:
	{
		float halfWidth = std::abs(asset->width) * 0.5f;
		float halfHeight = std::abs(asset->height) * 0.5f;

		minX = asset->position.x - halfWidth;
		minY = asset->position.y - halfHeight;
		minZ = asset->position.z;

		break;
	}
	case AssetType::CIRCLE:
	{
		float radius = std::abs(asset->radius);

		minX = asset->position.x - radius;
		minY = asset->position.y - radius;
		minZ = asset->position.z;

		break;
	}
	case AssetType::LINE:
	{
		minX = std::min(asset->position.x, asset->endpoint.x);
		minY = std::min(asset->position.y, asset->endpoint.y);
		minZ = std::min(asset->position.z, asset->endpoint.z);

		break;
	}
	case AssetType::TRIANGLE:
	{
		minX = std::min({ asset->p1.x, asset->p2.x, asset->p3.x });
		minY = std::min({ asset->p1.y, asset->p2.y, asset->p3.y });
		minZ = std::min({ asset->p1.z, asset->p2.z, asset->p3.z });

		break;
	}
	case AssetType::CUBE:
	{
		float halfSizeX = std::abs(asset->width) * 0.5f;
		float halfSizeY = std::abs(asset->height) * 0.5f;
		float halfSizeZ = std::abs(asset->depth) * 0.5f;

		minX = asset->position.x - halfSizeX;
		minY = asset->position.y - halfSizeY;
		minZ = asset->position.z - halfSizeZ;

		break;
	}
	case AssetType::SPHERE:
	{
		float radius = std::abs(asset->width);

		minX = asset->position.x - radius;
		minY = asset->position.y - radius;
		minZ = asset->position.z - radius;

		break;
	}
	}

	return { minX, minY, minZ };
}

void Application::setCameraTargetOnSelectedAssets(bool value)
{
	if (cameras.size() == 0)
		return;

	ofVec3f minBounds(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f maxBounds(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	if (selectedAssets.size() == 0 || !toggleCenterOnSelection)
	{
		cameras[activeCamIndex]->setPosition(0, 0, 779);
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


		ofVec3f camPos = center + ofVec3f(0, 0, distance);
		cameras[activeCamIndex]->setPosition(camPos);
		cameras[activeCamIndex]->lookAt(center);
	}
}

//--------------------------------------------------------------
/*void Application::geometryRotateXChanged(int& value)
{
	for (Asset* asset : selectedAssets)
	{
		if (asset->type == AssetType::CUBE)
		{
			assetManager.rotateX(asset, value);
		}
	}

	updateBoundingBox();
}*/

//--------------------------------------------------------------
/*void Application::geometryRotateYChanged(int& value)
{
	for (Asset* asset : selectedAssets)
	{
		if (asset->type == AssetType::CUBE)
		{
			assetManager.rotateY(asset, value);
		}
	}

	updateBoundingBox();
}*/

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
					//geometryRotateX = asset->geometryPrimitive.getPitchDeg();
					//geometryRotateY = asset->geometryPrimitive.getHeadingDeg();
				}
				else
				{
					//geometryRotateX = 0;
					//geometryRotateY = 0;
				}
			}

			selectedAssets.push_back(asset);
		}
	}

	if (toggleCenterOnSelection)
	{
		setCameraTargetOnSelectedAssets(true);
	}
	if (selectedAssets.size() == 1) {
		translateXField.setup("Position X", selectedAssets[0]->position.x);
		translateYField.setup("Position Y", selectedAssets[0]->position.y);
		translateZField.setup("Position Z", selectedAssets[0]->position.z);
		if (!groupTranslation.isMinimized()) {
			groupTranslation.minimize();
			groupTranslation.maximize();
		}
		//TODO
	}
}

void Application::positionXChanged(float& value) {
	//TODO
}

void Application::positionYChanged(float& value) {
	//TODO
}

void Application::positionZChanged(float& value) {
	//TODO
}

void Application::translateXChanged(float& value) {
	// TODO
}

void Application::translateYChanged(float& value) {
	// TODO
}

void Application::translateZChanged(float& value) {
	// TODO
}

void Application::angleXChanged(float& value) {
	//TODO
}

void Application::angleYChanged(float& value) {
	//TODO
}

void Application::angleZChanged(float& value) {
	//TODO
}

void Application::rotateXChanged(float& value) {
	//TODO
}

void Application::rotateYChanged(float& value) {
	//TODO
}

void Application::rotateZChanged(float& value) {
	//TODO
}

void Application::scaleXChanged(float& value) {
	//TODO
}

void Application::scaleYChanged(float& value) {
	//TODO
}

void Application::scaleZChanged(float& value) {
	//TODO
}

void Application::growthXChanged(float& value) {
	//TODO
}

void Application::growthYChanged(float& value) {
	//TODO
}

void Application::growthZChanged(float& value) {
	//TODO
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

void Application::toggleCenterOnSelectionChanged(bool& value)
{
	if (cameras.size() == 0)
		return;

	if (value)
	{
		setCameraTargetOnSelectedAssets(value);
	}
	else
	{
		cameras[activeCamIndex]->setPosition(0, 0, 779);
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
	clearSelectedAssets();
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

	bool tmp = true;
	selectedAssetChanged(tmp);

	//Asset empty;
	//assetManager.boundingBox = empty;
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

	toggleAddModel1 = false;
	toggleAddModel2 = false;
	toggleAddModel3 = false;
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

void Application::exportImage() {
	ofImage image;
	string fileName;
	if (recording) {
		fileName = "image_export_" + ofGetTimestampString("%F-%H-%M-%S") + "_" + std::to_string(imageIndex) + ".png";
		imageIndex++;
	}
	else fileName = "image_export_" + ofGetTimestampString("%F-%H-%M-%S") + ".png";
	ofLog(OF_LOG_NOTICE, "Image export�e vers /bin/data/" + fileName);
	image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	image.save(fileName);
}
