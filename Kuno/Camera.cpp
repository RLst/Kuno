#include "Camera.h"
#include <iostream>
#include "imgui\imgui.h"
#include "GameDefines.h"

#include "KunoApp.h"

namespace util {

	void Camera::update(float deltaTime)
	{
		aie::Input * input = aie::Input::getInstance();

		float mouseX = input->getMouseX();
		float mouseY = input->getMouseY();
		float mouseScroll = input->getMouseScroll();
		float windowWidth = KunoApp::getInstance()->getWindowWidth();
		float windowHeight = KunoApp::getInstance()->getWindowHeight();

		////Camera panning (edge + arrow keys)
		//Left Pan
		if (mouseX < 0 + m_edgeScrlSize ||
			input->isKeyDown(aie::INPUT_KEY_LEFT))
		{
			x -= m_scrollSpeed;
		}
		//Right Pan
		if (mouseX > windowWidth - m_edgeScrlSize ||
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
		if (mouseY > windowHeight - m_edgeScrlSize ||
			input->isKeyDown(aie::INPUT_KEY_UP))
		{
			y += m_scrollSpeed;
		}

		//Handle zoom (scale)
		scale -= mouseScroll * m_zoomSpeed;
		if (scale < 1.0f) scale = 1.0f;
		if (scale > 5.0f) scale = 5.0f;

		//// DEBUG ////
		ImGui::Begin("Camera Zoom");
		ImGui::Text("camera.scale = %f", scale);
		ImGui::Text("mouseScroll = %f", mouseScroll);
		ImGui::End();
		///////////////
	}

}