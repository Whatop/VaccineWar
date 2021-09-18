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

	SetPosition(1920 / 2, -200);
	for (int i = 0; i < 5; i++) {
		Turret[i]->SetPosition(m_Position.x+50 + i * 100 - 100, m_Position.y+m_Size.y/2-50);
		Turret[i]->SetScale(1.1f, 1.1f);
	}
	m_MaxHp = 12000;
	m_Hp = m_MaxHp;
	m_Speed = 450.f; 
	m_Layer = 2;
	std::cout << "보스 공군 생성" << std::endl;

	EnemyAirTag = enemyCount;
	EnemyAllTag = GameInfo->EnemyTag[0];
	GameInfo->EnemyCount[0]++;
	GameInfo->EnemyTag[0]++;
	GameInfo->EnemyTag[2]++;


	GameInfo->AllEnemyPos.push_back(Vec2(9999, 9999));
	GameInfo->AerialPos.push_back(Vec2(9999, 9999));
	ones = true;
	SetScale(1.1f, 1.1f);
	isSpawnMove = true;

	GameInfo->isDangerBoss = true;
	GameInfo->isBossSpawn = true;
	Camera::GetInst()->ShakeTimeX = -4.5f;
	
	DelayTime = 1.f;
	AttackTime = 1.f;
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
		if (m_Hp <= 0)
		{
			ObjMgr->AddObject(new Item(m_Position), "Heal");
			if ((rand() % 30) == 0)
				ObjMgr->AddObject(new Item(m_Position), "Heal");
			ObjMgr->RemoveObject(this);
			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Big/", 1, 9, 0.1f, m_Position), "Effect");

			GameInfo->MaxScore += 100;
			GameInfo->KillScore += 100;
			GameInfo->AllEnemyPos.at(EnemyAllTag) = Vec2(9999, 9999);
			GameInfo->AerialPos.at(EnemyAirTag) = Vec2(9999, 9999);
			GameInfo->EnemyCount[0]--;
			GameInfo->EnemyCount[2]--;
			GameInfo->isBossSpawn = false;
		}
		RotationTurret();
	}
}

void Stage1Boss::Render()
{
	m_Boss->Render();
	for (int i = 0; i < 5; i++)
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
	for (int i = 0; i < 5; i++)
		Turret[i]->SetPosition(m_Position.x + 50 + i * 100-100, m_Position.y + m_Size.y / 2 - 50);
}

void Stage1Boss::RotationTurret()
{
	Turret[0]->m_Rotation = D3DXToRadian(0);
	Turret[1]->m_Rotation = D3DXToRadian(30);
	Turret[2]->m_Rotation = D3DXToRadian(60);
	Turret[3]->m_Rotation = D3DXToRadian(-30);
	Turret[4]->m_Rotation = D3DXToRadian(-60);
}

void Stage1Boss::Attack()
{
	AttackTime += dt;
	if (AttackTime > DelayTime) {
		for (int i = 0; i < 5; i++)
			ObjMgr->AddObject(new EnemyRotationBullet(Turret[i]->m_Position, Turret[i]->m_Rotation + D3DXToRadian(90)), "EnemyBullet");
		AttackTime = 0.f;
	}
}
