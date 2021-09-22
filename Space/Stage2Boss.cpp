#include "stdafx.h"
#include "Stage2Boss.h"
#include "Item.h"
#include "EnemyDirBullet.h"
#include "EnemyRotationBullet.h"

Stage2Boss::Stage2Boss(int enemyCount)
{
	m_Boss = Sprite::Create(L"Painting/Boss/Stage2/Boss.png", D3DCOLOR_XRGB(255, 255, 255));
	m_Boss->SetParent(this);

	WaterEffect = new Animation();
	WaterEffect->Init(0.2f, true);
	WaterEffect->SetParent(this);
	WaterEffect->AddContinueFrame(L"Painting/Boss/Stage2/Boss", 1, 4);

	SetPosition(1920-m_Size.x, 800);

	m_MaxHp = 2000;
	m_Hp = m_MaxHp;
	m_Speed = 450.f;
	m_Layer = 2;
	std::cout << "보스 공군 생성" << std::endl;

	EnemyOcTag = GameInfo->EnemyTag[2];;
	EnemyAllTag = GameInfo->EnemyTag[0];
	GameInfo->EnemyCount[0]++;
	GameInfo->EnemyCount[2]++;
	GameInfo->EnemyTag[0]++;
	GameInfo->EnemyTag[2]++;


	GameInfo->AllEnemyPos.push_back(Vec2(9999, 9999));
	GameInfo->OceanicPos.push_back(Vec2(9999, 9999));
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
	GameInfo->Level_Petturn++;
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
				GameInfo->AerialPos.at(EnemyOcTag) = Vec2(9999, 9999);
				GameInfo->EnemyCount[0]--;
				GameInfo->EnemyCount[2]--;
				GameInfo->isBossSpawn = false;
				GameInfo->isOneBoss = true;
			}
			RotationTurret();
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
}

void Stage2Boss::RotationTurret()
{
}

void Stage2Boss::Attack()
{
	AttackTime += dt;
	if (AttackTime > DelayTime) {
		for (int i = 0; i < 7; i++) {
			//ObjMgr->AddObject(new EnemyRotationBullet(Turret[i]->m_Position, Turret[i]->m_Rotation + D3DXToRadian(90)), "EnemyBullet");
			if (PatternCount == 0)
				AttackTime = 0.5f;
			else
				AttackTime = 0.75f;
		}
		AttackCount++;
	}
}
