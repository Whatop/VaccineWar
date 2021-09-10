#pragma once
class Player : public Object
{
	Animation* PlayerPlatform;
	Sprite* m_Player;// = ColBox
	Sprite* m_ColBox;
	Sprite* ColBox[5];// LEFT COLBOX, RIGHT COLBOX, UP COLBOX, DOWN COLBOX, HIT BOX

	int LEFT, RIGHT, UP, DOWN, HIT;
	bool isLeft, isRight, isUp, isDown, isHit;

	float m_MaxHp, m_Hp, m_Rpm,m_DelayTime;
	
	bool HitDelay;

	float defenseTime; //무적시간
	float Damage_Received; // 데미지
	bool isSlow;
	float SlowTime;

	//재장전
	float ReloadTime;
	bool isReload;

	// 기관총, 함포 , 어뢰, 미사일 
	//MachineGun, NavalProjectile, Torpedo, Missile;
	//int m_Type; GameMgr 관리
public:
	Player(float hp = 100);
	~Player();
	
	//플레이어 등장 움직임 후 선택화면 생성하도록 함수만들기 $
	void Init();
	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);
	void Move();
	void Attack();
	void CollisionBox();
	void GunType();
	void Buff();

	float RpmDelayTime;
};

