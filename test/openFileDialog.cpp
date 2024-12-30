#include <windows.h>
#include <iostream>

using namespace std;

//int main() {
//	OPENFILENAMEA ofn = {sizeof(ofn)};
//	char filename[1024] = {0};
//	ofn.lpstrFile = filename;
//	ofn.nMaxFile = 1024;
//
//	if (!GetOpenFileName(&ofn)) {
//		cout << "GetOpenFileNameA failed!" << endl;
//	}
//
//	cout << "File: " << filename << '\n';
//	system("pause");
//
//	return 0;
//}

int main() {
	OPENFILENAME ofn;

	char szFile[1024];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "SVG files\0*.SVG\0All files\0*.*\0"; // Filter for file types
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "SVG Rendering - G11: Select one or more files";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	if (GetOpenFileNameA(&ofn)) {
		char *file = ofn.lpstrFile;
		char *path = file;
		file += strlen(file) + 1;
		bool multipleFile = false;
		while (*file) {
			multipleFile = true;
			printf("%s\\%s\n", path, file);
			file += strlen(file) + 1; // Move to the next file
		}
		if (!multipleFile) {
			printf("%s\n", path);
		}
	} else {
		DWORD error = CommDlgExtendedError();
		if (error) {
			printf("Error opening file! Error code: %lu\n", error);
		} else {
			printf("No files selected or dialog was canceled.\n");
		}
	}
	system("pause");
	return 0;
}
