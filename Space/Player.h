#pragma once
class Player : public Object
{
	Animation* PlayerPlatform;
	Sprite* m_Player;// = ColBox
	Sprite* m_ColBox;
	Sprite* ColBox[5];// LEFT COLBOX, RIGHT COLBOX, UP COLBOX, DOWN COLBOX, HIT BOX
	Sprite* Shield;

	int LEFT, RIGHT, UP, DOWN, HIT;
	bool isLeft, isRight, isUp, isDown, isHit;

	float m_MaxHp, m_Hp, m_Rpm,m_DelayTime;
	
	bool HitDelay;

	float defenseTime; //�����ð�
	float Damage_Received; // ������
	
	//bool isSlow; GameMgr ����
	float SlowTime;

	// ������
	float ReloadTime;
	bool isReload;
	float chargeTime;

	// ���ǵ�
	bool isSpeed;
	float SpeedTime;
	
	//����
	bool isInvincible;
	float InvincibleTime;

	// �����, ���� , ���, �̻��� 
	//MachineGun, NavalProjectile, Torpedo, Missile;
	//int m_Type; GameMgr ����


public:
	Player(float hp = 100);
	~Player();
	
	//�÷��̾� ���� ������ �� ����ȭ�� �����ϵ��� �Լ������ $
	void Init();
	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);
	void Move();
	void Attack();
	void CollisionBox();
	void GunType();
	void Buff();

	void Skill();


	float RpmDelayTime;
};

