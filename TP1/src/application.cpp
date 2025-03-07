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
	pointerGuiGroupElements.push_back(&groupHSBFillColor);
	pointerGuiGroupElements.push_back(&groupHSBBoundingBoxColor);
	pointerGuiGroupElements.push_back(&groupHSBBackgroundColor);

	pointerGuiButtonElements.push_back(&resetButton);
	pointerGuiButtonElements.push_back(&histogramButton);
	pointerGuiButtonElements.push_back(&deleteButton);
	pointerGuiButtonElements.push_back(&instanceButton);

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

	pointerGuiColorSliderElements.push_back(&RGBAFillColorSlider);
	pointerGuiColorSliderElements.push_back(&RGBABoundingBoxColorSlider);
	pointerGuiColorSliderElements.push_back(&RGBABackgroundColorSlider);

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
	pointerGuiFloatSliderElements.push_back(&HFillColorSlider);
	pointerGuiFloatSliderElements.push_back(&SFillColorSlider);
	pointerGuiFloatSliderElements.push_back(&BFillColorSlider);
	pointerGuiFloatSliderElements.push_back(&HBoundingBoxColorSlider);
	pointerGuiFloatSliderElements.push_back(&SBoundingBoxColorSlider);
	pointerGuiFloatSliderElements.push_back(&BBoundingBoxColorSlider);
	pointerGuiFloatSliderElements.push_back(&HBackgroundColorSlider);
	pointerGuiFloatSliderElements.push_back(&SBackgroundColorSlider);
	pointerGuiFloatSliderElements.push_back(&BBackgroundColorSlider);

	assetsPanel.setup("Graphe de scene");
	assetsPanel.setPosition(ofGetWindowWidth() - assetsPanel.getWidth() - 10, 10);

	cameraPanel.setup("Camera");
	cameraPanel.setWidthElements(220);
	cameraPanel.setPosition(ofGetWindowWidth() - cameraPanel.getWidth() - 10, assetsPanel.getPosition().y + assetsPanel.getHeight() + 500);

	objectPanel.setup("Item(s) selectionne(s)");
	objectPanel.setPosition(assetsPanel.getPosition().x - assetsPanel.getWidth() - 10, assetsPanel.getPosition().y);
	
	cameraPanel.add(lblCamActive.setup("", "Camera active: 1"));

	resetButton.addListener(this, &Application::resetButtonPressed);
	histogramButton.addListener(this, &Application::histogramButtonPressed);
	deleteButton.addListener(this, &Application::deleteButtonPressed);
	instanceButton.addListener(this, &Application::instanceButtonPressed);
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
	rotateYField.addListener(this, &Application::angleYChanged);
	rotateZField.addListener(this, &Application::angleZChanged);
	rotateXSlider.addListener(this, &Application::rotateXChanged);
	rotateYSlider.addListener(this, &Application::rotateYChanged);
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
	colorParam.addListener(this, &Application::RGBADrawColorChanged);

	groupHSBFillColor.setup("HSB color");

	HFillColorSlider.addListener(this, &Application::HSBDrawColorChanged);
	SFillColorSlider.addListener(this, &Application::HSBDrawColorChanged);
	BFillColorSlider.addListener(this, &Application::HSBDrawColorChanged);

	groupHSBFillColor.add(HFillColorSlider.setup("Hue", 0.0f, 0.0f, 360.0f));
	groupHSBFillColor.add(SFillColorSlider.setup("Saturation", 0.0f, 0.0f, 100.0f));
	groupHSBFillColor.add(BFillColorSlider.setup("Brightness", 100.0f, 0.0f, 100.0f));

	groupHSBFillColor.minimize();

	groupDrawOptions.add(&groupHSBFillColor);

	groupDrawOptions.add(RGBAFillColorSlider.setup(colorParam));

	toggleDrawBoundingBox.addListener(this, &Application::drawBoundingBoxToggleChanged);

	groupDrawBoundingBox.add(toggleDrawBoundingBox.setup("Activer", false));

	groupDrawBoundingBox.add(boundingBoxLineWidth.setup("Epaisseur", 2, 1, 10));

	ofParameter<ofColor> boundingBoxColorParam = ofParameter<ofColor>("Couleur", ofColor(255, 0, 0), ofColor(0, 0), ofColor(255, 255));
	boundingBoxColorParam.addListener(this, &Application::RGBABoundingBoxColorChanged);

	groupHSBBoundingBoxColor.setup("HSB color");
	groupHSBBoundingBoxColor.minimize();

	HBoundingBoxColorSlider.addListener(this, &Application::HSBBoundingBoxColorChanged);
	SBoundingBoxColorSlider.addListener(this, &Application::HSBBoundingBoxColorChanged);
	BBoundingBoxColorSlider.addListener(this, &Application::HSBBoundingBoxColorChanged);

	groupHSBBoundingBoxColor.add(HBoundingBoxColorSlider.setup("Hue", 0.0f, 0.0f, 360.0f));
	groupHSBBoundingBoxColor.add(SBoundingBoxColorSlider.setup("Saturation", 100.0f, 0.0f, 100.0f));
	groupHSBBoundingBoxColor.add(BBoundingBoxColorSlider.setup("Brightness", 100.0f, 0.0f, 100.0f));

	groupDrawBoundingBox.add(&groupHSBBoundingBoxColor);
	groupDrawBoundingBox.add(RGBABoundingBoxColorSlider.setup(boundingBoxColorParam));
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
	groupTranslation.add(translateXSlider.setup("Translation X", 0.0f, -300.0f, 300.0f));
	groupTranslation.add(translateYSlider.setup("Translation Y", 0.0f, -300.0f, 300.0f));
	groupTranslation.add(translateZSlider.setup("Translation Z", 0.0f, -300.0f, 300.0f));
	groupRotation.add(rotateXField.setup("Angle X", 0.0f, 0.0f, 360.0f));
	groupRotation.add(rotateYField.setup("Angle Y", 0.0f, 0.0f, 360.0f));
	groupRotation.add(rotateZField.setup("Angle Z", 0.0f, 0.0f, 360.0f));
	groupRotation.add(rotateXSlider.setup("Rotation X", 0.0f, -180.0f, 180.0f));
	groupRotation.add(rotateYSlider.setup("Rotation Y", 0.0f, -180.0f, 180.0f));
	groupRotation.add(rotateZSlider.setup("Rotation Z", 0.0f, -180.0f, 180.0f));
	groupScale.add(scaleXField.setup("Echelle X", 1.0f, -30000.0f, 30000.0f));
	groupScale.add(scaleYField.setup("Echelle Y", 1.0f, -30000.0f, 30000.0f));
	groupScale.add(scaleZField.setup("Echelle Z", 1.0f, -30000.0f, 30000.0f));
	groupScale.add(scaleXSlider.setup("Agrand. X", 0.0f, -10.0f, 10.0f));
	groupScale.add(scaleYSlider.setup("Agrand. Y", 0.0f, -10.0f, 10.0f));
	groupScale.add(scaleZSlider.setup("Agrand. Z", 0.0f, -10.0f, 10.0f));

	togglePerspective.addListener(this, &Application::togglePerspectiveChanged);
	toggleOrtho.addListener(this, &Application::toggleOrthoChanged);
	toggleCenterOnSelection.addListener(this, &Application::toggleCenterOnSelectionChanged);

	gui.add(&groupDraw);
	gui.add(&groupGeometry);

	groupHSBBackgroundColor.setup("HSB color");
	groupHSBBackgroundColor.minimize();
	HBackgroundColorSlider.addListener(this, &Application::HSBBackgroundColorChanged);
	SBackgroundColorSlider.addListener(this, &Application::HSBBackgroundColorChanged);
	BBackgroundColorSlider.addListener(this, &Application::HSBBackgroundColorChanged);

	groupHSBBackgroundColor.add(HBackgroundColorSlider.setup("Hue", 0.0f, 0.0f, 360.0f));
	groupHSBBackgroundColor.add(SBackgroundColorSlider.setup("Saturation", 0.0f, 0.0f, 100.0f));
	groupHSBBackgroundColor.add(BBackgroundColorSlider.setup("Brightness", 39.0f, 0.0f, 100.0f));

	gui.add(&groupHSBBackgroundColor);

	ofParameter<ofColor> backgroundColorParam = ofParameter<ofColor>("Arriere-Plan", ofColor(100, 100, 100), ofColor(0, 0), ofColor(255, 255));
	backgroundColorParam.addListener(this, &Application::RGBABackgroundColorChanged);

	gui.add(RGBABackgroundColorSlider.setup(backgroundColorParam));

	cameraPanel.add(toggleCenterOnSelection.setup("Centrer sur la selection", false));
	cameraPanel.add(&groupCameraProjection);

	assetsPanel.add(deleteButton.setup("Supprimer"));

	objectPanel.add(instanceButton.setup("Instancer"));
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
	alertFont.load("fonts\\verdana.ttf", 32);
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

	displayCameraSwitchMessage = ofGetElapsedTimef() - cameraSwitchTime <= 3;
}

