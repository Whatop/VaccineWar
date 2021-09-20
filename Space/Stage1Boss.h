#pragma once
class Stage1Boss : public Object
{
	Sprite* m_Boss;
	Sprite* Turret[7];
	
	float m_Hp, m_MaxHp;

	bool ones;
	bool isDie;
	float NextTime;

	float DamegeCoolTime;

	int EnemyAirTag;
	int EnemyAllTag;

	int constEnemyOcTag;

	int	tempOceanic;
	int	random;

	// Attack
	float AttackTime;
	float DelayTime;//����

	bool isSpawnMove;

	int AttackCount;//����ī��Ʈ 5���߻�-> ���� ü����
	int PatternCount;//����
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

