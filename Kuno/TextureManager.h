//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <pkr\math\Vector2.h>

//Forward declares
namespace aie { 
	class Texture; 
	class Input;
	class Application;
	class Renderer2D;
}

namespace util {
	
	//Texture manager stores textures and can be retrieved on request
	//Saves memory by preventing duplicate texture having to be loaded
	class TextureManager 
	{
	private:
		std::unordered_map<std::string, aie::Texture*> m_textures;	//Unordered is better than map in this case ie. single element access

	public:
		TextureManager() {}
		~TextureManager();		//Must go through std::map and delete all textures
		
		void			addTexture(const char* path);							//Add texture by path
		void			addTexture(const char* name, aie::Texture* texture);	//Add texture by name and tex pointer

		aie::Texture*	getTexture(char* name);							//Retrieves texture
		aie::Texture*	getTextureAuto(char* filename);					//Retrieves texture if available; else attempts to load
	};

};