//--------------------------------------------------------------
void Application::draw()
{
	ofBackground(backgroundColor);
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

	if (displayCameraSwitchMessage)
	{
		string msg = "Camera " + ofToString(activeCamIndex + 1) + " active";
		ofRectangle textBox = alertFont.getStringBoundingBox(msg, 0, 0);
		ofSetColor(255, 255, 255);

		alertFont.drawString(msg, (ofGetWidth() - textBox.getWidth()) / 2, 50);
	}
}

//--------------------------------------------------------------
void Application::keyPressed(int key)
{
	if (key == 32) // espace
	{
		spacePressed = true;
		cameras[activeCamIndex]->enableMouseInput();
		cameraMode = true;
		resetToggles();
		SetCursor(CAM);
	}
}

//--------------------------------------------------------------
void Application::keyReleased(int key)
{
	switch (key)
	{
	case 32: // espace
		spacePressed = false;
		cameras[activeCamIndex]->disableMouseInput();
		cameraMode = false;
		break;
	case 49: // 1
	case 50: // 2
	case 51: // 3
		if (key - 49 != activeCamIndex && spacePressed)
		{
			activeCamIndex = key - 49;

			lblCamActive = "Camera active: " + ofToString(activeCamIndex + 1);
			cameraSwitchTime = ofGetElapsedTimef();

			togglePerspective = !cameras[activeCamIndex]->getOrtho();
		}
		break;
	case 111: // o
		recording = !recording;
		if (recording) {
			ofSetFrameRate(6);
			imageIndex = 0;
		}
		else ofSetFrameRate(60);
		break;
	case 112: // p
		screenshot = true;
		break;
	}
}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y)
{
	if (isInGui(x, y))
	{
		checkForCursor(x, y);
	}
	else if (cameraMode)
	{
		SetCursor(CAM);
	}
	else if (isDrawing())
	{
		SetCursor(PEN);
	}
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
	if (!isInGui(x, y) && !clickedInUi && !isDrawing() && !cameraMode)
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
	}
	else if (isDrawing())
	{
		SetCursor(PEN);
	}
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button)
{
	mousePressX = x;
	mousePressY = y;
	isMousePressed = true;

	if (!isInGui(x, y))
	{
		if (button != 0 || cameras[activeCamIndex]->getMouseInputEnabled())
			return;

		mousePressX = x;
		mousePressY = y;

		if (!isDrawing() && selectedAssets.size() == 0)
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
	else
	{
		clickedInUi = true;

		if (selectedAssets.size() == 1) {
			previousPosition = selectedAssets[0]->position;
			previousRotation = selectedAssets[0]->rotation;
			previousScale = selectedAssets[0]->scale;
		}
	}
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
	isMousePressed = false;

	if (button != 0 || ((mousePressX == x && mousePressY == y) && !isDrawing()) || cameras[activeCamIndex]->getMouseInputEnabled())
	{
		clickedInUi = false;
		return;
	}

	if (!clickedInUi)
	{
		Asset* asset = nullptr;
		string buttonName = "";
		glm::vec3 screenZero = cameras[activeCamIndex]->worldToScreen(glm::vec3(0, 0, 0));
		glm::vec3 assetPosition = cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, screenZero.z });

		if (toggleDrawLine)
		{
			string shapeName = "line_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addLine(shapeName, assetPosition, cameras[activeCamIndex]->screenToWorld({ x, y, screenZero.z }), lineWidth, RGBAFillColorSlider);

			buttonName = "Ligne";
		}
		else if (toggleDrawRectangle)
		{
			string shapeName = "rectangle_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addRectangle(shapeName, assetPosition, x - mousePressX, y - mousePressY, lineWidth, RGBAFillColorSlider, toggleDrawFill);

			buttonName = "Rectangle";
		}
		else if (toggleDrawCircle)
		{
			string shapeName = "circle_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addCircle(shapeName, assetPosition, x - mousePressX, lineWidth, RGBAFillColorSlider, toggleDrawFill);

			buttonName = "Cercle";
		}
		else if (toggleDrawEllipse)
		{
			string shapeName = "ellipse_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addEllipse(shapeName, assetPosition, x - mousePressX, y - mousePressY, lineWidth, RGBAFillColorSlider, toggleDrawFill);

			buttonName = "Ellipse";
		}
		else if (toggleDrawTriangle)
		{
			string shapeName = "triangle_" + std::to_string(x) + "_" + std::to_string(y);

			glm::vec3 p1 = cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY, screenZero.z });
			glm::vec3 p2 = cameras[activeCamIndex]->screenToWorld({ mousePressX + (x - mousePressX) * 0.5f, y, screenZero.z });
			glm::vec3 p3 = cameras[activeCamIndex]->screenToWorld({ mousePressX - (x - mousePressX) * 0.5f, y, screenZero.z });

			asset = assetManager.addTriangle(shapeName, p1, p2, p3, lineWidth, RGBAFillColorSlider, toggleDrawFill);

			buttonName = "Triangle";
		}
		else if (toggleDrawCube)
		{
			string shapeName = "cube_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addCube(shapeName, assetPosition, x - mousePressX, lineWidth, RGBAFillColorSlider, toggleDrawFill);

			buttonName = "Cube";
		}
		else if (toggleDrawSphere)
		{
			string shapeName = "sphere_" + std::to_string(x) + "_" + std::to_string(y);
			asset = assetManager.addSphere(shapeName, assetPosition, (x - mousePressX) * 0.5f, lineWidth, RGBAFillColorSlider, toggleDrawFill);

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

			glm::vec3 position = cameras[activeCamIndex]->screenToWorld({ mousePressX, mousePressY + 150, screenZero.z });
			asset = assetManager.add3dModel(shapeName, position, "set-of-plants-3d-model\\Yucca\\yuccaPlant.obj");

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

			if (selectedAssets.size() == 1) {
				translateXField = selectedAssets[0]->position.x;
				translateYField = selectedAssets[0]->position.y;
				translateZField = selectedAssets[0]->position.z;

				if (!groupTranslation.isMinimized()) {
					groupTranslation.minimize();
					groupTranslation.maximize();
				}
			}
		}

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

		updateBoundingBox();
	}
	else
	{
		clickedInUi = false;
	}
}

