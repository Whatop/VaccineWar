#pragma once
class AerialEnemy1 : public Object
{
	Sprite* m_AerialEnemy1;
	Animation* HelicopterWing;
	Animation* HelicopterBackWing;
	float m_Hp;

	float MoveTime;
	float m_LastMoveTime;
	float SpawnMove;
	bool ones;
	Vec2 m_RandomPosition;

	float DamegeCoolTime;

	int EnemyAirTag;
	int EnemyAllTag;

	int constEnemyOcTag;

	int	tempOceanic;
	int	random;
public:
	AerialEnemy1(Vec2 Pos, int enemyCount);
	~AerialEnemy1();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
};

