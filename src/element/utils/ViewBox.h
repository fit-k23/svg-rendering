#ifndef SVG_RENDERING_VIEW_BOX_H
#define SVG_RENDERING_VIEW_BOX_H

/**
 * @brief Structure for a view box
 * @param minX Minimum x coordinate
 * @param minY Minimum y coordinate
 * @param width Viewbox width
 * @param height Viewbox height.
*/
struct ViewBox{
	float minX;
	float minY;
	float width;
	float height;
};

#endif //SVG_RENDERING_VIEW_BOX_H