bool Application::isDrawing()
{
	return toggleDrawLine || toggleDrawRectangle || toggleDrawCircle || toggleDrawEllipse || toggleDrawTriangle || toggleDrawCube || toggleDrawSphere || toggleAddModel1 || toggleAddModel2 || toggleAddModel3;
}

bool Application::isInGui(int x, int y)
{
	for (const auto& guiElem : pointerGuiPanelElements)
	{
		if (guiElem->getShape().inside(x, y)) {
			return true;
		}
	}

	return false;
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

void Application::RGBADrawColorChanged(ofColor& value)
{
	for (Asset* asset : selectedAssets)
	{
		asset->color = value;
	}

	if (changedColor)
		return;

	changedColor = true;

	float H;
	float S;
	float B;

	value.getHsb(H, S, B);

	H = (H / 255.0f) * 360.0f;
	S = (S / 255.0f) * 100.0f;
	B = (B / 255.0f) * 100.0f;

	HFillColorSlider.setup("Hue", H, 0.0f, 360.0f);
	SFillColorSlider.setup("Saturation", S, 0.0f, 100.0f);
	BFillColorSlider.setup("Brightness", B, 0.0f, 100.0f);

	changedColor = false;
}

void Application::HSBDrawColorChanged(float& value)
{
	if (changedColor)
		return;

	changedColor = true;

	ofColor color = ofColor::fromHsb(
		ofMap(HFillColorSlider, 0, 360, 0, 255),
		ofMap(SFillColorSlider, 0, 100, 0, 255),
		ofMap(BFillColorSlider, 0, 100, 0, 255),
		255
	);

	ofParameter<ofColor> colorParam = ofParameter<ofColor>("Couleur", color, ofColor(0, 0), ofColor(255, 255));
	colorParam.addListener(this, &Application::RGBADrawColorChanged);

	RGBAFillColorSlider.setup(colorParam);

	RGBADrawColorChanged(color);

	changedColor = false;
}

void Application::RGBABoundingBoxColorChanged(ofColor& value)
{
	assetManager.boundingBox.color = value;

	if (changedColor)
		return;

	changedColor = true;

	float H;
	float S;
	float B;

	value.getHsb(H, S, B);

	H = (H / 255.0f) * 360.0f;
	S = (S / 255.0f) * 100.0f;
	B = (B / 255.0f) * 100.0f;

	HBoundingBoxColorSlider.setup("Hue", H, 0.0f, 360.0f);
	SBoundingBoxColorSlider.setup("Saturation", S, 0.0f, 100.0f);
	BBoundingBoxColorSlider.setup("Brightness", B, 0.0f, 100.0f);

	changedColor = false;
}

void Application::HSBBoundingBoxColorChanged(float& value)
{
	if (changedColor)
		return;

	changedColor = true;

	ofColor color = ofColor::fromHsb(
		ofMap(HBoundingBoxColorSlider, 0, 360, 0, 255),
		ofMap(SBoundingBoxColorSlider, 0, 100, 0, 255),
		ofMap(BBoundingBoxColorSlider, 0, 100, 0, 255)
	);

	ofParameter<ofColor> boundingBoxColorParam = ofParameter<ofColor>("Couleur", color, ofColor(0, 0), ofColor(255, 255));
	boundingBoxColorParam.addListener(this, &Application::RGBABoundingBoxColorChanged);

	RGBABoundingBoxColorSlider.setup(boundingBoxColorParam);

	RGBABoundingBoxColorChanged(color);

	changedColor = false;
}

void Application::RGBABackgroundColorChanged(ofColor& value)
{
	backgroundColor = value;

	if (changedColor)
		return;

	changedColor = true;

	float H;
	float S;
	float B;

	value.getHsb(H, S, B);

	H = (H / 255.0f) * 360.0f;
	S = (S / 255.0f) * 100.0f;
	B = (B / 255.0f) * 100.0f;

	HBackgroundColorSlider.setup("Hue", H, 0.0f, 360.0f);
	SBackgroundColorSlider.setup("Saturation", S, 0.0f, 100.0f);
	BBackgroundColorSlider.setup("Brightness", B, 0.0f, 100.0f);

	changedColor = false;
}

void Application::HSBBackgroundColorChanged(float& value)
{
	if (changedColor)
		return;

	changedColor = true;

	ofColor color = ofColor::fromHsb(
		ofMap(HBackgroundColorSlider, 0, 360, 0, 255),
		ofMap(SBackgroundColorSlider, 0, 100, 0, 255),
		ofMap(BBackgroundColorSlider, 0, 100, 0, 255)
	);

	ofParameter<ofColor> backgroundColorParam = ofParameter<ofColor>("Arriere-Plan", color, ofColor(0, 0), ofColor(255, 255));
	backgroundColorParam.addListener(this, &Application::RGBABackgroundColorChanged);
	RGBABackgroundColorSlider.setup(backgroundColorParam);

	RGBABackgroundColorChanged(color);

	changedColor = false;
}

//--------------------------------------------------------------
void Application::lineWidthChanged(int& value)
{
	for (Asset* asset : selectedAssets)
	{
		asset->lineWidth = lineWidth;
	}
}

void Application::boundingBoxLineWidthChanged(int& value)
{
	assetManager.boundingBox.lineWidth = boundingBoxLineWidth;
}

//--------------------------------------------------------------
void Application::drawBoundingBoxToggleChanged(bool& value)
{
	if (toggleDrawBoundingBox)
	{
		updateBoundingBox();
	}

	assetManager.drawBoundingBox = toggleDrawBoundingBox;
}

void Application::updateBoundingBox()
{
	float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;
	float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;

	for (auto& [_, asset] : assetManager.assets)
	{
		std::vector<glm::vec3> extremes = getExtremePos(&asset);

		minX = std::min(minX, extremes.at(0).x);
		minY = std::min(minY, extremes.at(0).y);
		minZ = std::min(minZ, extremes.at(0).z);

		maxX = std::max(maxX, extremes.at(1).x);
		maxY = std::max(maxY, extremes.at(1).y);
		maxZ = std::max(maxZ, extremes.at(1).z);
	}

	assetManager.boundingBox.width = maxX - minX;
	assetManager.boundingBox.height = maxY - minY;
	assetManager.boundingBox.depth = maxZ - minZ;

	assetManager.boundingBox.position = {
		minX + assetManager.boundingBox.width * 0.5f,
		minY + assetManager.boundingBox.height * 0.5f,
		minZ + assetManager.boundingBox.depth * 0.5f
	};

    assetManager.boundingBox.color = RGBABoundingBoxColorSlider;
    assetManager.boundingBox.lineWidth = boundingBoxLineWidth;
}

std::vector<glm::vec3> Application::getExtremePos(Asset* asset)
{
	std::vector<glm::vec3> extremes;

	glm::vec3 minPoint(FLT_MAX);
	glm::vec3 maxPoint(-FLT_MAX);

	int minX = asset->position.x, minY = asset->position.y, minZ = asset->position.z;
	int maxX = asset->position.x, maxY = asset->position.y, maxZ = asset->position.z;

	switch (asset->type)
	{
		case AssetType::IMAGE:
		case AssetType::RECTANGLE:
		{
			float scaledWidth = asset->width * asset->scale.x;
			float scaledHeight = asset->height * asset->scale.y;
			float scaledDepth = asset->depth * asset->scale.z;

			minX = std::min(asset->position.x, asset->position.x + scaledWidth);
			minY = std::min(asset->position.y, asset->position.y + scaledHeight);
			minZ = std::min(asset->position.z, asset->position.z + scaledDepth);

			maxX = std::max(asset->position.x, asset->position.x + scaledWidth);
			maxY = std::max(asset->position.y, asset->position.y + scaledHeight);
			maxZ = std::max(asset->position.z, asset->position.z + scaledDepth);

			break;
		}
		case AssetType::CIRCLE:
		{
			float scaledRadiusX = asset->radius * asset->scale.x;
			float scaledRadiusY = asset->radius * asset->scale.y;

			minX = asset->position.x - scaledRadiusX;
			maxX = asset->position.x + scaledRadiusX;
			minY = asset->position.y - scaledRadiusY;
			maxY = asset->position.y + scaledRadiusY;
			minZ = asset->position.z;
			maxZ = asset->position.z;

			break;
		}
		case AssetType::ELLIPSE:
		{
			float scaledWidth = asset->width * asset->scale.x;
			float scaledHeight = asset->height * asset->scale.y;

			minX = asset->position.x - scaledWidth / 2;
			maxX = asset->position.x + scaledWidth / 2;
			minY = asset->position.y - scaledHeight / 2;
			maxY = asset->position.y + scaledHeight / 2;
			minZ = asset->position.z;
			maxZ = asset->position.z;

			break;
		}
		case AssetType::LINE:
		{
			minX = std::min(asset->position.x, asset->endpoint.x);
			minY = std::min(asset->position.y, asset->endpoint.y);
			minZ = std::min(asset->position.z, asset->endpoint.z);

			maxX = std::max(asset->position.x, asset->endpoint.x);
			maxY = std::max(asset->position.y, asset->endpoint.y);
			maxZ = std::max(asset->position.z, asset->endpoint.z);

			break;
		}
		case AssetType::TRIANGLE:
		{
			minX = std::min({ asset->p1.x, asset->p2.x, asset->p3.x });
			minY = std::min({ asset->p1.y, asset->p2.y, asset->p3.y });
			minZ = std::min({ asset->p1.z, asset->p2.z, asset->p3.z });

			maxX = std::max({ asset->p1.x, asset->p2.x, asset->p3.x });
			maxY = std::max({ asset->p1.y, asset->p2.y, asset->p3.y });
			maxZ = std::max({ asset->p1.z, asset->p2.z, asset->p3.z });

			break;
		}
		case AssetType::CUBE:
		{
			glm::vec3 halfSize = glm::vec3(asset->width * 0.5f, asset->height * 0.5f, asset->depth * 0.5f);

			glm::vec3 corners[8] = {
				glm::vec3(-halfSize.x, -halfSize.y, -halfSize.z),
				glm::vec3(-halfSize.x, -halfSize.y,  halfSize.z),
				glm::vec3(-halfSize.x,  halfSize.y, -halfSize.z),
				glm::vec3(-halfSize.x,  halfSize.y,  halfSize.z),
				glm::vec3(halfSize.x, -halfSize.y, -halfSize.z),
				glm::vec3(halfSize.x, -halfSize.y,  halfSize.z),
				glm::vec3(halfSize.x,  halfSize.y, -halfSize.z),
				glm::vec3(halfSize.x,  halfSize.y,  halfSize.z)
			};

			glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), asset->position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(asset->rotation.x), glm::vec3(1, 0, 0))
				* glm::rotate(glm::mat4(1.0f), glm::radians(asset->rotation.y), glm::vec3(0, 1, 0))
				* glm::rotate(glm::mat4(1.0f), glm::radians(asset->rotation.z), glm::vec3(0, 0, 1))
				* glm::scale(glm::mat4(1.0f), asset->scale);

			minPoint = glm::vec3(FLT_MAX);
			maxPoint = glm::vec3(-FLT_MAX);

			for (int i = 0; i < 8; i++) {
				glm::vec3 transformedCorner = glm::vec3(transformationMatrix * glm::vec4(corners[i], 1.0f));
				minPoint = glm::min(minPoint, transformedCorner);
				maxPoint = glm::max(maxPoint, transformedCorner);
			}

			minX = minPoint.x;
			minY = minPoint.y;
			minZ = minPoint.z;

			maxX = maxPoint.x;
			maxY = maxPoint.y;
			maxZ = maxPoint.z;

			break;
		}
		case AssetType::SPHERE:
		{
			float scaledRadiusX = std::abs(asset->width * asset->scale.x);
			float scaledRadiusY = std::abs(asset->width * asset->scale.y);
			float scaledRadiusZ = std::abs(asset->width * asset->scale.z);

			minX = asset->position.x - scaledRadiusX;
			maxX = asset->position.x + scaledRadiusX;

			minY = asset->position.y - scaledRadiusY;
			maxY = asset->position.y + scaledRadiusY;

			minZ = asset->position.z - scaledRadiusZ;
			maxZ = asset->position.z + scaledRadiusZ;

			break;
		}
		case AssetType::MODEL:
		{
			for (int i = 0; i < asset->model.getNumMeshes(); i++) {
				ofMesh mesh = asset->model.getMesh(i);

				for (auto& vertex : mesh.getVertices()) {
					glm::vec3 worldVertex = asset->model.getModelMatrix() * glm::vec4(vertex, 1.0);

					minPoint = glm::min(minPoint, worldVertex);
					maxPoint = glm::max(maxPoint, worldVertex);
				}
			}

			minX = minPoint.x;
			minY = minPoint.y;
			minZ = minPoint.z;

			maxX = maxPoint.x;
			maxY = maxPoint.y;
			maxZ = maxPoint.z;

			break;
		}
		case AssetType::INSTANCE:
		{
			Asset inst;
			inst.type = asset->parent->type;
			inst.image = asset->image;
			inst.position = asset->position;
			inst.rotation = asset->rotation;
			inst.scale = asset->scale;
			inst.width = asset->width;
			inst.height = asset->height;
			inst.depth = asset->depth;
			inst.radius = asset->radius;
			inst.endpoint = asset->endpoint;
			inst.p1 = asset->p1;
			inst.p2 = asset->p2;
			inst.p3 = asset->p3;

			return getExtremePos(&inst);
		}
	}

	extremes.push_back({ minX, minY, minZ });

	extremes.push_back({ maxX, maxY, maxZ });

	return extremes;
}

