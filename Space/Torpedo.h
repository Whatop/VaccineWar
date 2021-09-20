#pragma once
class Torpedo : public Object
{
	Animation* m_Torpedo;
	Sprite* m_ColBox;

	Vec2 Enemy, Dire, Rad;
	float turnRadian, vrad, Delay;
	float impellent;
	float HomingTime;
	bool isHoming;
	float DestroyTime;
public:
	Torpedo(Vec2 Pos);
	~Torpedo();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);

	void Move();
};

