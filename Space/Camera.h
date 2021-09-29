#pragma once

#define CamPos Camera::GetInst()->m_Position

class Camera : public Singleton<Camera>
{
private:
	Matrix mRot;
	Matrix mTrans;
	Matrix mScale;
	Matrix mWorld;
public:
	Camera();
	~Camera();

	float ShakeTimeX;
	float m_Rotation;
	Vec2 m_Position;
	Vec2 m_Scale;

	float XShakePosition;
	Matrix GetWorld()
	{
		return mWorld;
	}

	void Init();
	void Update(float deltaTime, float time);
	void Render();
};
