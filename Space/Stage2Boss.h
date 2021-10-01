#pragma once
class Stage2Boss : public Object
{
	Sprite* m_Boss;
	Animation* WaterEffect;
	Animation* Turret[2];

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

	float BulletRotation;

	bool BUP, BDOWN;
public:
	Stage2Boss(int enemyCount);
	~Stage2Boss();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
	void Attack1();//Gun
	void Attack2();//Missile
	void Attack3();//
};

