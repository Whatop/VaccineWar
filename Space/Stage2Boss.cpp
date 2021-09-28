#include "stdafx.h"
#include "Stage2Boss.h"
#include "Item.h"
#include "EnemyDirBullet.h"
#include "EnemyRotationBullet.h"

Stage2Boss::Stage2Boss(int enemyCount)
{
	m_Boss = Sprite::Create(L"Painting/Boss/Stage2/Boss1.png", D3DCOLOR_XRGB(255, 255, 255));
	m_Boss->SetParent(this);

	WaterEffect = new Animation();
	WaterEffect->Init(0.25f, true);
	WaterEffect->SetParent(this);
	WaterEffect->AddContinueFrame(L"Painting/Boss/Stage2/Boss", 1, 4);

	Turret[0] = new Animation();
	Turret[0] ->Init(0.2f, false);
	Turret[0] ->AddContinueFrame(L"Painting/Boss/Stage2/Gun", 1, 2);

	Turret[1] = new Animation();
	Turret[1] ->Init(0.2f, true);
	Turret[1] ->AddContinueFrame(L"Painting/Boss/Stage2/Turret", 1, 7);
	Turret[0]->SetScale(1.7f, 1.7f);
	Turret[1]->SetScale(1.7f, 1.7f);

	SetScale(1.7f, 1.7f);

	SetPosition(2200+m_Size.x*m_Scale.x, 650);


	m_MaxHp = 2000;
	m_Hp = m_MaxHp;
	m_Speed = 450.f;
	m_Layer = 2;
	std::cout << "보스 공군 생성" << std::endl;

	EnemyOcTag = GameInfo->EnemyTag[1];;
	EnemyAllTag = GameInfo->EnemyTag[0];
	GameInfo->EnemyCount[0]++;
	GameInfo->EnemyCount[1]++;
	GameInfo->EnemyTag[0]++;
	GameInfo->EnemyTag[1]++;


	GameInfo->AllEnemyPos.push_back(Vec2(9999, 9999));
	GameInfo->OceanicPos.push_back(Vec2(9999, 9999));
	ones = true;
	isSpawnMove = true;

	GameInfo->isOneBoss = true;
	GameInfo->isDangerBoss = true;
	GameInfo->isBossSpawn = true;
	Camera::GetInst()->ShakeTimeX = -4.5f;

	DelayTime = 1.f;// 1초
	AttackTime = 1.f;
	PatternCount = 0;
	GameInfo->Level_Petturn=5;
}
Stage2Boss::~Stage2Boss()
{
}

void Stage2Boss::Update(float deltaTime, float Time)
{
	GameInfo->BossHpUpdate(m_MaxHp, m_Hp);
	GameInfo->AllEnemyPos.at(EnemyAllTag) = m_Position;
	GameInfo->OceanicPos.at(EnemyOcTag) = m_Position;
	if (!GameInfo->isPause) {
		if (GameInfo->isBossSpawn) {
			Move();
			if (isSpawnMove) {
				m_Position.x -= 100 * dt;
				if (m_Position.x < 1425 + m_Size.x * m_Scale.x) {
					isSpawnMove = false;
				}
			}
			else {
				ObjMgr->CollisionCheak(this, "Bullet");
				if (Camera::GetInst()->ShakeTimeX > 0.4f) {
					GameInfo->isDangerBoss = false;
				}
				Attack1();
			}
			if (m_Hp <= 0 && !isDie)
			{
				isDie = true;
				ObjMgr->AddObject(new Item(m_Position), "Heal");
				if ((rand() % 30) == 0)
					ObjMgr->AddObject(new Item(m_Position), "Heal");


				GameInfo->MaxScore += 2000;
				GameInfo->KillScore += 2000;
				GameInfo->MaxScore += GameInfo->GetPlayerHp() * GameInfo->Clock / 5;
				GameInfo->BonusScore += GameInfo->GetPlayerHp() * GameInfo->Clock / 5;
				GameInfo->AllEnemyPos.at(EnemyAllTag) = Vec2(9999, 9999);
				GameInfo->OceanicPos.at(EnemyOcTag) = Vec2(9999, 9999);
				GameInfo->EnemyCount[0]--;
				GameInfo->EnemyCount[1]--;
				GameInfo->isBossSpawn = false;
				GameInfo->isOneBoss = true;
			}
			WaterEffect->Update(deltaTime,Time);

		}
		if (isDie) {
			NextTime += dt;
			if ((rand() % 30) == 0)
				ObjMgr->AddObject(new Item(m_Position, 999), "Heal");
			float randx = (rand() % (int)m_Size.x * m_Scale.x) + m_Position.x - m_Size.x / 2 * m_Scale.x;
			float randy = (rand() % (int)m_Size.y * m_Scale.y) + m_Position.y - m_Size.y / 2 * m_Scale.y;

			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Big/", 1, 9, 0.1f, Vec2(randx, randy)), "Effect");

			if (NextTime > 8) {
				GameInfo->isScoreScene = true;
			}
		}
	}
}

void Stage2Boss::Render()
{
	m_Boss->Render();
	WaterEffect->Render();
	Turret[0]->Render();
	Turret[1]->Render();
}

void Stage2Boss::OnCollision(Object* obj)
{
	if (obj->m_Tag == "Bullet") {
		m_Hp -= obj->m_Atk;
		float randx = (rand() % (int)m_Size.x * m_Scale.x) + m_Position.x - m_Size.x / 2 * m_Scale.x;
		float randy = (rand() % (int)m_Size.y * m_Scale.y) + m_Position.y - m_Size.y / 2 * m_Scale.y;
		obj->SetDestroy(true);
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Explosion/", 1, 9, 0.1f, Vec2(randx, randy)), "Effect");
	}
}

void Stage2Boss::Move()
{
	Turret[0]->SetPosition(m_Position);
	Turret[1]->SetPosition(m_Position);
}

void Stage2Boss::Attack1()
{
	AttackTime += dt;
	if (AttackTime > DelayTime) {
		Turret[0]->m_CurrentFrame = 1;
		ObjMgr->AddObject(new EnemyRotationBullet(Vec2(Turret[0]->m_Position.x-80, Turret[0]->m_Position.y+5),D3DXToRadian(-135)), "EnemyBullet");
		AttackTime = 0.25f;
		AttackCount++;
	}
	if(AttackTime > 0.45f)
		Turret[0]->m_CurrentFrame = 0;
}

void Stage2Boss::Attack2()
{
	AttackTime += dt;
	if (AttackTime > DelayTime) {
		
		AttackTime = 0.25f;
		AttackCount++;
	}
	if (AttackTime > 0.45f)
		Turret[0]->m_CurrentFrame = 0;
}

void Stage2Boss::Attack3()
{
	AttackTime += dt;
	if (AttackTime > DelayTime) {
		Turret[0]->m_CurrentFrame = 1;
		ObjMgr->AddObject(new EnemyRotationBullet(Vec2(Turret[0]->m_Position.x - 80, Turret[0]->m_Position.y + 5), D3DXToRadian(-135)), "EnemyBullet");
		AttackTime = 0.25f;
		AttackCount++;
	}
	if (AttackTime > 0.45f)
		Turret[0]->m_CurrentFrame = 0;
}
