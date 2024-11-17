#ifndef SVG_RENDERING_LINEARGRADIENT_H
#define SVG_RENDERING_LINEARGRADIENT_H

#include "Gradient.h"
#include "Stop.h"
#include "Vector2D.h"

class LinearGradient : public Gradient {
private:
	Vector2D<float> pos[2];
public:
	LinearGradient(); 

	LinearGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units);

	LinearGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units, Vector2D<float> pos1, Vector2D<float> pos2);

	std::string getType() const override;

	void setPos(int id, const Vector2D<float> &newPos);

	Vector2D<float> getPos(int id) const;
};

#endif // SVG_RENDERING_LINEARGRADIENT_H