#pragma once
class Stage1Boss : public Object
{
	Sprite* m_Boss;
	Sprite* Turret[4];
	
	float m_Hp;

	bool ones;

	float DamegeCoolTime;

	int EnemyAirTag;
	int EnemyAllTag;

	int constEnemyOcTag;

	int	tempOceanic;
	int	random;

	// Attack
	float AttackTime;
	float DelayTime;
public:
	Stage1Boss(int enemyCount);
	~Stage1Boss();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
	void RotationTurret();
	void Attack();
};

