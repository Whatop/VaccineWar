#include "stdafx.h"
#include "Stage1Boss.h"
#include "Item.h"
#include "EnemyDirBullet.h"
#include "EnemyRotationBullet.h"

Stage1Boss::Stage1Boss(int enemyCount)
{
	m_Boss = Sprite::Create(L"Painting/Boss/Stage1/BossFrame.png", D3DCOLOR_XRGB(255, 255, 255));
	m_Boss->SetParent(this);

	Turret[0] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[1] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[2] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[3] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[4] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[5] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[6] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");

	SetPosition(1920 / 2, -200);
	for (int i = 0; i < 5; i++) {
		Turret[i]->SetScale(1.1f, 1.1f);
	}
	Turret[0]->SetPosition(m_Position.x -300, m_Position.y + m_Size.y / 2 - 50);
	Turret[1]->SetPosition(m_Position.x -200, m_Position.y + m_Size.y / 2 - 50);
	Turret[2]->SetPosition(m_Position.x -100, m_Position.y + m_Size.y / 2 - 50);
	Turret[3]->SetPosition(m_Position.x, m_Position.y + m_Size.y / 2 - 50);
	Turret[4]->SetPosition(m_Position.x + 100, m_Position.y + m_Size.y / 2 - 50);
	Turret[5]->SetPosition(m_Position.x + 200, m_Position.y + m_Size.y / 2 - 50);
	Turret[6]->SetPosition(m_Position.x + 300, m_Position.y + m_Size.y / 2 - 50);

	m_MaxHp = 2000;
	m_Hp = m_MaxHp;
	m_Speed = 450.f; 
	m_Layer = 2;
	std::cout << "보스 공군 생성" << std::endl;

	EnemyAirTag = GameInfo->EnemyTag[2];;
	EnemyAllTag = GameInfo->EnemyTag[0];
	GameInfo->EnemyCount[0]++;
	GameInfo->EnemyCount[2]++;
	GameInfo->EnemyTag[0]++;
	GameInfo->EnemyTag[2]++;


	GameInfo->AllEnemyPos.push_back(Vec2(9999, 9999));
	GameInfo->AerialPos.push_back(Vec2(9999, 9999));
	ones = true;
	SetScale(1.1f, 1.1f);
	isSpawnMove = true;

	GameInfo->isOneBoss = true;
	GameInfo->isDangerBoss = true;
	GameInfo->isBossSpawn = true;
	Camera::GetInst()->ShakeTimeX = -4.5f;
	
	DelayTime = 1.f;// 1초
	AttackTime = 1.f;
	PatternCount = 0;
	GameInfo->Level_Petturn = 5;
}
Stage1Boss::~Stage1Boss()
{
}

void Stage1Boss::Update(float deltaTime, float Time)
{
	GameInfo->BossHpUpdate(m_MaxHp, m_Hp);
	GameInfo->AllEnemyPos.at(EnemyAllTag) = m_Position;
	GameInfo->AerialPos.at(EnemyAirTag) = m_Position;
	if (!GameInfo->isPause) {
		if (GameInfo->isBossSpawn) {
			Move();
			if (isSpawnMove) {
				m_Position.y += 100 * dt;
				if (m_Position.y > 220) {
					isSpawnMove = false;
				}
			}
			else {
				ObjMgr->CollisionCheak(this, "Bullet");
				if (Camera::GetInst()->ShakeTimeX > 0.4f) {
					GameInfo->isDangerBoss = false;
				}
				Attack();
			}
			//220
			if (m_Hp <= 0 && !isDie)
			{
				isDie = true;
				ObjMgr->AddObject(new Item(m_Position), "Heal");
				if ((rand() % 30) == 0)
					ObjMgr->AddObject(new Item(m_Position), "Heal");
				//ObjMgr->RemoveObject(this);


				GameInfo->MaxScore += 2000;
				GameInfo->KillScore += 2000;
				GameInfo->MaxScore += GameInfo->GetPlayerHp() * GameInfo->Clock / 5;
				GameInfo->BonusScore += GameInfo->GetPlayerHp() * GameInfo->Clock / 5;
				GameInfo->AllEnemyPos.at(EnemyAllTag) = Vec2(9999, 9999);
				GameInfo->AerialPos.at(EnemyAirTag) = Vec2(9999, 9999);
				GameInfo->EnemyCount[0]--;
				GameInfo->EnemyCount[2]--;
				GameInfo->isBossSpawn = false;
				GameInfo->isOneBoss = true;
			}
			RotationTurret();
			
		}
		if (isDie) {
			NextTime += dt;
			if ((rand() % 30) == 0)
				ObjMgr->AddObject(new Item(m_Position,999), "Heal");
			float randx = (rand() % (int)m_Size.x * m_Scale.x) + m_Position.x - m_Size.x / 2 * m_Scale.x;
			float randy = (rand() % (int)m_Size.y * m_Scale.y) + m_Position.y - m_Size.y / 2 * m_Scale.y;

			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Big/", 1, 9, 0.1f, Vec2(randx, randy)), "Effect");

			if (NextTime > 8) {
				GameInfo->isScoreScene = true;
			}
		}
	}
}

