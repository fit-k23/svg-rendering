#ifndef SVG_RENDERING_PATH_H
#define SVG_RENDERING_PATH_H

#include "../Element.h"

struct PathPoint {
	char cmd;
	Vector2D<float> pos;
	Vector2D<float> cen[2] = { {}, {} };
	Vector2D<float> radii = { 0.0f, 0.0f };
	float xRotation = 0.0f;
	bool largeArcFlag = false;
	bool sweepFlag = false;

	/** @brief Default constructor for normal point */
	PathPoint(char cmd, const Vector2D<float> &pos) {
		this->cmd = cmd;
		this->pos = pos;
	}

	/** @brief Default constructor for arc point */
	PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> radii, float xRotation, bool largeArcFlag, bool sweepFlag) {
		this->cmd = cmd;
		this->pos = pos;
		this->radii = radii;
		this->xRotation = xRotation;
		this->largeArcFlag = largeArcFlag;
		this->sweepFlag = sweepFlag;
	}

	/** @brief Default constructor for quadratic bezier curve */
	PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> cen) {
		this->cmd = cmd;
		this->pos = pos;
		this->cen[0] = cen;
	}

	/** @brief Default constructor for cubic quadratic bezier curve */
	PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> cen1, Vector2D<float> cen2) {
		this->cmd = cmd;
		this->pos = pos;
		this->cen[0] = cen1;
		this->cen[1] = cen2;
	}

	void output() {
		std::cout << "Cmd: " << cmd << '\n';
		std::cout << "Pos: " << pos.x << ", " << pos.y << '\n';
		std::cout << "Center point: "; 
		for (int i = 0; i < 2; ++i)
			std::cout << "(" << cen[i].x << ", " << cen[i].y << ") ";
		std::cout << '\n';
		std::cout << "radii: " << radii.x << ", " << radii.y << '\n';
		std::cout << "x axis rotation: " << xRotation << '\n';
		std::cout << "largeArcFlag = " << largeArcFlag << '\n' << "sweepFlag = " << sweepFlag << '\n';
	}
};

class SVGPath : public Element{
private:
	std::vector<PathPoint> points;
public:
	/** @brief Default constructor for path */
	SVGPath();

	/**
	 * @brief Parameterized constructor for path
	 * @param points new vector of points
	*/
	SVGPath(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth, const std::vector<PathPoint> &points);


	/**
	 * @brief Get type path
	 * @return ElementType::Path
	 * @note This function is override
	*/
	ElementType getTypeName() override;

	/**
	 * @brief Print all information of path
	 * @note This function is override
	*/
	void dbg() override;

	/**
	 * @brief Get bounding box of path object
	 * @note This function is override and does not change any attributes
	*/
	std::pair<Vector2D<float>, Vector2D<float>> getBoundingBox() const override;
};

#endif //SVG_RENDERING_PATH_H
