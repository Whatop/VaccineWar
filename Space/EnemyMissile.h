#pragma once
class EnemyMissile : public Object
{
	Animation* m_Missile;
	Sprite* m_ColBox;

	Vec2 Enemy, Dire, Rad;
	float turnRadian, vrad, Delay;
	float impellent;
	float HomingTime;
	bool isHoming;
	float DestroyTime;
	bool AllTarget;

	bool one;
public:
	EnemyMissile(Vec2 Pos, float r = 370);
	~EnemyMissile();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);

	void Move();
};
