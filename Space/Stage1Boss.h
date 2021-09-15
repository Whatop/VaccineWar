#pragma once
class Stage1Boss : public Object
{
	Sprite* m_Boss;
	Sprite* Turret[4];
	//

	// Attack
	float AttackTime;
	float DelayTime;
public:
	Stage1Boss();
	~Stage1Boss();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
	void RotationTurret();
	void Attack();
};

