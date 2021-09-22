#pragma once
class Stage2Boss : public Object
{
	Sprite* m_Boss;
	Animation* WaterEffect;
	Sprite* Turret[7];

	float m_Hp, m_MaxHp;

	bool ones;
	bool isDie;
	float NextTime;

	float DamegeCoolTime;

	int EnemyOcTag;
	int EnemyAllTag;

	int constEnemyOcTag;

	int	tempOceanic;
	int	random;

	// Attack
	float AttackTime;
	float DelayTime;//공속

	bool isSpawnMove;

	int AttackCount;//어택카운트 5번발사-> 패턴 체인지
	int PatternCount;//패턴
public:
	Stage2Boss(int enemyCount);
	~Stage2Boss();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
	void RotationTurret();
	void Attack();
};

