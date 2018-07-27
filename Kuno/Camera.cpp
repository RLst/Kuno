#include "Camera.h"
#include <iostream>
#include "imgui\imgui.h"
#include "GameDefines.h"

#include "KunoApp.h"

namespace util {

	//// Camera ////
	Camera::Camera() :
		x(0), y(0), scale(1.0f)
	{
	}

	pkr::Vector2 Camera::ViewportToCanvas(float viewportX, float viewportY)
	{
		//Init vars for return
		pkr::Vector2 canvas = { 0,0 };

		auto windowWidth = KunoApp::getInstance()->getWindowWidth();
		auto windowHeight = KunoApp::getInstance()->getWindowHeight();

		//Account for scale
		float xPcentage = viewportX / windowWidth;
		float yPcentage = viewportY / windowHeight;

		float scaledWidth = windowWidth * scale;
		float scaledHeight = windowHeight * scale;

		float midX = x + (windowWidth / 2.0f);
		float midY = y + (windowHeight / 2.0f);

		float left = midX - (scaledWidth / 2.0f);
		float bottom = midY - (scaledHeight / 2.0f);

		canvas.x = left + (xPcentage * scaledWidth);
		canvas.y = bottom + (yPcentage * scaledHeight);

		return canvas;
	}

	void Camera::testViewportToCanvas(aie::Renderer2D * renderer)
	{
		aie::Input* input = aie::Input::getInstance();

		//Get mouse position in window coords
		float windowX = input->getMouseX();
		float windowY = input->getMouseY();

		//Transform from window coords to canvas coords
		pkr::Vector2 canvas = ViewportToCanvas(windowX, windowY);

		renderer->setRenderColour(0.25f, 1, 0.25f);
		renderer->drawCircle(canvas.x, canvas.y, 50.0f);

		//// DEBUG ////
		ImGui::Begin("WindowToCanvas(test)");
		ImGui::Text("Before > X: %f, Y: %f", windowX, windowY);
		ImGui::Text("After > X: %f, Y: %f", canvas.x, canvas.y);
		ImGui::End();
		//////////////
	}

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