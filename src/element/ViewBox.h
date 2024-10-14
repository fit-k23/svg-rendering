#ifndef SVG_RENDERING_VIEW_BOX_H
#define SVG_RENDERING_VIEW_BOX_H

class ViewBox{
	float getMinX() const;
	float getMinY() const;
	float getWidth() const;
	float getHeight() const;
private:
	float min_x;
	float min_y;
	float width;
	float height;
};

#endif //SVG_RENDERING_VIEW_BOX_H
