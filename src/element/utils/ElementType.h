#ifndef SVG_RENDERING_ELEMENT_ID_H
#define SVG_RENDERING_ELEMENT_ID_H

enum class ElementType : int{
	Circle,
	Ellipse,
	Group,
	Line,
	Path,
	Polygon,
	Polyline,
	Rectangle,
	Text
};

#include <string>

namespace ElementTypeHelper{
	static std::string getElementTypeName(const ElementType type) {
		switch (type) {
			case ElementType::Circle:
				return "circle";
			case ElementType::Ellipse:
				return "ellipse";
			case ElementType::Group:
				return "group";
			case ElementType::Line:
				return "line";
			case ElementType::Path:
				return "path";
			case ElementType::Polygon:
				return "polygon";
			case ElementType::Polyline:
				return "polyline";
			case ElementType::Rectangle:
				return "rectangle";
			case ElementType::Text:
				return "text";
			default:
				return "unknown";
		}
	}
}

#endif //SVG_RENDERING_ELEMENT_ID_H
