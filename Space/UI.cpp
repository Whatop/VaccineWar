#include "stdafx.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Init()
{
	PlayerBar = Sprite::Create(L"Painting/UI/Hp.png");
	PlayerBar->SetPosition(390, 35);

	BossBar = Sprite::Create(L"Painting/UI/BossHp.png");
	BossBar->SetPosition(1920 / 2+90, 1080-169/2+10 + 200);
	BossBar->m_Scale.y = 0.9f;
	BossBackGround = Sprite::Create(L"Painting/UI/BossBar1.png");
	BossBackGround->SetPosition(1920 / 2, 1080-169/2 + 200);

	UIScoreFrame = Sprite::Create(L"Painting/UI/Cover.png");
	UIScoreFrame->SetPosition(1920 / 2, 1080 / 2);

	StateWindow = Sprite::Create(L"Painting/UI/Window.png");
	StateWindow->SetPosition(1920 / 2, 72 / 2);
	StateWindow->SetScale(1.5f, 1);
	ScoreImage = Sprite::Create(L"Painting/UI/Money.png");
	ScoreImage->SetPosition(1920 / 2 - 270, 72 / 2);

	HpImage = Sprite::Create(L"Painting/UI/HpUI.png");
	HpImage->SetPosition(130, 35);

	TimeLmitImage = Sprite::Create(L"Painting/UI/timer_f.png");
	TimeLmitImage->SetPosition(1920 / 2 + 600, 72 / 2);

	SpeedImage = Sprite::Create(L"Painting/UI/SpeedBar.png");
	SpeedImage->SetPosition(76 / 2, 72 / 2);

	SpeedFrameImage = Sprite::Create(L"Painting/UI/Speed.png");
	SpeedFrameImage->SetPosition(76 / 2, 72 / 2);
	SpeedFrameImage->m_Rotation = D3DXToRadian(-90);

	GunTpye = Sprite::Create(L"Painting/UI/GunType/0.png");
	GunTpye->SetPosition(320 / 2, 160);

	UIAim = Sprite::Create(L"Painting/UI/Aim.png");
	UIAim->SetPosition(1920 / 2, 700);

	MiniMap[0] = Sprite::Create(L"Painting/UI/MiniMap.png",D3DCOLOR_XRGB(0,0,0));
	MiniMap[0]->SetPosition(1920-390/2 - 10, 155);

	MiniMap[1] = Sprite::Create(L"Painting/UI/MiniMapPlayer.png");
	MiniMap[1]->SetPosition(1920 - 390 / 2-10, 155);

	for (int i = 0; i < 2; i++) {
		Skill_1[0] = Sprite::Create(L"Painting/UI/ShieldSkill.png");
		Skill_1[1] = Sprite::Create(L"Painting/UI/SkillCooldown.png");

		Skill_2[0] = Sprite::Create(L"Painting/UI/airsupport.png");
		Skill_2[1] = Sprite::Create(L"Painting/UI/SkillCooldown.png");

		Skill_1[i]->SetPosition(220 / 2, 1080 - 220 / 2 - 20);
		Skill_1[i]->SetScale(2.f, 2.f);

		Skill_2[i]->SetPosition(320, 1080 - 220 / 2 - 20);
		Skill_2[i]->SetScale(2.f, 2.f);
	}
	Skill_1[1]->m_Rotation = D3DXToRadian(-90);
	Skill_2[1]->m_Rotation = D3DXToRadian(-90);
	//State


	ScoreText = new TextMgr();
	ScoreText->Init(80, true, false, "굴림");
	ScoreText->SetColor(255, 255, 255, 0);

	AmmoText = new TextMgr();
	AmmoText->Init(50, true, false, "굴림");
	AmmoText->SetColor(255, 255, 255, 255);

	ResultScoreText = new TextMgr();
	ResultScoreText->Init(80, true, false, "굴림");
	ResultScoreText->SetColor(255, 255, 255, 0);

	Timelimit = new TextMgr();
	Timelimit->Init(80, true, false, "굴림");
	Timelimit->SetColor(255, 255, 255, 255);

	TestText = new TextMgr();
	TestText->Init(80, true, false, "굴림");
	TestText->SetColor(255, 255, 255, 255);

	ReloadText = new TextMgr();
	ReloadText->Init(30, true, false, "굴림");
	ReloadText->SetColor(255, 255, 255, 255);

	Time[0] = 0;
	Time[1] = 3;
	Time[2] = 0;
	Time[3] = 0;
	Time[4] = 0;
	Time[5] = 0;

	PlayerBar->m_Visible = false;
	BossBar->m_Visible = false;
	BossBackGround->m_Visible = false;
	UIScoreFrame->m_Visible = false;
	memset(limit, 0, sizeof(limit));
	ScoredaleyTime = 0.f;

	ObjMgr->AddObject(MiniMap[0], "UI");
	ObjMgr->AddObject(MiniMap[1], "UI");
	//ObjMgr->AddObject(StateWindow, "UI");
	//ObjMgr->AddObject(SpeedImage, "UI");
	//ObjMgr->AddObject(SpeedFrameImage, "UI");
	//ObjMgr->AddObject(PlayerBar, "UI");
	//ObjMgr->AddObject(HpImage, "UI");
	//ObjMgr->AddObject(TimeLmitImage, "UI");
	//ObjMgr->AddObject(BossBar, "UI");
	//ObjMgr->AddObject(MiniBossBar, "UI");
	//ObjMgr->AddObject(UIScoreFrame, "UI");
	//ObjMgr->AddObject(ScoreImage, "UI");

	GunTpye->A = 0;
	UIAim->A = 0;
	StateWindow->A = 0;
	SpeedImage->A = 0;
	SpeedFrameImage->A = 0;
	PlayerBar->A = 0;
	HpImage->A = 0;
	TimeLmitImage->A = 0;
	UIScoreFrame->A = 0;
	ScoreImage->A = 0;
	BossBackGround->A = 0;
	BossBar->A = 0;
}

