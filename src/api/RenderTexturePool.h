#ifndef SVG_RENDERING_RENDER_TEXTURE_POOL_H
#define SVG_RENDERING_RENDER_TEXTURE_POOL_H

#include "../../lib/raylib/raylib.h"

#include <vector>

class RenderTexturePool {
	static std::vector<RenderTexture2D> pools;
	static std::vector<Vector2> keys;
	RenderTexturePool();
public:
	static std::vector<RenderTexture2D> getPools();
	static RenderTexture2D &CreateRenderTexture(int width, int height);
	static RenderTexture2D &getRenderTexture(int width, int height);
};

#endif //SVG_RENDERING_RENDER_TEXTURE_POOL_H
