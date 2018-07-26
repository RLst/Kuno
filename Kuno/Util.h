#pragma once

#include <map>
#include <string>


//Forward declares
class KunoApp;
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
		KunoApp*		m_app;				//this required to access screen width and height?
		float			m_edgeScrlSize = 30.0f;	//px; Pixels from edge of screen where the mouse will move 
		float			m_scrollSpeed = 100.0f;
		float			m_zoomSpeed = 0.2f;
		int				m_windowWidth;
		int				m_windowHeight;

	public:
		//// PUBLIC!!! ////
		float	x, y;			//px; position
		float	scale;			//arb; scale/zoom
		///////////////////
		
		Camera(KunoApp* app) : m_app(app), x(0), y(0), scale(1.0f) {}

		void	screenToWorld(float &X, float &Y);	//Input screen pos passed in as reference will be converted to world pos 

		void	update(float deltaTime);		//App get's passed in to access window size

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