void UI::Release()
{
}

void UI::Update()
{
	if (GunTpye->A < 255) {
		GunTpye->A += 1;
		UIAim->A += 1;
		StateWindow->A += 1;
		SpeedImage->A += 1;
		SpeedFrameImage->A += 1;
		PlayerBar->A += 1;
		HpImage->A += 1;
		TimeLmitImage->A += 1;
		UIScoreFrame->A += 1;
		ScoreImage->A += 1;
		BossBackGround->A += 1;
		BossBar->A += 1;
	}
	else {
		GunTpye->A = 255;
		UIAim->A = 255;
		StateWindow->A = 255;
		SpeedImage->A = 255;
		SpeedFrameImage->A = 255;
		PlayerBar->A = 255;
		HpImage->A = 255;
		TimeLmitImage->A = 255;
		UIScoreFrame->A = 255;
		ScoreImage->A = 255;
		BossBackGround->A = 255;
		BossBar->A = 255;
	}
	if (GameInfo->isScoreScene) {
		if (ScoredaleyTime < 4)
			ScoredaleyTime += dt;
		else
			ScoreUI();
	}
	else {
		UIScoreFrame->m_Visible = false;
		ResultScoreText->SetColor(0, 255, 255, 255);
	}
	if (!GameInfo->isPause) {
		Timer();
	
		if (GameInfo->isDangerBoss) {
			BossBackGround->m_Position.y -= 40 * dt;
			BossBar->m_Position.y -= 40 * dt;
			BossBackGround->m_Visible = true;
		}
		if (!GameInfo->isBossSpawn) {
			if (GameInfo->isOneBoss) {
				BossBackGround->m_Position.y += 40 * dt;
				BossBar->m_Position.y += 40 * dt;
				BossBackGround->m_Visible = true;
			}
		}
	}

	if (GameInfo->m_DebugMode) {
		TestText->SetColor(255, 255, 255, 255);
	}
	else {
		TestText->SetColor(0, 255, 255, 255);
	}
	GunTpye = Sprite::Create(L"Painting/UI/GunType/" + std::to_wstring(GameInfo->PlayerType) + L".png");
	GunTpye->SetPosition(320 / 2, 160);
	Vec2 Dire, Enemy, A, B;
	if (GameInfo->PlayerType == 1 || GameInfo->PlayerType == 0) {
		Enemy = GameInfo->CloseEnemy[0] - UIAim->m_Position;
		B = GameInfo->CloseEnemy[0];
	}
	else if (GameInfo->PlayerType == 2 || GameInfo->PlayerType == 3) {
		Enemy = GameInfo->CloseEnemy[GameInfo->PlayerType - 1] - UIAim->m_Position;
		B = GameInfo->CloseEnemy[GameInfo->PlayerType - 1];
	}
	// 적이 있고 플레이어 좋이 머신건 or 함포 상태
	if (GameInfo->EnemyCount[0] > 0 && (GameInfo->PlayerType == 1 || GameInfo->PlayerType == 0)) {

		D3DXVec2Normalize(&Dire, &Enemy);
		A = UIAim->m_Position;
		float limit = (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)) / 500.f);

		if (limit > 0.01f)
			UIAim->Translate(Dire.x * 500.f * dt, Dire.y * 500.f * dt);

	}
	// 모든 적이 없을때
	if (GameInfo->EnemyCount[0] <= 0) {
		Enemy = Vec2(GetPlayer->m_Position.x + 500, GetPlayer->m_Position.y) - UIAim->m_Position;
		B = Vec2(GetPlayer->m_Position.x + 500, GetPlayer->m_Position.y);
		D3DXVec2Normalize(&Dire, &Enemy);
		A = UIAim->m_Position;
		float limit = (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)) / 500.f);

		if (limit > 0.01f)
			UIAim->Translate(Dire.x * 500.f * dt, Dire.y * 500.f * dt);
	}
	// 어뢰이고 바다적이 없는 경우
	if (GameInfo->PlayerType == 2 && GameInfo->EnemyCount[1] == 0) {
		D3DXVec2Normalize(&Dire, &Enemy);
		A = UIAim->m_Position;
		float limit = (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)) / 500.f);

		if (limit > 0.01f)
			UIAim->Translate(Dire.x * 500.f * dt, Dire.y * 500.f * dt);
	}
	else if(GameInfo->PlayerType == 2 && GameInfo->EnemyCount[1] != 0){
		D3DXVec2Normalize(&Dire, &Enemy);
		A = UIAim->m_Position;
		float limit = (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)) / 500.f);

		if (limit > 0.01f)
			UIAim->Translate(Dire.x * 500.f * dt, Dire.y * 500.f * dt);
	}
	// 미사일이고 공중적이 없는 경우
	if (GameInfo->PlayerType == 3 && GameInfo->EnemyCount[2] == 0) {
		Enemy = Vec2(GetPlayer->m_Position.x + 500, GetPlayer->m_Position.y) - UIAim->m_Position;
		B = Vec2(GetPlayer->m_Position.x + 500, GetPlayer->m_Position.y);
		D3DXVec2Normalize(&Dire, &Enemy);
		A = UIAim->m_Position;
		float limit = (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)) / 500.f);

		if (limit > 0.01f)
			UIAim->Translate(Dire.x * 500.f * dt, Dire.y * 500.f * dt);
	}
	else if (GameInfo->PlayerType == 3 && GameInfo->EnemyCount[2] != 0) {
		D3DXVec2Normalize(&Dire, &Enemy);
		A = UIAim->m_Position;
		float limit = (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2)) / 500.f);

		if (limit > 0.01f)
			UIAim->Translate(Dire.x * 500.f * dt, Dire.y * 500.f * dt);
	}

	if (GameInfo->isReload) {
		ReloadText->SetColor(255, 255, 255, 255);
		Reload += dt;
		if (Reload > 0.2f) {
			a += ".";
			Reload = 0.f;
		}
		if (a.size() > 5) {
			a = "";
		}
	}
	else {
		ReloadText->SetColor(0, 255, 255, 255);
	}

	for (int i = 0; i < 2; i++) {
		Skill_1[i]->SetPosition(190 / 2, 330);
		Skill_2[i]->SetPosition(190 / 2, 500);
		Skill_2[i]->SetScale(1.5f, 1.5f);
		Skill_1[i]->SetScale(1.5f, 1.5f);
	}
}


