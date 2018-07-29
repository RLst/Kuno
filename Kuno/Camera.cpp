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
			x -= m_panSpeed * deltaTime;
		}
		//Right Pan
		if (mX > windowWidth - m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_RIGHT))
		{
			x += m_panSpeed * deltaTime;
		}
		//Backwards Pan
		if (mY < 0 + m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_DOWN))
		{
			y -= m_panSpeed * deltaTime;
		}
		//Forward Pan
		if (mY > windowHeight - m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_UP))
		{
			y += m_panSpeed * deltaTime;
		}

		//// Camera Zoom/Scale ////
		auto newScrollPos = input->getMouseScroll();
		auto scrollDiff = newScrollPos - m_lastScrollPos;
		zoom -= (float)scrollDiff * m_zoomSpeedMultiplier * deltaTime;
		m_lastScrollPos = newScrollPos;

		//Clamps
		zoom = pkr::Clamp(zoom, m_maxZoom, m_minZoom);

		////// DEBUG ////
		//ImGui::Begin("Camera Zoom");
		//ImGui::Text("camera.scale: %f", zoom);
		//ImGui::Text("newScrollPos: %f", newScrollPos);
		//ImGui::Text("scrollDiff: %f", scrollDiff);
		//ImGui::Text("lastScrollPos: %f", m_lastScrollPos);
		//ImGui::End();
		/////////////////
	}

	void Camera::translate(aie::Renderer2D * renderer)
	{
		renderer->setCameraPos(x, y);
		renderer->setCameraScale(zoom);
	}

}