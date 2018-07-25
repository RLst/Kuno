#include "Util.h"
#include <iostream>

#include <Texture.h>
#include <Input.h>
#include <Application.h>

namespace Util {
	
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
			m_textures[name] = texture;
		}
		else {
			//Texture doesn't exist, notify
			std::cout << "Error loading texture!" << std::endl;
		}
	}

	aie::Texture * TextureManager::getTexture(char * name) const
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

	void Camera::update(float deltaTime, aie::Input * input, aie::Application * app)
	{
		//Handles moving the camera
		//
		////Left edge
		//if (input->getMouseX() )




	}
}