void UI::Render()
{
	GunTpye->Render();
	UIAim->Render();

	StateWindow->Render();
	SpeedImage->Render();
	SpeedFrameImage->Render();
	PlayerBar->Render();
	HpImage->Render();
	TimeLmitImage->Render();
	UIScoreFrame->Render();
	ScoreImage->Render();
	BossBackGround->Render();
	BossBar->Render();

	for (int i = 0; i < 2; i++) {
		Skill_1[i]->Render();
		Skill_2[i]->Render();
	}
	Bar();
	Text();
}

void UI::ScoreUI()
{
	//UIScoreFrame->m_Visible = true;
	if (limit[0] <= 1)
		limit[0] += dt;

	if (limit[0] >= 1 && limit[1] <= 1)
		limit[1] += dt;

	if (limit[1] >= 1 && limit[2] <= 1)
		limit[2] += dt;

	if (limit[2] >= 1 && limit[3] <= 1)
		limit[3] += dt;

	for (int i = 0; i < 4; i++) {
		if (limit[i] > 1)
			limit[i] = 1;
	}
}

void UI::ScoreTextUI()
{
	ResultScoreText->SetColor(255, 255, 255, 255);
	if (limit[0] > 0) {
		ScoreText->print("Kill", 450, 350);
		ScoreText->print("+ " + std::to_string(int(GameInfo->KillScore * limit[0])), 700, 350);
	}
	if (limit[1] > 0) {
		ScoreText->print("Item", 450, 450);
		ScoreText->print("+ " + std::to_string(int(GameInfo->ItemScore * limit[1])), 700, 450);
	}
	if (limit[2] > 0) {
		ScoreText->print("Bonus", 450, 550);
		ScoreText->print("+ " + std::to_string(int(GameInfo->BonusScore * limit[2])), 700, 550);
	}
	if (limit[3] > 0) {
		ScoreText->print("All", 450, 650);
		ScoreText->print("= " + std::to_string(int(GameInfo->m_Score * limit[3])), 700, 650);
	}
}

