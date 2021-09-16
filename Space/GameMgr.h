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

	// UI Hpbar
	float MaxHp, Hp;
	float BossMaxHp, BossHp;
	float MiniBossMaxHp, MiniBossHp;
public:
	// PlayerColBox
	Sprite* PSprite;
	GameMgr();
	~GameMgr();

	std::vector<RankingPlayer*> Ranks;
	RankingPlayer* m_Rank; // 플레이어의 랭크
	StageScene m_Scene; // 현제 화면 상태

	// Check
	bool m_isCreatePlayer;
	bool m_isCreateUI;

	// BossCheck
	bool isBossSpawn;
	bool isMiniBossSpawn;
	bool isOneBoss;
	bool isOneMiniBoss;

	// EnemyCheck
	bool isSpawnEnemy;

	// HitCheck
	bool PlayerHit;

	// Obstacle
	bool  MineDamage;
	bool PlayerSlow;
	bool isTrash;

	// 결과 창 ScoreScene
	bool isScoreScene; 

	// Score
	int MaxScore;
	float m_Score;
	float KillScore, ItemScore, BonusScore;

	float Player_Coefficient; // 플레이어 공격력 계수
	
	float Enemy_Coefficient; // 적 공격력 계수

	// EnemySpawn
	float SpawnDelay;
	float AddDelay;

	bool isNoHit; //노히트 판정체크

	//Skill
	float SKILL_Air_force; 
	float SKILL_Focus_attck;

	
	float SKILL_CoolTime[2]; // Focus_attck , Air_Force

	// CheatKey
	bool CK_BossSpawn;
	bool CK_MiniBossSpawn;
	bool CK_GodMode;
	bool CK_TimePause;
	bool isPause;

	bool m_DebugMode;
	bool AutoCamera;
	bool CameraStop;
	
	// EnemyPosition
	std::vector<Vec2> AllEnemyPos;
	std::vector<Vec2> OceanicPos;
	std::vector<Vec2> AerialPos;

	Vec2 CloseEnemy[3];

	int EnemyCount[3];// All, Oc, Air

	int EnemyTag[3];

	float Enemydistance[3];
	float tempdistance[3];

	Vec2 BossPosition;
	int StageScore;

	//MachineGun(30)~180, NavalProjectile (5), Torpedo(), Missile;
	int Ammo[4];
	int MaxAmmo[4];
	int PlayerType;

	//재장전
	bool isReload;

	//pet
	int PetCount;

	//Stage Level Patturn
	int Level_Petturn;
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

	void ClosePosAllEnemy();
	void ClosePosOceanic();
	void ClosePosAerial();
};

