#include "RenderTexturePool.h"

std::vector<RenderTexture2D> RenderTexturePool::pools = {};
std::vector<Vector2> RenderTexturePool::keys = {};

RenderTexture2D &RenderTexturePool::CreateRenderTexture(int width, int height) {
	RenderTexture2D rt = LoadRenderTexture(width, height);
	pools.push_back(rt);
	keys.push_back({static_cast<float>(width), static_cast<float>(height)});
	return pools[pools.size() - 1];
}

RenderTexture2D &RenderTexturePool::getRenderTexture(int width, int height) {
	int idx = -1;
	for (int i = 0;  i  < keys.size(); ++i) {
		if (width == keys[i].x && height == keys[i].y) {
			idx = i;
			break;
		}
	}
	return idx == -1 ? CreateRenderTexture(width, height) : pools[idx];
}

std::vector<RenderTexture2D> RenderTexturePool::getPools() {
	return pools;
}