void Application::setCameraTargetOnSelectedAssets(bool value)
{
	if (cameras.size() == 0)
		return;

	ofVec3f minBounds(FLT_MAX, FLT_MAX, FLT_MAX);
	ofVec3f maxBounds(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	if (selectedAssets.size() == 0 || !toggleCenterOnSelection)
	{
		cameras[activeCamIndex]->setPosition(DEFAULT_CAM_POS);
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
		float distance = radius / std::tan(fov * 0.5f);


		ofVec3f camPos = center + ofVec3f(0, 0, distance);

		cameras[activeCamIndex]->setPosition(camPos);
		cameras[activeCamIndex]->lookAt(center);
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
				RGBAFillColorSlider = asset->color;
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
		translateXField = selectedAssets[0]->position.x;
		translateYField = selectedAssets[0]->position.y;
		translateZField = selectedAssets[0]->position.z;
		if (!groupTranslation.isMinimized()) {
			groupTranslation.minimize();
			groupTranslation.maximize();
		}
		rotateXField = selectedAssets[0]->rotation.x;
		rotateYField = selectedAssets[0]->rotation.y;
		rotateZField = selectedAssets[0]->rotation.z;
		if (!groupRotation.isMinimized()) {
			groupRotation.minimize();
			groupRotation.maximize();
		}
		scaleXField = selectedAssets[0]->scale.x;
		scaleYField = selectedAssets[0]->scale.y;
		scaleZField = selectedAssets[0]->scale.z;
		if (!groupScale.isMinimized()) {
			groupScale.minimize();
			groupScale.maximize();
		}
	}
}

void Application::positionXChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setPosition(selectedAssets[0], glm::vec3(value, selectedAssets[0]->position.y, selectedAssets[0]->position.z));

	updateBoundingBox();

	return;
}

