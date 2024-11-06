#ifndef SVG_RENDERING_VIEW_BOX_H
#define SVG_RENDERING_VIEW_BOX_H

class ViewBox{
	float minX;
	float minY;
	float width;
	float height;
public:
	ViewBox();
	ViewBox(float minX, float minY, float width, float height);
	float getMinX() const;
	float getMinY() const;
	float getWidth() const;
	float getHeight() const;
};

#endif //SVG_RENDERING_VIEW_BOX_H
