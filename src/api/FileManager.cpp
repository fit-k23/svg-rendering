#include "FileManager.h"

vector<string> FileManager::filePaths;
size_t FileManager::current = 0;

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
	filePaths.erase(filePaths.begin() + idx); // NOLINT(*-narrowing-conversions)
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
		r.push_back(FileManager::getFile(file));
	}
	return r;
}

string FileManager::getCurrentFile() { return filePaths[current]; }

size_t FileManager::getCurrent() { return current; }

void FileManager::setCurrent(size_t idx) {
	if (idx >= filePaths.size()) {
		return;
	}
	current = idx;
	XMLParser::getInstance()->traverseXML(filePaths[idx], nullptr, nullptr);
}

void FileManager::clearFiles() {
	filePaths.clear();
	current = -1;
}
