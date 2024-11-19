#ifndef SVG_RENDERING_RADIALGRADIENT_H
#define SVG_RENDERING_RADIALGRADIENT_H

#include "Gradient.h"
#include "Stop.h"
#include "Vector2D.h"

class RadialGradient : public Gradient {
private:
	Vector2D<float> pos;
	float radius;
	Vector2D<float> focal;
public:
	RadialGradient();

	RadialGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units);

	RadialGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units, const Vector2D<float> &pos, float radius, const Vector2D<float> &focal);

	std::string getType() const override;

	void dbg() const override;

	void setPos(const Vector2D<float>& pos);

	Vector2D<float> getPos() const;

	void setRadius(float radius);

	float getRadius() const;

	void setFocal(const Vector2D<float>& focal);

	Vector2D<float> getFocal() const;
};


#endif // SVG_RENDERING_RADIALGRADIENT_H