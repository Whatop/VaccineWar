#pragma once

#define GameInfo GameMgr::GetInst()
#define GetPlayer GameMgr::GetInst()->GetPlayerInfo()

enum class StageScene {
	STAGE1,
	STAGE2,
	NONE
};

struct RankingPlayer
{
public:
	int score;
	std::string name;
};

class GameMgr : public Singleton<GameMgr>
{
	Object* PlayerInfo;

	float MaxHp, Hp;
	float BossMaxHp, BossHp;
	float MiniBossMaxHp, MiniBossHp;
public:
	Sprite* PSprite;
	GameMgr();
	~GameMgr();

	std::vector<RankingPlayer*> Ranks;
	RankingPlayer* m_Rank; // �÷��̾��� ��ũ
	StageScene m_Scene; // ���� ȭ�� ����

	bool m_isCreatePlayer;
	bool m_isCreateUI;
	bool m_DebugMode;

	bool AutoCamera;
	bool CameraStop;

	bool isBossSpawn;
	bool isMiniBossSpawn;

	bool isOneBoss;
	bool isOneMiniBoss;

	bool isSpawnEnemy;

	bool PlayerHit;
	bool  MineDamage;

	bool isScoreScene; // ������ ���� ȭ��

	int MaxScore;
	float m_Score;
	float KillScore, ItemScore, BonusScore;
	
	float m_Money;

	float Player_Coefficient; // �÷��̾� ���ݷ� ���
	
	float Enemy_Coefficient; // �� ���ݷ� ���

	float SpawnDelay;
	float AddDelay;
	
	int ChargeCount;

	bool isNoHit; //����Ʈ ����üũ

	float SKILL_Air_force; 
	float SKILL_Focus_attck;

	bool CK_BossSpawn;
	bool CK_MiniBossSpawn;
	bool CK_GodMode;
	bool CK_TimePause;
	bool isPause;

	int PetCount;

	int EnemyCount;
	Vec2 EnemyPos[10];
	Vec2 CloseEnemie;

	Vec2 BossPosition;
	int StageScore;

	//MachineGun(30)~180, NavalProjectile (5), Torpedo(), Missile;
	int Ammo[4];
	int MaxAmmo[4];
	int PlayerType;

	//������
	bool  isReload;

public:
	void Init();
	void Release();

	void CreateUI();
	void ReleaseUI();

public:
	void CreatePlayer();
	void PlayerDeath();
	Object* GetPlayerInfo() { return PlayerInfo; }
	void PlayerUpdate(Object* obj) { PlayerInfo = obj; }
	void SpriteUpdate(Sprite* obj) { PSprite = obj; }
	void PlayerHpUpdate(float maxhp,float hp) { MaxHp = maxhp, Hp = hp; }
	float GetPlayerMaxHp() { return MaxHp; }
	float GetPlayerHp() { return Hp; }
public:
	void BossHpUpdate(float maxhp,float hp) { BossMaxHp = maxhp, BossHp = hp; }
	void MiniBossHpUpdate(float maxhp,float hp) { MiniBossMaxHp = maxhp, MiniBossHp = hp; }
	float GetBossMaxHp() { return BossMaxHp; }
	float GetBossHp() { return BossHp; }
	float GetMiniBossMaxHp() { return MiniBossMaxHp; }
	float GetMiniBossHp() { return MiniBossHp; }

	void SpawnEnemy();
public:
	void Update();
	void Render();

	void AddScore(int score);
	void RankInit();
	void SortRanking();
	
	void CheatKey();

	void SpawnCoin(Vec2 Pos);
};

