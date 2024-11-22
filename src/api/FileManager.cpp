#include "FileManager.h"

std::vector<std::wstring> FileManager::filePaths;
int FileManager::current = (int) filePaths.size() - 1;

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
	auto it = std::find(filePaths.begin(), filePaths.end(), filePath);
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

bool FileManager::isFileExist(const std::wstring &filePath) {
	std::ifstream file(filePath.c_str());
	if (!file.is_open()) {
		return false;
	}
	file.close();
	return true;
}

std::wstring FileManager::getFileName(const std::wstring &filePath) {
	return filePath.substr(filePath.find_last_of(L"/\\") + 1);
}

std::wstring FileManager::getFilePath(size_t idx) {
	if (idx >= filePaths.size()) return L"";
	return filePaths.at(idx);
}

std::vector<std::wstring> FileManager::getFileNameList() {
	std::vector<std::wstring> r;
	r.reserve(filePaths.size());
	for (auto &file : filePaths) {
		r.push_back(FileManager::getFileName(file));
	}
	return r;
}

int FileManager::getCurrent() { return current; }

void FileManager::setCurrent(int idx) {
	if (idx < 0 || idx >= filePaths.size()) {
		return;
	}
	current = idx;
}

void FileManager::clearFiles() {
	filePaths.clear();
	current = -1;
}
