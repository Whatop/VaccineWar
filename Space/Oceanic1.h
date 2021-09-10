#pragma once
class Oceanic1 : public Object
{
	Sprite* m_Oceanic1;
	Animation* WaterEffect;
	float m_Hp;

	float MoveTime;
	float m_LastMoveTime;
	float SpawnMove;
	bool ones;
	Vec2 m_RandomPosition;

	float DamegeCoolTime;

	int EnemyTag;
public:
	Oceanic1(Vec2 Pos);
	~Oceanic1();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
};