void UI::Timer()
{
	if (!GameInfo->CK_TimePause) {
		if (Time[1] >= 0) {
			if (Time[1] < 1) {
				Timelimit->SetColor(255, 200, 0, 0);
			}
			if (Time[5] < 0) {
				Time[4] -= 1;
				Time[5] = 9;
			}
			if (Time[4] < 0) {
				Time[3] -= 1;
				Time[4] = 9;
			}
			if (Time[3] < 0) {
				Time[2] -= 1;
				Time[3] = 9;
			}
			if (Time[2] < 0) {
				Time[1] -= 1;
				Time[2] = 5;
			}
			if (Time[1] == 0 && Time[2] == 0 && Time[3] == 0 && Time[4] == 0) {
				Time[1] = 0;
				Time[2] = 0;
				Time[3] = 0;
				Time[4] = 0;
				Time[5] = 0;
			}
			else {
				Time[5] -= 95 * dt;
			}
		}
	}
}

void UI::Bar()
{
	if (GameInfo->m_isCreatePlayer) {
		float m_PlayerHpGage = PlayerBar->m_Size.x / GameInfo->GetPlayerMaxHp();
		int PlayerHp = GameInfo->GetPlayerMaxHp() - GameInfo->GetPlayerHp();
		if (GameInfo->GetPlayerHp() >= 0)
		{
			SetRect(&PlayerBar->m_Collision, PlayerBar->m_Position.x - PlayerBar->m_Size.x / 2, PlayerBar->m_Position.y - PlayerBar->m_Size.y / 2,
				PlayerBar->m_Position.x + PlayerBar->m_Size.x / 2, PlayerBar->m_Position.y + PlayerBar->m_Size.y / 2);

			PlayerBar->m_Rect.right = PlayerBar->m_Size.x - (PlayerHp * m_PlayerHpGage);
			PlayerBar->m_Visible = true;
		}
	}
	if (GameInfo->isBossSpawn) {
		float m_BossHpGage = BossBar->m_Size.x / GameInfo->GetBossMaxHp();
		int BossHp = GameInfo->GetBossMaxHp() - GameInfo->GetBossHp();
		if (GameInfo->GetBossHp() > 0)
		{
			SetRect(&BossBar->m_Collision, BossBar->m_Position.x - BossBar->m_Size.x / 2, BossBar->m_Position.y - BossBar->m_Size.y / 2,
				BossBar->m_Position.x + BossBar->m_Size.x / 2, BossBar->m_Position.y + BossBar->m_Size.y / 2);

			BossBar->m_Rect.right = BossBar->m_Size.x - (BossHp * m_BossHpGage);
			BossBar->m_Visible = true;
		}
		else {
			BossBar->m_Visible = false;
		}
	}
	else {
		BossBar->m_Visible = false;
	}
	
	float SpeedGage = SpeedFrameImage->m_Size.x / 500.f;
	int Speed = 500.f - GetPlayer->m_Speed;
	SetRect(&SpeedFrameImage->m_Collision, SpeedFrameImage->m_Position.x - SpeedFrameImage->m_Size.x / 2, SpeedFrameImage->m_Position.y - SpeedFrameImage->m_Size.y / 2,
		SpeedFrameImage->m_Position.x + SpeedFrameImage->m_Size.x / 2, SpeedFrameImage->m_Position.y + SpeedFrameImage->m_Size.y / 2);

	SpeedFrameImage->m_Rect.right = SpeedFrameImage->m_Size.x - (Speed * SpeedGage);

	if (GameInfo->SKILL_CoolTime[0] >= 0.f) {
		float AttackCoolGage = Skill_1[1]->m_Size.x / 20.f;
		float AttackCoolTime = 20.f - GameInfo->SKILL_CoolTime[0];
		SetRect(&Skill_1[1]->m_Collision, Skill_1[1]->m_Position.x - Skill_1[1]->m_Size.x / 2, Skill_1[1]->m_Position.y - Skill_1[1]->m_Size.y / 2,
			Skill_1[1]->m_Position.x + Skill_1[1]->m_Size.x / 2, Skill_1[1]->m_Position.y + Skill_1[1]->m_Size.y / 2);

		Skill_1[1]->m_Rect.right = Skill_1[1]->m_Size.x - (AttackCoolTime * AttackCoolGage);
	}
	else {
		GameInfo->SKILL_CoolTime[0] = 0.f;
	}
	if (GameInfo->SKILL_CoolTime[1] >= 0.f) {
		float AirCoolGage = Skill_2[1]->m_Size.x / 40.f;
		int AirCoolTime = 40.f - GameInfo->SKILL_CoolTime[1];
		SetRect(&Skill_2[1]->m_Collision, Skill_2[1]->m_Position.x - Skill_2[1]->m_Size.x / 2, Skill_2[1]->m_Position.y - Skill_2[1]->m_Size.y / 2,
			Skill_2[1]->m_Position.x + Skill_2[1]->m_Size.x / 2, Skill_2[1]->m_Position.y + Skill_2[1]->m_Size.y / 2);

		Skill_2[1]->m_Rect.right = Skill_2[1]->m_Size.x - (AirCoolTime * AirCoolGage);
	}
	else {
		GameInfo->SKILL_CoolTime[1] = 0.f;
	}
}

void UI::Text()
{
	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	ScoreText->print(std::to_string(int(GameInfo->m_Score)), 1920 / 2 - 200, -4);
	ScoreTextUI();

	Timelimit->print(
		std::to_string((int)Time[0]) + std::to_string((int)Time[1]) + ":" +
		std::to_string((int)Time[2]) + std::to_string((int)Time[3]) + ":" +
		std::to_string((int)Time[4]) + std::to_string((int)Time[5]), 1600, -4);

	AmmoText->print(
		std::to_string(GameInfo->Ammo[GameInfo->PlayerType])
		+ " / " + std::to_string(GameInfo->MaxAmmo[GameInfo->PlayerType]), 170, 90);

	TestText->print(std::to_string(int(GetPlayer->m_Position.x)) + " / " + std::to_string(int(GetPlayer->m_Position.y)), 1920 / 2, -4);

	ReloadText->print("Reload" + a, GetPlayer->m_Position.x - 40, GetPlayer->m_Position.y - GetPlayer->m_Size.y / 2);

	Renderer::GetInst()->GetSprite()->End();
}
