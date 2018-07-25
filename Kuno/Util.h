#pragma once

#include <map>
#include <string>

#

namespace aie { 
	class Texture; 
	class Input;
	class Application;
}

namespace Util {
//Other utilities

	class Camera
	{
	private:
		aie::Application*	m_app;
		int					m_scrollZone = 10;	//px; Pixels from edge of screen where the mouse will move 

	public:
		//// PUBLIC!!! ////
		float			x, y;			//px; position
		float			scale;			//arb; scale/zoom
		///////////////////
		
		Camera(aie::Application *app) : m_app(app), x(0), y(0), scale(1.0f) {}

		void	screenToWorld(float &X, float &Y);	//Input screen pos passed in as reference will be converted to world pos 

		void	update(float deltaTime, aie::Application* app);		//App get's passed in to access window size

		//pkr::Vector2	m_position = { 0,0 };
		//void update(float deltaTime, aie::Input* input, aie::Application* app)
		//{
		//	if (input)
		//		app->getWindowHeight();
		//	FINISH ME OFF!!
		//}
	};


	
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

