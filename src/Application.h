#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>
#include <string>
#include <vector>
#include "api/Renderer.h"
#include "api/XMLParser.h"
#include "api/FileManager.h"

class Application final{
	inline static Application *instance = nullptr;
	Application();
	~Application();
	static void initialize();
	static void deinitialize();
public:
	static void buildMenu();
	static void buildFileMenu();
	inline static HMENU menu;
	inline static HMENU fileMenu;
	inline bool static isRulerMode = false;
	static Application *getInstance();
	void draw(HDC hdc);
};

#endif //APPLICATION_H