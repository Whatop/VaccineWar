#include"stdafx.h"
#include "Camera.h"
Camera::Camera()
{
	Init();
}

Camera::~Camera()
{
}

void Camera::Init()
{
	m_Rotation = 0;
	m_Position = Vec2(0, 0);
	m_Scale = Vec2(1.f, 1.f);
	ShakeTimeX = 1;
}

void Camera::Update(float deltaTime, float time)
{
	if (m_Rotation >= 360)
		m_Rotation = 0;

	ShakeTimeX += dt;
	if (ShakeTimeX < 0.5f) {
		m_Position.x += (sin(2.0f * 3.14159f * ShakeTimeX * 4) * 3.5f +
			sin(2.0f * 3.14159f * ShakeTimeX * 8 + 0.2f) * 3.4f +
			sin(2.0f * 3.14159f * ShakeTimeX * 16 + 0.5f) * 3.2f) * (5 - ShakeTimeX) / 5;
		if (m_Position.x < 100) {
			m_Position.x += 5 * dt;
		}
	}
	else {
		m_Position.x = 0;
	}
}

void Camera::Render()
{
	D3DXMatrixRotationZ(&mRot, D3DXToRadian(m_Rotation));
	D3DXMatrixTranslation(&mTrans, -m_Position.x, -m_Position.y, 1.f);
	D3DXMatrixScaling(&mScale, m_Scale.x, m_Scale.y, 1.f);

	mWorld = mScale * mRot * mTrans;
}

