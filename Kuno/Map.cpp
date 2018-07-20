#include "Map.h"
#include "Tile.h"

namespace PF {

Map::~Map()
{
	//Delete tiles
	for (auto &tile : m_tiles) {
		delete tile;
		tile = nullptr;
	}
}
void Map::draw(aie::Renderer2D * renderer)
{
for (auto tile : m_tiles) {
	tile->draw(renderer);
}
}

}
