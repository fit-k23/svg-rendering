#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

using namespace std;

//int main() {
//	const string base("/is/the/speed/of/light/absolute");
//	const string p("D:/is/the/speed/of/light/absolute/or/is/it/relative/to/the/observer");
//	const string p2("C:/little/light/races/in/orbit/of/a/rogue/planet");
//	cout << "Base is base: " << fs::relative(p, base).string() << '\n';
//	cout << "Base is deeper: " << fs::relative(base, p).string() << '\n';
//	cout << "Base is orthogonal: " << fs::relative(string("/") + p2, string("/") + base).string() << '\n';
//	cout << "Base is orthogonal: " << fs::relative(base, p2).string() << '\n';
//}

#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

std::string get_relative_path(const fs::path& path1, const fs::path& path2) {
	// Ensure that both paths are absolute
	if (!fs::absolute(path1).has_root_path() || !fs::absolute(path2).has_root_path()) {
		throw std::invalid_argument("Both paths must be absolute.");
	}

	// Convert paths to canonical form to resolve any potential issues with relative paths
	fs::path p1 = fs::absolute(path1); // Convert path1 to absolute if it isn't already
	fs::path p2 = fs::absolute(path2); // Convert path2 to absolute if it isn't already

	// Find the relative path from p1 to p2
	fs::path relative_path = fs::relative(p1, p2);
	if (relative_path.empty()) {
		return path1.string();
	}

	// Return the relative path as a string
	return relative_path.string();
}

int main() {
	try {
		// Test case 1: C:/Download/ to D:/Dev
		fs::path path1 = "C:/Download/";
		fs::path path2 = "D:/Dev";
		std::cout << "Relative Path: " << get_relative_path(path1, path2) << std::endl;

		// Test case 2: D:/Dev/ to C:/Download/
		path1 = "D:/Dev/";
		path2 = "C:/Download/";
		std::cout << "Relative Path: " << get_relative_path(path1, path2) << std::endl;

		// Test case 3: C:/Download/HelloWorld/test.txt to C:/Download/
		path1 = "C:/Download/HelloWorld/test.txt";
		path2 = "C:/Download/";
		std::cout << "Relative Path: " << get_relative_path(path1, path2) << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}