void Application::positionYChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setPosition(selectedAssets[0], glm::vec3(selectedAssets[0]->position.x, value, selectedAssets[0]->position.z));

	updateBoundingBox();

	return;
}

void Application::positionZChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setPosition(selectedAssets[0], glm::vec3(selectedAssets[0]->position.x, selectedAssets[0]->position.y, value));

	updateBoundingBox();

	return;
}

void Application::translateXChanged(float& value) {
	if (selectedAssets.size() == 1) {
		assetManager.setPosition(selectedAssets[0], glm::vec3(previousPosition.x + value, selectedAssets[0]->position.y, selectedAssets[0]->position.z));
		translateXField = selectedAssets[0]->position.x;
	}
	if (!isMousePressed) translateXSlider = 0;

	updateBoundingBox();

	return;
}

void Application::translateYChanged(float& value) {
	if (selectedAssets.size() == 1) {
		assetManager.setPosition(selectedAssets[0], glm::vec3(selectedAssets[0]->position.x, previousPosition.y + value, selectedAssets[0]->position.z));
		translateYField = selectedAssets[0]->position.y;
	}
	if (!isMousePressed) translateYSlider = 0;

	updateBoundingBox();

	return;
}

void Application::translateZChanged(float& value) {
	if (selectedAssets.size() == 1) {
		assetManager.setPosition(selectedAssets[0], glm::vec3(selectedAssets[0]->position.x, selectedAssets[0]->position.y, previousPosition.z + value));
		translateZField = selectedAssets[0]->position.z;
	}
	if (!isMousePressed) translateZSlider = 0;

	updateBoundingBox();

	return;
}

