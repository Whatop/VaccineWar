#include "stdafx.h"
#include "Stage1.h"
#include "Stage2.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

void Stage2::Init()
{
	ObjMgr->Release();
	GameInfo->Init();

	BGInit();

	m_Cover = Sprite::Create(L"Painting/UI/Cover.png");
	m_Cover->SetPosition(1920 / 2, 1080 / 2);
	m_Cover->m_Visible = false;

	UpWall = Sprite::Create(L"Painting/Wall.png");
	UpWall->SetPosition(1920 / 2, 500);
	UpWall->SetScale(19.2f, 1);

	DownWall = Sprite::Create(L"Painting/Wall.png");
	DownWall->SetPosition(1920 / 2, 1080 + DownWall->m_Size.y / 2);
	DownWall->SetScale(19.2f, 1);

	Left_Limit = Sprite::Create(L"Painting/Wall.png");
	Left_Limit->SetPosition(-50, 1080 / 2);
	Left_Limit->SetScale(1, 10.8f);

	Right_Limit = Sprite::Create(L"Painting/Wall.png");
	Right_Limit->SetPosition(1970, 1080 / 2);
	Right_Limit->SetScale(1, 10.8f);

	ObjMgr->AddObject(UpWall, "Wall");
	ObjMgr->AddObject(DownWall, "Wall");
	ObjMgr->AddObject(Left_Limit, "Wall");
	ObjMgr->AddObject(Right_Limit, "Wall");

	UpWall->m_Visible = false;
	DownWall->m_Visible = false;
	Left_Limit->m_Visible = false;
	Right_Limit->m_Visible = false;

	GameInfo->m_Scene = StageScene::STAGE2;
	GameInfo->ReleaseUI();
	GameInfo->CreateUI();

	if (!GameInfo->m_isCreatePlayer)
		GameMgr::GetInst()->CreatePlayer();

	GameInfo->isSpawnEnemy = false;
}

void Stage2::Release()
{
}

void Stage2::Update(float deltaTime, float time)
{
	GameInfo->CheatKey();
	if (GameInfo->m_Scene == StageScene::STAGE2) {
		if (GameInfo->m_DebugMode) {
			UpWall->m_Visible = true;
			DownWall->m_Visible = true;
			Left_Limit->m_Visible = true;
			Right_Limit->m_Visible = true;
		}
		else {
			UpWall->m_Visible = false;
			DownWall->m_Visible = false;
			Left_Limit->m_Visible = false;
			Right_Limit->m_Visible = false;
		}
		if (!GameInfo->isPause) {
			for (int i = 0; i < 6; i++) {
				if (m_BackGround[i][0]->A < 255)
					m_BackGround[i][0]->A += 1;
				else if (m_BackGround[i][0]->A > 255)
					m_BackGround[i][0]->A = 255;

				if (m_BackGround[i][1]->A < 255)
					m_BackGround[i][1]->A += 1;
				else if (m_BackGround[i][1]->A > 255) {
					m_BackGround[i][1]->A = 255;
				}
			}
			if (sdTime <= 3)
				sdTime += dt;
			if (!one && sdTime > 3) {
				GameInfo->isPause = true;
				one = true;
				sdTime = 4;
			}
			if (!GameInfo->isBossSpawn) {
				MoveBG();
				ResetBG();
			}
			m_Cover->m_Visible = false;
			GameInfo->SpawnEnemy();
		}
		else {
			m_Cover->m_Visible = true;
			if (INPUT->GetButtonDown() || INPUT->GetKey(VK_SPACE) == KeyState::DOWN) {
				GameInfo->isPause = false;
				GameInfo->isSpawnEnemy = true;
				GameInfo->CK_TimePause = false;
				m_Cover = Sprite::Create(L"Painting/UI/Cover1.png");
				m_Cover->SetPosition(1920 / 2, 1080 / 2);
			}
		}

	}
}

void Stage2::Render()
{
	for (int i = 0; i < 6; i++) {
		m_BackGround[i][0]->Render();
		m_BackGround[i][1]->Render();
	}
	m_Cover->Render();

}

void Stage2::BGInit()
{
	for (int i = 0; i < 6; i++) {
		m_BackGround[i][0] = Sprite::Create(L"Painting/GameScreen/Stage2/" + std::to_wstring(i) + L".png");
		m_BackGround[i][0]->SetPosition(1920 / 2, 1080 / 2);
		m_BackGround[i][1] = Sprite::Create(L"Painting/GameScreen/Stage2/" + std::to_wstring(i) + L".png");
		m_BackGround[i][1]->SetPosition(m_BackGround[i][0]->m_Position.x + 1920, 1080 / 2);
		m_BackGround[i][0]->SetScale(1, 1);
		m_BackGround[i][1]->SetScale(1, 1);
		m_BackGround[i][0]->A = 0;
		m_BackGround[i][1]->A = 0;
	}
}

void Stage2::MoveBG()
{
	for (int i = 0; i < 2; i++) {
		m_BackGround[5][i]->m_Position.x -= 10 * dt;
		m_BackGround[4][i]->m_Position.x -= 15 * dt;
		m_BackGround[3][i]->m_Position.x -= 25 * dt;
		m_BackGround[2][i]->m_Position.x -= 50 * dt;
		m_BackGround[1][i]->m_Position.x -= 75 * dt;
		m_BackGround[0][i]->m_Position.x -= 100 * dt;
	}
}

void Stage2::ResetBG()
{
	for (int i = 0; i < 5; i++) {
		if (m_BackGround[i][0]->m_Position.x <= -1920 / 2) {
			m_BackGround[i][0]->m_Position.x = m_BackGround[i][0]->m_Position.x + m_BackGround[0][0]->m_Size.x * 2;
		}
		if (m_BackGround[i][1]->m_Position.x <= -1920 / 2) {
			m_BackGround[i][1]->m_Position.x = m_BackGround[i][1]->m_Position.x + m_BackGround[0][1]->m_Size.x * 2;
		}
	}
}

