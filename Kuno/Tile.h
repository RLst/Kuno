#pragma once
#include "PF.h"

namespace aie {
	class Texture;
}

namespace pf {

enum eTileType
{
	INACCESSIBLE = 0,
	ACCESSIBLE,
	CLIMBABLE,
	TILETYPE_COUNT		//The total number of tile types
};

class Tile : public Node
{
	//// THE IDEAL TILE ////
	//Iso Tile Width: 100
	//Iso Tile Height: 50
	//Image width: 100
	//Image height: 200
	//

protected:	
	//Texture properties
	aie::Texture*	m_tex = nullptr;
	pkr::Vector2	m_texOffset;

	//Tile properties
	eTileType		m_type;
	//float			m_width;
	//float			m_height;

	//Cartesian World
	pkr::Vector2	m_pos;
	eTileType		m_type;

public:
	///////////////////////
	////PUBLIC VARS
	////Array indices
	//int				X, Y;
	/////////////////////////////

	Tile() = default;
	virtual ~Tile() = default;	//Texture manager will delete the textures

	Tile(pkr::Vector2 position, aie::Texture* tex, pkr::Vector2 texOffset = { 0,0 }, eTileType type = ACCESSIBLE);

	//Accessors
	aie::Texture*	getTexture() const { return m_tex; }
	pkr::Vector2	getTexOffset() const { return m_texOffset; }
	pkr::Vector2	getPosition() const { return m_pos; }

	//Cores
	void			draw(aie::Renderer2D* renderer);
};

}
