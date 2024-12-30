#include "Application.h"

Application *Application::getInstance() {
	return instance ? instance : instance = new Application();
}

Application::Application() {
	FileManager::addFolder("asset/team_sample/");
	// FileManager::addFile("asset/team_sample/linear_grad.svg");
	FileManager::setCurrentIdx(6, true);

	Renderer::getInstance();
	XMLParser::getInstance();

	buildMenu();
}

Application::~Application() {
	delete Renderer::getInstance();
	delete XMLParser::getInstance();
}

void Application::openImportFileMenu() {
	OPENFILENAME ofn;
	char szFile[1024 * 5] = {};
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "SVG files\0*.SVG\0All files\0*.*\0"; // Filter for file types
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;
	ofn.lpstrTitle = "SVG Rendering - G11: Import one or more files";
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		char *file = ofn.lpstrFile;
		char *path = file;
		file += strlen(file) + 1;
		bool multipleFile = false;
		bool newFileAdded = false;
		while (*file) {
			multipleFile = true;
			if (FileManager::addFile(std::string(path) + "\\" + file)) {
				newFileAdded = true;
			}
			file += strlen(file) + 1;
		}
		if (!multipleFile) {
			newFileAdded = FileManager::addFile(std::string(path));
		}
		if (newFileAdded) {
			SetCurrentDirectory(FileManager::EXECUTABLE_PATH.c_str());
			buildMenu();
		}
	} else {
		DWORD error = CommDlgExtendedError();
		if (error) {
			printf("Error opening file! Error code: %lu\n", error);
		} else {
			printf("No files selected or dialog was canceled.\n");
		}
	}
}

void Application::buildMenu() {
	buildFileMenu();
	menu = CreatePopupMenu();

	AppendMenu(menu, MF_STRING, MenuBase::current + 0, "Import files");
	AppendMenu(menu, MF_STRING | (isMaximumScreen ? MF_CHECKED : MF_UNCHECKED), MenuBase::current + 1, "Maximum screen");
	AppendMenu(menu, MF_STRING | (isViewFullPath ? MF_CHECKED : MF_UNCHECKED), MenuBase::current + 2, "View full paths");
	AppendMenu(menu, MF_STRING | (isRulerMode ? MF_CHECKED : MF_UNCHECKED), MenuBase::current + 3, "Ruler mode");
	AppendMenu(menu, MF_STRING | (doSRGBGradient ? MF_CHECKED : MF_UNCHECKED), MenuBase::current + 4, "SRGB Gradient Mode");
	AppendMenu(menu, MF_STRING | MF_POPUP, reinterpret_cast<UINT_PTR>(fileMenu), "Imported SVGs");
}

void Application::buildFileMenu() {
	vector<string> files = FileManager::getFileList(isViewFullPath);

	fileMenu = CreatePopupMenu();

	size_t cur = FileManager::getCurrentIdx();
	for (int i = 0; i < files.size(); i++) {
		AppendMenu(fileMenu, MF_STRING | (cur == i ? MF_CHECKED : MF_UNCHECKED), i, files[i].c_str());
	}
	MenuBase::fileBase = files.size();
	MenuBase::current = files.size();
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
		Gdiplus::SolidBrush brush(SVG_GRAY);
		Gdiplus::Font font(L"Arial", 1);
		for (int i = drawAreaStart.x; i < drawArea.x; i += 10) {
			graphics.DrawString(std::to_wstring(i).c_str(), -1, &font, {static_cast<Gdiplus::REAL>(i), 0}, &brush);
			graphics.DrawLine(&pen, i, 0, i, drawArea.y);
		}
		for (int i = drawAreaStart.y / 10 * 10; i < drawArea.y; i += 10) {
			graphics.DrawString(std::to_wstring(i).c_str(), -1, &font, {0, static_cast<Gdiplus::REAL>(i)}, &brush);
		}
		for (int i = drawAreaStart.y; i < drawArea.y; i += 10) {
			graphics.DrawLine(&pen, 0, i, drawArea.x, i);
		}
	}
}
