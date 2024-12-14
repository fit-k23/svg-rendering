#ifndef SVG_RENDERING_STRING_HELPER_H
#define SVG_RENDERING_STRING_HELPER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using std::string;
using std::cout;
using std::cin;

namespace StringHelper{
	/**
	 * Check if input a 32bit character (utf8) is whitespace!
	 * @link https://cplusplus.com/reference/cctype/
	 */
	static bool isUnicodeWhitespace(char32_t ch) {
		return (ch == 0x0009 || // Tab
				ch == 0x000A || // Line feed
				ch == 0x000B || // Vertical tab
				ch == 0x000C || // Form feed
				ch == 0x000D || // Carriage return
				ch == 0x0020 || // Space
				ch == 0x0085 || // Next line
				// ch == 0x00A0 || // Non-breaking space // SVG keeps this?
				(ch >= 0x2000 && ch <= 0x200A) || // En quad, Em quad, En space, etc.
				ch == 0x2028 || // Line separator
				ch == 0x2029 || // Paragraph separator
				ch == 0x202F || // Narrow no-break space
				ch == 0x205F || // Medium mathematical space
				ch == 0x3000);  // Ideographic space
	}

	static inline bool isAnsiUpperAlphabet(char ch) {
		return ch >= 'A' && ch <= 'Z';
	}

	static inline void toLowerAsciiChar(char &ch) {
		if (isAnsiUpperAlphabet(ch)) {
			ch += 32;
		}
	}

	static inline void toLowerAsciiString(string &s) {
		for (char &c : s) {
			toLowerAsciiChar(c);
		}
	}

	static inline void pushEncodeUTF8CharIntoToString(string &s, char32_t ch) {
		if (ch <= 0x7F) { // ASCII
			s.push_back(static_cast<char>(ch));
		} else if (ch <= 0x7FF) { // Two-byte UTF-8
			s.push_back(static_cast<char>(0xC0 | ((ch >> 6) & 0x1F)));
			s.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
		} else if (ch <= 0xFFFF) { // Three-byte UTF-8
			s.push_back(static_cast<char>(0xE0 | ((ch >> 12) & 0x0F)));
			s.push_back(static_cast<char>(0x80 | ((ch >> 6) & 0x3F)));
			s.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
		} else if (ch <= 0x10FFFF) { // Four-byte UTF-8
			s.push_back(static_cast<char>(0xF0 | ((ch >> 18) & 0x07)));
			s.push_back(static_cast<char>(0x80 | ((ch >> 12) & 0x3F)));
			s.push_back(static_cast<char>(0x80 | ((ch >> 6) & 0x3F)));
			s.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
		}
	}

	static string replaceEmptySpacesWithSpace(const string &s) {
		string r;
		r.reserve(s.size());
		bool wasSpace = false;
		for (char32_t c : s) {
			if (isUnicodeWhitespace(c)) {
				if (!wasSpace) {
					r.push_back(' ');
					wasSpace = true;
				}
			} else {
				pushEncodeUTF8CharIntoToString(r, c);
				wasSpace = false;
			}
		}
		return r;
	}
};

#endif //SVG_RENDERING_STRING_HELPER_H