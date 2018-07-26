#pragma once

#include <map>
#include <string>
#include <Vector2.h>

//Forward declares
class KunoApp;
namespace aie { 
	class Texture; 
	class Input;
	class Application;
	class Renderer2D;
}

namespace Util {
//Other utilities
	
	class TextureManager 
	{
	private:
		std::map<std::string, aie::Texture*> m_textures;

	public:
		TextureManager() {}
		~TextureManager();		//Must go through std::map and delete all textures
		
		void			addTexture(const char* path);							//Add texture by path
		void			addTexture(const char* name, aie::Texture* texture);	//Add texture by name and tex pointer

		aie::Texture*	getTexture(char* name);							//Retrieves texture
		aie::Texture*	getTextureAuto(char* filename);					//Retrieves texture if available; else attempts to load
	};




};

