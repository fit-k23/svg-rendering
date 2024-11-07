#include <iostream>
#include <map>
#include <string>

class IParserBase {
public:
	virtual ~IParserBase() = default;
};

template<typename T>
class IParser : public IParserBase {
public:
	virtual T *parse() = 0;
};

class SVGColor {
public:
	void display() const { std::cout << "SVGColor parsed!" << std::endl; }
};

class Circle {
public:
	void display() const { std::cout << "Circle parsed!" << std::endl; }
};

class ColorParser : public IParser<SVGColor> {
public:
	SVGColor *parse() override {
		printf("Called ColorParser\n");
		return new SVGColor();
	}
};

class CircleParser : public IParser<Circle> {
public:
	Circle *parse() override {
		printf("Called CircleParser\n");
		return new Circle();
	}
};

class ParserManager {
private:
	std::map<std::string, IParserBase *> parsers;

public:
	template<typename T>
	void registerParser(const std::string &name, IParser<T> *parser) {
		printf("Registered %s\n", name.c_str());
		parsers[name] = parser;
	}

	template<typename T>
	T *requestToParse(const std::string &name) {
		auto it = parsers.find(name);
		if (it != parsers.end()) {
			auto *parser = dynamic_cast<IParser<T> *>(it->second);
			if (parser) {
				return parser->parse();
			}
		}
		return nullptr;
	}

	~ParserManager() {
		for (auto &entry: parsers) {
			delete entry.second;
		}
	}
};

int main() {
	ParserManager pm;

	pm.registerParser<SVGColor>("color", new ColorParser());
	pm.registerParser<Circle>("circle", new CircleParser());

	auto *color = pm.requestToParse<SVGColor>("color");
	if (color) {
		color->display();
		delete color;
	} else {
		printf("Color not found\n");
	}

	auto *circle = pm.requestToParse<Circle>("circle");
	if (circle) {
		circle->display();
		delete circle;
	} else {
		printf("Circle not found\n");
	}

	return 0;
}
