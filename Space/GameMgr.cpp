#include "stdafx.h"
#include "GameMgr.h"
#include "UI.h"
#include "Item.h"

#include "MainScene.h"
#include "Stage1.h"
#include "Stage2.h"

#include "Oceanic1.h"
#include "AerialEnemy1.h"
#include "Stage1Boss.h"

#include "Obstacle.h"

#include <algorithm>

GameMgr::GameMgr()
{
}

GameMgr::~GameMgr()
{
}

void GameMgr::Init()
{
	m_isCreateUI = false;
	m_DebugMode = false;
	m_isCreatePlayer = false;
	AutoCamera = true;
	CameraStop = false;

	EnemyCount[0] = 0;
	EnemyCount[1] = 0;
	EnemyCount[2] = 0;
	EnemyAllTag = 0;

	SpawnDelay = 0.f;
	AddDelay = 0.f;

	isOneBoss = true;
	isOneMiniBoss = true;

	BossMaxHp = 0, BossHp = 0;
	MiniBossMaxHp = 0, MiniBossHp = 0;
	Player_Coefficient = 1.f;
	isSpawnEnemy = false;

	StageScore = m_Score; // 스테이지 넘어갈때마다 저장

	KillScore = 0.f;
	ItemScore = 0.f;
	BonusScore = 0.f;

	PetCount = 0;
	
	CK_TimePause = true;
	isPause = false;

	//추가 치트키
	CK_MiniBossSpawn = false;
	CK_BossSpawn = false;
	CK_GodMode = false;
	// 보스 잡고 점수화면 
	isScoreScene = false;
	Ammo[0] = 30;
	Ammo[1] = 5;
	Ammo[2] = 5;
	Ammo[3] = 3;

	MaxAmmo[0] = 30;
	MaxAmmo[1] = 5;
	MaxAmmo[2] = 5;
	MaxAmmo[3] = 3;

	SKILL_CoolTime[0] = 0.f;
	SKILL_CoolTime[1] = 0.f;


	AllEnemyPos.clear();
	OceanicPos.clear();
	AerialPos.clear();

}

void GameMgr::Release()
{
}

void GameMgr::CreateUI()
{
	if (!m_isCreateUI)
	{
		UI::GetInst()->Init();
		m_isCreateUI = true;
		std::cout << "UI 생성" << std::endl;
	}
}

void GameMgr::ReleaseUI()
{
	UI::GetInst()->Release();
	UI::GetInst()->ReleaseInst();
	m_isCreateUI = false;
	std::cout << "UI 삭제" << std::endl;
}

void GameMgr::CreatePlayer()
{
	if (GameInfo->m_Scene == StageScene::STAGE1)
		ObjMgr->AddObject(new Player(), "Player");
	else
		ObjMgr->AddObject(new Player(Hp), "Player");

	m_isCreatePlayer = true;
}

void GameMgr::PlayerDeath()
{
	m_isCreatePlayer = false;
	ObjMgr->DeleteObject("Player");
	ObjMgr->DeleteObject("pBullet");
}


void GameMgr::Update()
{
	if (m_isCreateUI)
		UI::GetInst()->Update();

	AddScore(MaxScore);
	ClosePosAllEnemy();
	ClosePosOceanic();
	ClosePosAerial();
	
}

void GameMgr::Render()
{
	if (m_isCreateUI)
		UI::GetInst()->Render();
}


void GameMgr::AddScore(int maxscore)
{
	if (int(m_Score) < maxscore) {
		if (int(m_Score) + 4000 < maxscore)
			m_Score += 90;

		else
			m_Score += 10;
	}
	else if (int(m_Score) > maxscore) {
		m_Score = maxscore;
	}
}

void GameMgr::RankInit()
{
	RankingPlayer* dummy1 = new RankingPlayer();
	dummy1->name = "dummy1";
	dummy1->score = rand() % 10000;;

	RankingPlayer* dummy2 = new RankingPlayer();
	dummy2->name = "dummy2";
	dummy2->score = rand() % 10000;;

	RankingPlayer* dummy3 = new RankingPlayer();
	dummy3->name = "dummy3";
	dummy3->score = rand() % 10000;

	m_Rank = new RankingPlayer();
	m_Rank->name = "Player(Temp)";
	m_Rank->score = 0;

	Ranks.push_back(dummy1);
	Ranks.push_back(dummy2);
	Ranks.push_back(dummy3);
	Ranks.push_back(m_Rank);
	m_Score = 0;

}

bool Sort(const RankingPlayer* pSour, const RankingPlayer* pDest)
{
	return (pSour->score > pDest->score);
}

void GameMgr::SortRanking()
{
	std::sort(Ranks.begin(), Ranks.end(), Sort);
}

