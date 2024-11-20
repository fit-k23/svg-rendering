#ifndef SVG_RENDERING_VIEW_BOX_H
#define SVG_RENDERING_VIEW_BOX_H

/**
 * @brief Structure for a view box
 * @param minX minimum x coordinate
 * @param minY minimum y coordinate 
 * @param width minimum width
 * @param height minimum height.
 */
struct ViewBox{
	float minX;
	float minY;
	float width;
	float height;
};

#endif //SVG_RENDERING_VIEW_BOX_H