void Stage1Boss::Render()
{
	m_Boss->Render();
	for (int i = 0; i < 7; i++)
		Turret[i]->Render();

}

void Stage1Boss::OnCollision(Object* obj)
{
	if (obj->m_Tag == "Bullet") {
		m_Hp -= obj->m_Atk;
		float randx = (rand() % (int)m_Size.x * m_Scale.x) + m_Position.x - m_Size.x / 2 * m_Scale.x;
		float randy = (rand() % (int)m_Size.y * m_Scale.y) + m_Position.y - m_Size.y / 2 * m_Scale.y;
		obj->SetDestroy(true);
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Explosion/", 1, 9, 0.1f, Vec2(randx, randy)), "Effect");
	}
}

void Stage1Boss::Move()
{
	Turret[0]->SetPosition(m_Position.x - 370, m_Position.y + m_Size.y / 2 - 50);
	Turret[1]->SetPosition(m_Position.x - 270, m_Position.y + m_Size.y / 2 - 50);
	Turret[2]->SetPosition(m_Position.x - 75, m_Position.y + m_Size.y / 2 - 50);
	Turret[3]->SetPosition(m_Position.x, m_Position.y + m_Size.y / 2 - 50);
	Turret[4]->SetPosition(m_Position.x + 75, m_Position.y + m_Size.y / 2 - 50);
	Turret[5]->SetPosition(m_Position.x + 270, m_Position.y + m_Size.y / 2 - 50);
	Turret[6]->SetPosition(m_Position.x + 370, m_Position.y + m_Size.y / 2 - 50);
}

void Stage1Boss::RotationTurret()
{
	if (AttackCount > 10) {
		int Temp = PatternCount;
		while (Temp == PatternCount)
		{
			PatternCount = rand() % 4;
		}
		if (PatternCount == 3) {
			Turret[0]->m_Rotation = D3DXToRadian(-90);
			Turret[1]->m_Rotation = D3DXToRadian(-90);
			Turret[5]->m_Rotation = D3DXToRadian(90);
			Turret[6]->m_Rotation = D3DXToRadian(90);
		}
		if (PatternCount == 0) {
			Turret[2]->m_Rotation = D3DXToRadian(0);
			Turret[3]->m_Rotation = D3DXToRadian(0);
			Turret[4]->m_Rotation = D3DXToRadian(0);
		}
		AttackCount = 0;
	}
	//모두 타겟팅
	if (PatternCount == 0) {//플레이어 방향으로 발사
		for (int i = 0; i < 7; i++) {
			if (i != 2 && i != 3 && i != 4) {
				Vec2 Dire = Turret[i]->m_Position - GetPlayer->m_Position;
				D3DXVec2Normalize(&Dire, &Dire);
				Turret[i]->m_Rotation = (std::atan2(Dire.y, Dire.x) + D3DXToRadian(90));
			}
		}
		Turret[2]->m_Rotation -= D3DXToRadian(1);
		Turret[3]->m_Rotation -= D3DXToRadian(1);
		Turret[4]->m_Rotation -= D3DXToRadian(1);
	}
	else if (PatternCount == 1) {
		for (int i = 0; i < 7; i++) {
			Vec2 Dire = Turret[i]->m_Position - GetPlayer->m_Position;
			D3DXVec2Normalize(&Dire, &Dire);
			Turret[i]->m_Rotation = (std::atan2(Dire.y, Dire.x) + D3DXToRadian(90));
		}
	}
	else if (PatternCount == 2) {
		Turret[0]->m_Rotation = D3DXToRadian(30);
		Turret[1]->m_Rotation = D3DXToRadian(30);
		Turret[2]->m_Rotation = D3DXToRadian(0);
		Turret[3]->m_Rotation += D3DXToRadian(2);
		Turret[4]->m_Rotation = D3DXToRadian(0);
		Turret[5]->m_Rotation = D3DXToRadian(-30);
		Turret[6]->m_Rotation = D3DXToRadian(-30);
	}
	else if (PatternCount == 3) {
		Turret[0]->m_Rotation -= D3DXToRadian(1);
		Turret[1]->m_Rotation -= D3DXToRadian(1);
		Turret[2]->m_Rotation = D3DXToRadian(0);
		Turret[3]->m_Rotation = D3DXToRadian(0);
		Turret[4]->m_Rotation = D3DXToRadian(0);
		Turret[5]->m_Rotation -= D3DXToRadian(1);
		Turret[6]->m_Rotation -= D3DXToRadian(1);
	}
	
	//공격각도
	//D3DXToRadian(0); 
	//D3DXToRadian(30);
	//D3DXToRadian(60);
	//D3DXToRadian(-30);
	//D3DXToRadian(-60);
}

void Stage1Boss::Attack()
{
	AttackTime += dt;
	if (AttackTime > DelayTime) {
		for (int i = 0; i < 7; i++) {
				ObjMgr->AddObject(new EnemyRotationBullet(Turret[i]->m_Position, Turret[i]->m_Rotation + D3DXToRadian(90)), "EnemyBullet");
				if (PatternCount == 0)
					AttackTime = 0.5f;
				else
					AttackTime = 0.75f;
		}
		AttackCount++;
	}
}
