#include "FileManager.h"

vector<string> FileManager::filePaths;
size_t FileManager::current = 0;

#include <filesystem>

bool FileManager::addFolder(const string &folderPath) {
	if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
		return false;
	}

	for (const auto &entry : std::filesystem::directory_iterator(folderPath)) {
		if (is_directory(entry)) {
			continue;
		}
		addFile(entry.path().string());
	}
	return true;
}

bool FileManager::addFile(const string &filePath) {
	if (filePath.empty() || !isFileExist(filePath)) return false;
	for (auto &file : filePaths) {
		if (file == filePath) {
			return false;
		}
	}
	filePaths.push_back(filePath);
	return true;
}

bool FileManager::removeFile(const string &filePath) {
	auto it = find(filePaths.begin(), filePaths.end(), filePath);
	if (it != filePaths.end()) {
		filePaths.erase(it);
		return true;
	}
	return false;
}

bool FileManager::removeFile(size_t idx) {
	if (idx >= filePaths.size()) return false;
	filePaths.erase(filePaths.begin() + idx);
	return true;
}

bool FileManager::isFileExist(const string &filePath) {
	std::ifstream file(filePath.c_str());
	if (!file.is_open()) {
		return false;
	}
	file.close();
	return true;
}

string FileManager::getFile(const string &filePath) {
	return filePath.substr(filePath.find_last_of("/\\") + 1);
}

string FileManager::getFile(size_t idx) {
	if (idx >= filePaths.size()) return "";
	return filePaths.at(idx);
}

vector<string> FileManager::getFileList() {
	vector<string> r;
	r.reserve(filePaths.size());
	for (auto &file : filePaths) {
		r.push_back(getFile(file));
	}
	return r;
}

string FileManager::getCurrentFile() { return filePaths[current]; }

size_t FileManager::getCurrentIdx() { return current; }

bool FileManager::setCurrentIdx(size_t idx, bool forceReload) {
	if (idx >= filePaths.size() || (idx == current && !forceReload))
		return false;
	current = idx;
	XMLParser::getInstance()->traverseXML(filePaths[idx], nullptr, nullptr);
	return true;
}

void FileManager::clearFiles() {
	filePaths.clear();
	current = -1;
}
