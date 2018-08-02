//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////


#include "TextureManager.h"
#include <iostream>

#include <Texture.h>

#include "imgui/imgui.h"

namespace util {
	
	//// Texture Manager ////
	TextureManager::~TextureManager()
	{		
		//Delete all textures
		for (auto t : m_textures) {
			aie::Texture* tex = t.second;
			delete tex;
		}
	}

	void TextureManager::addTexture(const char* path)
	{
		aie::Texture* tex = new aie::Texture(path);
		
		if (tex != nullptr) {
			//Texture exists so load into manager
			m_textures[path] = tex;
		}
		else {	
			//Texture doesn't exist, notify
			std::cout << "Error loading texture!" << std::endl;
		}
	}

	void TextureManager::addTexture(const char * name, aie::Texture * texture)
	{
		if (texture != nullptr) {
			//Texture exists so load into manager
			m_textures.insert_or_assign(name, texture);
			//m_textures[name] = texture;
		}
		else {
			//Texture doesn't exist, notify
			std::cout << "Error loading texture!" << std::endl;
		}
	}

	aie::Texture * TextureManager::getTexture(char * name)
	{
		//Attempt to retrive texture from map
		aie::Texture* load = m_textures[name];

		//Check if it's available
		if (load != nullptr)
			return load;
		else //Error and assert
			std::cout << "Texture doesn't exist!" << std::endl;

		return nullptr;
	}

	aie::Texture * TextureManager::getTextureAuto(char * filename)
	{
		//Borrowed from cbrwn
		const char* fileNameTemplate = "./textures/%s.png";

		aie::Texture* loaded = m_textures[filename];
		if (loaded == nullptr)
		{
			const int fileNameSize = 512;
			// texture doesn't exist - try loading
			char fileName[fileNameSize];
			sprintf_s(fileName, fileNameSize, fileNameTemplate, filename);
			aie::Texture* tex = new aie::Texture(fileName);
			if (tex != nullptr)
			{
				m_textures[filename] = tex;
				return tex;
			}
			else
			{
				// wasn't found!
				printf("Texture named %s was not found!\n", filename);
				return nullptr;
			}
		}
		else
		{
			return loaded;
		}
	}
}