void Application::angleXChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setRotation(selectedAssets[0], glm::vec3(value, selectedAssets[0]->rotation.y, selectedAssets[0]->rotation.z));

	updateBoundingBox();

	return;
}

void Application::angleYChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setRotation(selectedAssets[0], glm::vec3(selectedAssets[0]->rotation.x, value, selectedAssets[0]->rotation.z));

	updateBoundingBox();

	return;
}

void Application::angleZChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setRotation(selectedAssets[0], glm::vec3(selectedAssets[0]->rotation.x, selectedAssets[0]->rotation.y, value));

	updateBoundingBox();

	return;
}

void Application::rotateXChanged(float& value) {
	float val = value;
	while (previousRotation.x + val < 0.0f || 360.0f < previousRotation.x + val) { //contraindre la valeur de l'angle entre 0 et 360, comme pour les fields
		if (previousRotation.x + val < 0.0f) val += 360.0f;
		else if (360.0f < previousRotation.x + val) val -= 360.0f;
	}
	if (selectedAssets.size() == 1) {
		assetManager.setRotation(selectedAssets[0], glm::vec3(previousRotation.x + val, selectedAssets[0]->rotation.y, selectedAssets[0]->rotation.z));
		rotateXField = selectedAssets[0]->rotation.x;
	}
	if (!isMousePressed) rotateXSlider = 0;

	updateBoundingBox();

	return;
}

