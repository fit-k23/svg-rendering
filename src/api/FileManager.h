#ifndef SVG_RENDERING_FILEMANAGER_H
#define SVG_RENDERING_FILEMANAGER_H

#include <iostream>
#include <vector>
#include <fstream>

class FileManager {
	static std::vector<std::wstring> filePaths;
public:
	static bool addFile(const std::wstring &filePath);
	static bool removeFile(const std::wstring &filePath);
	static bool removeFile(size_t idx);
	static std::vector<std::wstring> &getFilePaths();
	static bool isFileExist(const std::wstring &filePath);
	static std::wstring getBaseName(const std::wstring &filePath);
};

#endif //SVG_RENDERING_FILEMANAGER_H