#include "FileManager.h"

vector<string> FileManager::filePaths;
size_t FileManager::current = 0;
string FileManager::EXECUTABLE_PATH;

bool FileManager::addFolder(const string &folderPath) {
	if (!FileHelper::pathExists(folderPath) || !FileHelper::pathIsDirectory(folderPath)) {
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
	std::string inFilePath = FileHelper::getRedirectPath(filePath, EXECUTABLE_PATH);
	if (filePath.empty() || FileHelper::pathIsDirectory(filePath)) return false;
	for (auto &file : filePaths) {
		if (file == inFilePath) {
			return false;
		}
	}
	filePaths.push_back(inFilePath);
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

string FileManager::getFile(size_t idx) {
	if (idx >= filePaths.size()) return "";
	return filePaths.at(idx);
}

vector<string> FileManager::getFileList(bool viewFull) {
	if (viewFull) {
		return filePaths;
	}
	vector<string> r;
	r.reserve(filePaths.size());
	for (auto &file : filePaths) {
		r.push_back(FileHelper::getFileName(file));
	}
	return r;
}

string FileManager::getCurrentFile() { return filePaths[current]; }

size_t FileManager::getCurrentIdx() { return current; }

bool FileManager::setCurrentIdx(size_t idx, bool forceReload) {
	if (idx >= filePaths.size() || (idx == current && !forceReload))
		return false;
	if (!FileHelper::pathExists(filePaths[idx]) && !FileHelper::pathExists(EXECUTABLE_PATH + '\\' + filePaths[idx])) {
		return false;
	}
	current = idx;
	XMLParser::getInstance()->traverseXML(filePaths[idx], nullptr, nullptr);
	return true;
}

void FileManager::clearFiles() {
	filePaths.clear();
	current = -1;
}