void Application::rotateYChanged(float& value) {
	float val = value;
	while (previousRotation.y + val < 0.0f || 360.0f < previousRotation.y + val) { //contraindre la valeur de l'angle entre 0 et 360, comme pour les fields
		if (previousRotation.y + val < 0.0f) val += 360.0f;
		else if (360.0f < previousRotation.y + val) val -= 360.0f;
	}
	if (selectedAssets.size() == 1) {
		assetManager.setRotation(selectedAssets[0], glm::vec3(selectedAssets[0]->rotation.x, previousRotation.y + val, selectedAssets[0]->rotation.z));
		rotateYField = selectedAssets[0]->rotation.y;
	}
	if (!isMousePressed) rotateYSlider = 0;

	updateBoundingBox();

	return;
}

void Application::rotateZChanged(float& value) {
	float val = value;
	while (previousRotation.z + val < 0.0f || 360.0f < previousRotation.z + val) { //contraindre la valeur de l'angle entre 0 et 360, comme pour les fields
		if (previousRotation.z + val < 0.0f) val += 360.0f;
		else if (360.0f < previousRotation.z + val) val -= 360.0f;
	}
	if (selectedAssets.size() == 1) {
		assetManager.setRotation(selectedAssets[0], glm::vec3(selectedAssets[0]->rotation.x, selectedAssets[0]->rotation.y, previousRotation.z + val));
		rotateZField = selectedAssets[0]->rotation.z;
	}
	if (!isMousePressed) rotateZSlider = 0;

	updateBoundingBox();

	return;
}

