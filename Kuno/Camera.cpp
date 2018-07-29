#include "Camera.h"
#include <iostream>
#include "imgui\imgui.h"
#include "GameDefines.h"

#include "KunoApp.h"

namespace util {
	Camera::Camera(float x, float y, float zoom) :
		x(x), y(y), zoom(zoom)
	{}

	void Camera::update(float deltaTime)
	{
		aie::Input * input = aie::Input::getInstance();

		float mX = input->getMouseX();
		float mY = input->getMouseY();
		float mScroll = input->getMouseScroll();
		float windowWidth = KunoApp::Instance()->getWindowWidth();
		float windowHeight = KunoApp::Instance()->getWindowHeight();

		//// Camera Panning (edge scroll + arrow keys) ////
		//Left Pan
		if (mX < 0 + m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_LEFT))
		{
			x -= m_panSpeed;
		}
		//Right Pan
		if (mX > windowWidth - m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_RIGHT))
		{
			x += m_panSpeed;
		}
		//Backwards Pan
		if (mY < 0 + m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_DOWN))
		{
			y -= m_panSpeed;
		}
		//Forward Pan
		if (mY > windowHeight - m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_UP))
		{
			y += m_panSpeed;
		}

		//// Camera Zoom/Scale ////
		auto newScrollPos = input->getMouseScroll();
		auto scrollDiff = newScrollPos - m_lastScrollPos;
		zoom -= (float)scrollDiff * m_zoomSpeedMultiplier;
		m_lastScrollPos = newScrollPos;

		//Clamps
		zoom = pkr::Clamp(zoom, 0.5f, 5.0f);

		////// DEBUG ////
		//ImGui::Begin("Camera Zoom");
		//ImGui::Text("camera.scale: %f", zoom);
		//ImGui::Text("newScrollPos: %f", newScrollPos);
		//ImGui::Text("scrollDiff: %f", scrollDiff);
		//ImGui::Text("lastScrollPos: %f", m_lastScrollPos);
		//ImGui::End();
		/////////////////
	}

}