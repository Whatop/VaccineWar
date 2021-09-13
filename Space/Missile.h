#pragma once
class Missile : public Object
{
	Animation* m_Missile;
	Sprite* m_ColBox;

	Vec2 Enemy, Dire, Rad;
	float turnRadian, vrad, Delay;
	float impellent;
	float HomingTime;
	float m_Speed;
	bool isHoming;
	float DestroyTime;
	bool AllTarget;
public:
	Missile(Vec2 Pos,bool alltarget = false);
	~Missile();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);

	void Move();
};

