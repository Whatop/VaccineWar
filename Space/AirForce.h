#pragma once
class AirForce : public Object
{
	Sprite* m_AirForce;

	float AttackDelay;
	float AttackTime;

	float DestroyTime;
public:
	AirForce();
	~AirForce();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
	void Attack();
};