void Application::scaleXChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setScale(selectedAssets[0], glm::vec3(value, selectedAssets[0]->scale.y, selectedAssets[0]->scale.z));

	updateBoundingBox();

	return;
}

void Application::scaleYChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setScale(selectedAssets[0], glm::vec3(selectedAssets[0]->scale.x, value, selectedAssets[0]->scale.z));

	updateBoundingBox();

	return;
}

void Application::scaleZChanged(float& value) {
	if (selectedAssets.size() == 1) assetManager.setScale(selectedAssets[0], glm::vec3(selectedAssets[0]->scale.x, selectedAssets[0]->scale.y, value));

	updateBoundingBox();
}

void Application::growthXChanged(float& value) {
	if (selectedAssets.size() == 1) {
		assetManager.setScale(selectedAssets[0], glm::vec3(previousScale.x + value, selectedAssets[0]->scale.y, selectedAssets[0]->scale.z));
		scaleXField = selectedAssets[0]->scale.x;
	}
	if (!isMousePressed) scaleXSlider = 0;

	updateBoundingBox();

	return;
}

void Application::growthYChanged(float& value) {
	if (selectedAssets.size() == 1) {
		assetManager.setScale(selectedAssets[0], glm::vec3(selectedAssets[0]->scale.x, previousScale.y + value, selectedAssets[0]->scale.z));
		scaleYField = selectedAssets[0]->scale.y;
	}
	if (!isMousePressed) scaleYSlider = 0;

	updateBoundingBox();

	return;
}

void Application::growthZChanged(float& value) {
	if (selectedAssets.size() == 1) {
		assetManager.setScale(selectedAssets[0], glm::vec3(selectedAssets[0]->scale.x, selectedAssets[0]->scale.y, previousScale.z + value));
		scaleZField = selectedAssets[0]->scale.z;
	}
	if (!isMousePressed) scaleZSlider = 0;

	updateBoundingBox();
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
		cameras[activeCamIndex]->setPosition(DEFAULT_CAM_POS);
	}
}


//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo)
{
	int importedImageCount = assetManager.assets.size();

	glm::vec3 screenZero = cameras[activeCamIndex]->worldToScreen(glm::vec3(0, 0, 0));
	glm::vec3 assetPosition = cameras[activeCamIndex]->screenToWorld({ dragInfo.position.x, dragInfo.position.y, screenZero.z });

	for (int i = 0; i < dragInfo.files.size(); i++)
	{
		string imageName = "imported_image_" + std::to_string(importedImageCount + i);
		Asset* asset = assetManager.addImage(imageName, dragInfo.files[i], assetPosition);

		auto button = std::make_shared<ofxToggle2>();
		assetsPanel.add(button.get()->setup("Image", true));
		assetsButtons[imageName] = button;

		asset->isSelected = true;
		selectedAssets.push_back(asset);
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
			if(assetManager.assets[key].type == AssetType::INSTANCE)
				assetManager.assets[key].parent->instances.erase(assetManager.assets[key].name[assetManager.assets[key].name.length()]); //vérifié sans problème de erase 2 fois
			else if (assetManager.assets[key].type != AssetType::INSTANCE && assetManager.assets[key].instances.size() > 0) {
				int numInstances = assetManager.assets[key].instances.size();
				for (int i = 0; i < numInstances; i++) {
					assetManager.assets.erase(assetManager.assets[key].name + "-" + std::to_string(i));
					buttonsToRemove.push_back(assetManager.assets[key].name + "-" + std::to_string(i));
				}
				assetManager.assets[key].instances.clear();
			}
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
	updateBoundingBox();
}

void Application::instanceButtonPressed() {
	if (selectedAssets[0]->type == AssetType::INSTANCE) return;
	else {
		Asset* asset = assetManager.addInstance(*selectedAssets[0]);
		string buttonName = asset->name;
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

	updateBoundingBox();
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

	ofLog(OF_LOG_NOTICE, "Image exportée vers /bin/data/" + fileName);

	image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	image.save(fileName);
}
