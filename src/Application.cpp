#include "Application.h"

Application::Application() {
	initialize();
}

Application::~Application() {
	deinitialize();
}

void Application::initialize() {
	FileManager::addFile("asset/gradient_rect.svg");
	FileManager::setCurrentIdx(0, true);

	Renderer::getInstance();
	XMLParser::getInstance();
}

void Application::deinitialize() {
	delete Renderer::getInstance();
	delete XMLParser::getInstance();
}

void Application::buildMenu() {

}

void Application::buildFileMenu() {
	vector<string> files = FileManager::getFileList();

	fileMenu = CreatePopupMenu();
	size_t cur = FileManager::getCurrentIdx();
	for (int i = 0; i < files.size(); i++) {
		if (cur == i) {
			AppendMenu(fileMenu, MF_STRING | MF_CHECKED, i, files[i].c_str());
		} else {
			AppendMenu(fileMenu, MF_STRING, i, files[i].c_str());
		}
	}
}

Application *Application::getInstance() {
	return instance ? instance : instance = new Application();
}

void Application::draw(HDC hdc) {
	Gdiplus::Graphics graphics(hdc);
	XMLParser *parser = XMLParser::getInstance();

	Vector2D<float> vPort = parser->getViewPort();

	Renderer *render = Renderer::getInstance();
	render->setViewPort(vPort);

	Renderer::configGraphic(graphics);
	Renderer::configCamera(graphics);

	render->draw(graphics, parser->getRoot());

	if (isRulerMode) {
		Gdiplus::Pen pen({255, 0, 0, 0}, 1 / Camera::zoom);

		Vector2D<int> drawAreaStart = {0, 0};
		Vector2D<int> drawArea = Camera::screenSize;

		if (Camera::zoom > 5.0) {
			pen.SetColor(SVG_ORANGE);
			for (int i = drawAreaStart.x; i < drawArea.x; i += 1) {
				graphics.DrawLine(&pen, i, 0, i, drawArea.y);
			}
			for (int i = drawAreaStart.y; i < drawArea.y; i += 1) {
				graphics.DrawLine(&pen, 0, i, drawArea.x, i);
			}
		} else if (Camera::zoom > 1.5) {
			pen.SetColor(SVG_BLUE);
			for (int i = drawAreaStart.x; i < drawArea.x; i += 5) {
				graphics.DrawLine(&pen, i, 0, i, drawArea.y);
			}
			for (int i = drawAreaStart.y; i < drawArea.y; i += 5) {
				graphics.DrawLine(&pen, 0, i, drawArea.x, i);
			}
		}
		pen.SetColor(SVG_BLACK);
		for (int i = drawAreaStart.x; i < drawArea.x; i += 10) {
			Gdiplus::SolidBrush brush(SVG_GRAY);
			Gdiplus::Font font(L"Arial", 1);
			graphics.DrawString(std::to_wstring(i).c_str(), -1, &font, {static_cast<Gdiplus::REAL>(i), 0}, &brush);
			graphics.DrawLine(&pen, i, 0, i, drawArea.y);
		}
		for (int i = drawAreaStart.y; i < drawArea.y; i += 10) {
			graphics.DrawLine(&pen, 0, i, drawArea.x, i);
		}
	}
}
