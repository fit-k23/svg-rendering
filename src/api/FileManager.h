#ifndef SVG_RENDERING_FILE_MANAGER_H
#define SVG_RENDERING_FILE_MANAGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "XMLParser.h"

using std::string;
using std::vector;

#include <filesystem>

namespace FileHelper{
	inline string toLinuxPath(const string &filePath) {
		std::string linuxPath = filePath;
		std::replace(linuxPath.begin(), linuxPath.end(), '\\', '/');
		return linuxPath;
	}

	inline string toWindowsPath(const string &filePath) {
		std::string windowsPath = filePath;
		std::replace(windowsPath.begin(), windowsPath.end(), '/', '\\');
		return windowsPath;
	}

	inline bool pathExists(const string &path) {
		return std::filesystem::exists(path);
	}

	inline bool pathIsDirectory(const string &path) {
		return std::filesystem::is_directory(path);
	}

	/**
	 * @brief Get File Name from File Path, eg: /example/folder/Hi.txt -> Hi.txt
	 * @param filePath Input filepath
	 */
	inline string getFileName(const string &filePath) {
		return filePath.substr(filePath.find_last_of("/\\") + 1);
	}

	inline string getParentPath(const string &filePath) {
		return std::filesystem::path(filePath).parent_path().string();
	}

	inline string getRelativePath(const string &path1, const string &path2) {
		return std::filesystem::relative(path1, path2).string();
	}

	static string getRedirectPath(const string &path1, const string &path2) {
		string relativePath = getRelativePath(path1, path2);
		if (relativePath.empty()) {
			return path1;
		}
		return relativePath;
	}

	inline string getAbsolutePath(const string &filePath) {
		return std::filesystem::absolute(filePath).string();
	}
}

class FileManager{
	static vector<string> filePaths;
	static size_t current;
public:
	static string EXECUTABLE_PATH;
	static bool addFolder(const string &folderPath);
	/**
	 * @brief Add file to file manager
	 * @param filePath Input filepath, must be wide string!
	 */
	static bool addFile(const string &filePath);
	/**
	 * @brief Remove file by searching its name, return false if not exist
	 * @param filePath Input filepath, must be wide string!
	 */
	static bool removeFile(const string &filePath);
	/**
	 * @brief Remove file by using its index in the vector, return false if not exist or index is out of bound.
	 * @param idx Index of the file in the vector
	 */
	static bool removeFile(size_t idx);
	static void clearFiles();
	/**
	 * @brief Get File Path in File Manager using index, return empty wide-string if not exist or index is out of bound.
	 * @param idx Index of the file in the vector
	 */
	static string getFile(size_t idx);
	/**
	 * @brief Get a list of file's name
	 * @param viewFull show file with full path | default: false
	 */
	static vector<string> getFileList(bool viewFull = false);
	/** @brief Set current file idx to target idx */
	static bool setCurrentIdx(size_t idx, bool forceReload = false);
	/** @brief Get current file idx */
	static size_t getCurrentIdx();
	/** @brief Get current file path */
	static string getCurrentFile();
};

#endif //SVG_RENDERING_FILE_MANAGER_H
