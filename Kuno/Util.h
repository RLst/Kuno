#pragma once

#include <map>
#include <string>

namespace aie { class Texture; }

namespace Util {
//Other utilities

	class Camera
	{
	private:
		int scrollZone = 10;	//px; Pixels from edge of screen where the mouse will move 
	public:
		Camera() {}

		//int x, y;		//Positions
		//void update(float deltaTime, aie::Input* input, aie::Application* app)
		//{
		//	if (input)
		//		app->getWindowHeight();


		//	FINISH ME OFF!!
		//}

		void	update(float deltaTime, aie::Input* input, aie::Application* app);		//App get's passed in to access window size


	};


	
	class TextureManager 
	{
	private:
		std::map<std::string, aie::Texture*> m_textures;
	
	public:
		TextureManager() {}
		~TextureManager();
		
		void	addTexture(const char* path);							//Add texture by path
		void	addTexture(const char* name, aie::Texture* texture);	//Add texture by name and tex pointer

		aie::Texture* getTexture(char* name) const;						//Retrieves texture
		aie::Texture* getTextureAuto(char* filename);					//Retrieves texture if available; else attempts to load
	};




};