void GameMgr::CheatKey()
{
	if (INPUT->GetKey('D') == KeyState::DOWN) {
		//Camera::GetInst()->ShakeTimeY = 0.f;
		Camera::GetInst()->ShakeTimeX = 0.3f;
	}
	if (!isPause && !GameInfo->isReload) {
		if (INPUT->GetKey('1') == KeyState::DOWN) {
			PlayerType = 0;
		}
		if (INPUT->GetKey('2') == KeyState::DOWN) {
			PlayerType = 1;
		}
		if (INPUT->GetKey('3') == KeyState::DOWN) {
			PlayerType = 2;
		}
		if (INPUT->GetKey('4') == KeyState::DOWN) {
			PlayerType = 3;
		}
	}
	//Camera::GetInst()->isVibration = true;
	//Camera::GetInst()->ShakeTimeY = 0;

	//Camera::GetInst()->isVibration = true;
	//Camera::GetInst()->ShakeTimeX = 0; 

	//ObjMgr->AddObject(new Item(Vec2(Camera::GetInst()->m_Position.x + 1500, 350)), "Heal");

	//	MaxScore += 3000;

	if (INPUT->GetKey('V') == KeyState::DOWN)
	{
		if (m_DebugMode)
		{
			m_DebugMode = false;

			std::cout << "디버깅 모드 비 활성화" << std::endl;
		}
		else if (!m_DebugMode)
		{
			m_DebugMode = true;
			std::cout << "디버깅 모드 활성화" << std::endl;
		}
	}

	if (INPUT->GetKey(VK_F1) == KeyState::DOWN) {
		if (CK_GodMode)
		{
			CK_GodMode = false;
			std::cout << "무적 비 활성화" << std::endl;
		}
		else if (!CK_GodMode)
		{
			CK_GodMode = true;
			std::cout << "무적 활성화" << std::endl;
		}
	}
	if (INPUT->GetKey(VK_F2) == KeyState::DOWN) {
		if (isPause)
		{
			isPause = false;
			std::cout << "일시정지 비 활성화" << std::endl;
		}
		else if (!isPause)
		{
			isPause = true;
			std::cout << "일시정지 활성화" << std::endl;
		}
	}
	if (INPUT->GetKey(VK_F3) == KeyState::DOWN) {
		if (CK_TimePause)
		{
			CK_TimePause = false;
			std::cout << "제한시간 비 활성화" << std::endl;
		}
		else if (!CK_TimePause)
		{
			CK_TimePause = true;
			std::cout << "제한시간 활성화" << std::endl;
		}
	}
	if (INPUT->GetKey(VK_F4) == KeyState::DOWN && m_Scene != StageScene::NONE) {
		SceneDirector::GetInst()->ChangeScene(new MainScene());
	}
	else if (INPUT->GetKey(VK_F5) == KeyState::DOWN && m_Scene != StageScene::STAGE1) {
		SceneDirector::GetInst()->ChangeScene(new Stage1());
	}
	else if (INPUT->GetKey(VK_F6) == KeyState::DOWN && m_Scene != StageScene::STAGE2) {
		SceneDirector::GetInst()->ChangeScene(new Stage2());
	}
}

void GameMgr::ClosePosAllEnemy()
{
	if (!AllEnemyPos.empty()) {
		for (int i = 0; i < AllEnemyPos.size(); i++) {
			tempdistance[0] =
				sqrt(pow(PlayerInfo->m_Position.x - AllEnemyPos.at(i).x, 2)
					+ pow(PlayerInfo->m_Position.y - AllEnemyPos.at(i).y, 2));
			if (Enemydistance[0] > tempdistance[0]) {
				Enemydistance[0]= tempdistance[0];
				CloseEnemy[0] = AllEnemyPos.at(i);
			}
		}
		Enemydistance[0] = 99999;
	}
}

void GameMgr::ClosePosOceanic()
{
	if (!OceanicPos.empty()) {
		for (int i = 0; i < OceanicPos.size(); i++) {
			tempdistance[1] =
				sqrt(pow(PlayerInfo->m_Position.x - OceanicPos.at(i).x, 2)
					+ pow(PlayerInfo->m_Position.y - OceanicPos.at(i).y, 2));
			if (Enemydistance[1] > tempdistance[1]) {
				Enemydistance[1] = tempdistance[1];
				CloseEnemy[1] = OceanicPos.at(i);
			}
		}
		Enemydistance[1] = 99999;
	}
}

void GameMgr::ClosePosAerial()
{
	if (!AerialPos.empty()) {
		for (int i = 0; i < AerialPos.size(); i++) {
			tempdistance[2] =
				sqrt(pow(PlayerInfo->m_Position.x - AerialPos.at(i).x, 2)
					+ pow(PlayerInfo->m_Position.y - AerialPos.at(i).y, 2));
			if (Enemydistance[2] > tempdistance[2]) {
				Enemydistance[2] = tempdistance[2];
				CloseEnemy[2] = AerialPos.at(i);
			}
		}
		Enemydistance[2] = 99999;
	}
}

void GameMgr::SpawnEnemy()
{
	if (isSpawnEnemy) {
		SpawnDelay += dt;
		if (SpawnDelay > 4) {

			ObjMgr->AddObject(new AerialEnemy1(Vec2(2000, rand() % 492+73), 0), "Enemy");
			ObjMgr->AddObject(new Stage1Boss(1), "Enemy");

			ObjMgr->AddObject(new Oceanic1(Vec2(2000, rand() % 492+540), 0), "Enemy");
			ObjMgr->AddObject(new Oceanic1(Vec2(2000, rand() % 492+540), 1), "Enemy");
			ObjMgr->AddObject(new Oceanic1(Vec2(2000, rand() % 492+540), 2), "Enemy");
			if(rand()%2==0)
				ObjMgr->AddObject(new Obstacle(Vec2(2000, rand() % 200+700), true), "Mine");
			else 
				ObjMgr->AddObject(new Obstacle(Vec2(2000, rand() % 200 + 700), false), "Trash");

			//ObjMgr->AddObject(new Obstacle(Vec2(2000, 700), false), "Mine");
			SpawnDelay = -100000.f;
		}
	}
}
