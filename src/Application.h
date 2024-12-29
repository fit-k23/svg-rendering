#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>
#include <string>
#include <vector>
#include "api/Renderer.h"
#include "api/XMLParser.h"
#include "api/FileManager.h"

struct MenuBase {
	inline static unsigned long long fileBase = 0;
	inline static unsigned long long current = fileBase;
};

class Application final{
	inline static Application *instance = nullptr;
	Application();
	~Application();
public:
	static void openImportFileMenu();
	static void buildFileMenu();
	static void buildMenu();
	inline static HMENU menu;
	inline static HMENU fileMenu;
	inline static bool isRulerMode = false;
	inline static bool doSRGBGradient = true;
	inline static bool isMaximumScreen = false;
	inline static bool isViewFullPath = true;
	static Application *getInstance();
	void draw(HDC hdc);
};

#endif //APPLICATION_H