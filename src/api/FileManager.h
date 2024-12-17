#ifndef SVG_RENDERING_FILE_MANAGER_H
#define SVG_RENDERING_FILE_MANAGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "XMLParser.h"

using std::string;
using std::vector;

class FileManager{
	static vector<string> filePaths;
	static size_t current;
public:
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
	 * @brief Validate if the file path leads to an accessible file.
	 * @param filePath Input filepath, must be wide string!
	 */
	static bool isFileExist(const string &filePath);
	/**
	 * @brief Get File Name from File Path, eg: /example/folder/Hi.txt -> Hi.txt
	 * @param filePath Input filepath, must be wide string!
	 */
	static string getFile(const string &filePath);
	/**
	 * @brief Get File Path in File Manager using index, return empty wide-string if not exist or index is out of bound.
	 * @param idx Index of the file in the vector
	 */
	static string getFile(size_t idx);
	/** @brief Get a list of file's name */
	static vector<string> getFileList();
	/** @brief Set current file idx to target idx */
	static bool setCurrentIdx(size_t idx, bool forceReload = false);
	/** @brief Get current file idx */
	static size_t getCurrentIdx();
	/** @brief Get current file path */
	static string getCurrentFile();
};

#endif //SVG_RENDERING_FILE_MANAGER_H