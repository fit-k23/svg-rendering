#ifndef SVG_RENDERING_FILEMANAGER_H
#define SVG_RENDERING_FILEMANAGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class FileManager{
	static std::vector<std::wstring> filePaths;
	static int current;
public:
	/**
	 * @brief Add file to file manager
	 * @param filePath Input filepath, must be wide string!
	*/
	static bool addFile(const std::wstring &filePath);
	/**
	 * @brief Remove file by searching its name, return false if not exist
	 * @param filePath Input filepath, must be wide string!
	*/
	static bool removeFile(const std::wstring &filePath);
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
	static bool isFileExist(const std::wstring &filePath);
	/**
	 * @brief Get File Name from File Path, eg: /example/folder/Hi.txt -> Hi.txt
	 * @param filePath Input filepath, must be wide string!
	*/
	static std::wstring getFileName(const std::wstring &filePath);
	/**
	 * @brief Get File Path in File Manager using index, return empty wide-string if not exist or index is out of bound.
	 * @param idx Index of the file in the vector
	*/
	static std::wstring getFilePath(size_t idx) ;
	/** @brief Get a list of file's name */
	static std::vector<std::wstring> getFileNameList();
	/** @brief Set current file idx to target idx */
	static void setCurrent(int idx);
	/** @brief Get current file idx */
	static int getCurrent();
};

#endif //SVG_RENDERING_FILEMANAGER_H