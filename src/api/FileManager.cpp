#include "FileManager.h"

std::vector<std::wstring> FileManager::filePaths;

std::vector<std::wstring> &FileManager::getFilePaths() {
	return filePaths;
}
bool FileManager::addFile(const std::wstring &filePath) {
	if (filePath.empty() || !isFileExist(filePath)) return false;
	for (auto &file : filePaths) {
		if (file == filePath) {
			return false;
		}
	}
	filePaths.push_back(filePath);
	return true;
}

bool FileManager::removeFile(const std::wstring &filePath) {
	for (auto &file : filePaths) {
		if (file == filePath) {
			return true;
		}
	}
	return false;
}

bool FileManager::removeFile(size_t idx) {
	return false;
}

bool FileManager::isFileExist(const std::wstring &filePath) {
	std::ifstream file(filePath.c_str());
	if (!file.is_open()) {
		return false;
	}
	file.close();
	return true;
}

std::wstring FileManager::getBaseName(const std::wstring &filePath) {
	return filePath.substr(filePath.find_last_of(L"/\\") + 1);
}
