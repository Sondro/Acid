﻿#include "overlaydebug.hpp"

OverlayDebug::OverlayDebug(UiObject *parent) :
	UiObject(parent, Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f))
{
	m_textHeight = CreateStatus("HEIGHT: 0.0", 0.005f, 0.86f, LEFT);
	m_textTime = CreateStatus("TIME: 0.0", 0.005f, 0.89f, LEFT);
	m_textPosition = CreateStatus("POSITION: 0.0, 0.0, 0.0", 0.005f, 0.92f, LEFT);
	m_textFps = CreateStatus("FPS: 0", 0.005f, 0.95f, LEFT);
	m_textUps = CreateStatus("UPS: 0", 0.005f, 0.98f, LEFT);
	m_timerUpdate = new Timer(0.333f);
}

OverlayDebug::~OverlayDebug()
{
	delete m_textFps;
	delete m_textUps;
}

void OverlayDebug::UpdateObject()
{
	if (m_timerUpdate->IsPassedTime())
	{
		m_timerUpdate->ResetStartTime();

		if (terrains::get() != nullptr)
		{
			float terrainHeight = 0.0f; //  terrains::get()->getTerrain()->getHeight(position->m_x, position->m_z);
			m_textHeight->setText("HEIGHT: " + std::to_string(Maths::RoundToPlace(terrainHeight, 2)));
		}

		if (Worlds::Get() != nullptr)
		{
			m_textTime->setText("TIME: " + std::to_string(static_cast<int>(Worlds::Get()->GetDayFactor() * 100.0f)) + "%");
		}

		if (Camera::Get() != nullptr)
		{
			Vector3 *position = Camera::Get()->GetCamera()->GetPosition();
			m_textPosition->setText("POSITION: " + std::to_string(static_cast<int>(position->m_x)) + ", " + std::to_string(static_cast<int>(position->m_y)) + ", " + std::to_string(static_cast<int>(position->m_z)));
		}

		m_textFps->setText("FPS: " + std::to_string(static_cast<int>(1.0 / Engine::Get()->GetDeltaRender())));
		m_textUps->setText("UPS: " + std::to_string(static_cast<int>(1.0 / Engine::Get()->GetDelta())));
	}
}

text *OverlayDebug::CreateStatus(const std::string &content, const float &positionX, const float &positionY, const uialign &align)
{
	text *result = new text(this, Vector2(positionX, positionY), content, 1.0f, uis::get()->m_candara, 1.0f, align);
	result->SetInScreenCoords(true);
	result->setTextColour(Colour(1.0f, 1.0f, 1.0f, 1.0f));
	result->setBorderColour(Colour(0.15f, 0.15f, 0.15f, 1.0f));
	result->setBorder(new driverconstant(0.04f));
	return result;
}
