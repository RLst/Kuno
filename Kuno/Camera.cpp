//////////////////
//// Tony Le ////
// 2 Aug 2018 //
///////////////

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

		float mX = (float)input->getMouseX();
		float mY = (float)input->getMouseY();
		float mScroll = (float)input->getMouseScroll();
		float windowWidth = (float)KunoApp::Instance()->getWindowWidth();
		float windowHeight = (float)KunoApp::Instance()->getWindowHeight();

		//// Camera Panning (edge scroll + arrow keys) ////
		//Left Pan
		if (mX < 0 + m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_A))
		{
			x -= m_panSpeed * deltaTime;
		}
		//Right Pan
		if (mX > windowWidth - m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_D))
		{
			x += m_panSpeed * deltaTime;
		}
		//Backwards Pan
		if (mY < 0 + m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_S))
		{
			y -= m_panSpeed * deltaTime;
		}
		//Forward Pan
		if (mY > windowHeight - m_borderZone ||
			input->isKeyDown(aie::INPUT_KEY_W))
		{
			y += m_panSpeed * deltaTime;
		}

		//// Camera Zoom/Scale ////
		auto newScrollPos = input->getMouseScroll();
		auto scrollDiff = newScrollPos - m_lastScrollPos;
		zoom -= (float)scrollDiff * m_zoomSpeedMultiplier * deltaTime;
		m_lastScrollPos = (float)newScrollPos;

		//Clamps
		zoom = pkr::Clamp(zoom, m_maxZoom, m_minZoom);
	}

	void Camera::translate(aie::Renderer2D * renderer)
	{
		renderer->setCameraPos(x, y);
		renderer->setCameraScale(zoom);
	}

}