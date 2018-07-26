#include "Camera.h"
#include <iostream>
#include "imgui\imgui.h"

#include "KunoApp.h"

namespace Util {

	//// Camera ////
	Camera::Camera(KunoApp * app) :
		m_app(app), x(0), y(0), scale(1.0f)
	{
		m_windowWidth = m_app->getWindowWidth();
		m_windowHeight = m_app->getWindowHeight();
		//x = y = 0;
		//scale = 1.0f;
	}

	pkr::Vector2 Camera::WindowToCanvas(float & windowX, float & windowY)
	{
		//Init vars for return
		pkr::Vector2 canvasCoord = { 0,0 };

		//Get the screen/window position (Done! windowX and windowY)

		//Transpose/Convert/Project into canvas coordinates
		//Adjust for camera scale/zoom
		//canvasCoord.x = 



		//Return canvas coords

		return pkr::Vector2();
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

	void Camera::testWindowToCanvas(aie::Renderer2D * renderer)
	{
		aie::Input* input = aie::Input::getInstance();

		float mousex = input->getMouseX();
		float mousey = input->getMouseY();



	}

}