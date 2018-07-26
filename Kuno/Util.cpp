#include "Util.h"
#include <iostream>

#include <Texture.h>
#include <Input.h>
#include "KunoApp.h"

#include "imgui/imgui.h"

namespace Util {
	
	Camera::Camera(KunoApp * app) : 
		m_app(app), x(0), y(0), scale(1.0f)
	{
		m_windowWidth = m_app->getWindowWidth();
		m_windowHeight = m_app->getWindowHeight();
		//x = y = 0;
		//scale = 1.0f;
	}

	void Camera::screenToWorld(float & X, float & Y)
	{
		
	}

	void Camera::update(float deltaTime)
	{
		aie::Input * input = aie::Input::getInstance();

		float mouseX = input->getMouseX();
		float mouseY = input->getMouseY();
		float mouseScroll = input->getMouseScroll();
		float scrnWidth = m_app->getWindowWidth();
		float scrnHeight = m_app->getWindowHeight();

		////Camera panning (edge + arrow keys)
		//Left Pan
		if (mouseX < 0 + m_edgeScrlSize || 
			input->isKeyDown(aie::INPUT_KEY_LEFT)) 
		{
			x -= m_scrollSpeed;
		}
		//Right Pan
		if (mouseX > scrnWidth - m_edgeScrlSize ||
			input->isKeyDown(aie::INPUT_KEY_RIGHT)) 
		{
			x += m_scrollSpeed;
		}
		//Backwards Pan
		if (mouseY < 0 + m_edgeScrlSize ||
			input->isKeyDown(aie::INPUT_KEY_DOWN)) 
		{
			y -= m_scrollSpeed;
		}
		//Forward Pan
		if (mouseY > scrnHeight - m_edgeScrlSize ||
			input->isKeyDown(aie::INPUT_KEY_UP)) 
		{
			y += m_scrollSpeed;
		}

		//Handle zoom (scale)
		scale -= mouseScroll * m_zoomSpeed;
		if (scale < 1.0f) scale = 1.0f;
		if (scale > 5.0f) scale = 5.0f;

		ImGui::Begin("Camera Zoom");
		ImGui::Text("camera.scale = %f", scale);
		ImGui::Text("mouseScroll = %f", mouseScroll);
		ImGui::End();
	}
	
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