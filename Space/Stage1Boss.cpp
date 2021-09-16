#include "stdafx.h"
#include "Stage1Boss.h"
#include "Item.h"

Stage1Boss::Stage1Boss(int enemyCount)
{
	m_Boss = Sprite::Create(L"Painting/Boss/Stage1/Boss.png", D3DCOLOR_XRGB(255, 255, 255));
	m_Boss->SetParent(this);

	Turret[0] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[1] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[2] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[3] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");

	//for (int i = 0; i < 4; i++)
	//	Turret[i]->SetPosition()
	//
	//// Attack
	//float AttackTime;
	//float DelayTime;

	SetPosition(1920 / 2, -300);
	m_Hp = 150;
	m_Speed = 450.f;
	m_Layer = 2;
	std::cout << "적 공군 1 생성" << std::endl;

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
}
Stage1Boss::~Stage1Boss()
{
}

void Stage1Boss::Update(float deltaTime, float Time)
{
	if (isSpawnMove) {
		m_Position.y += 100 * dt;
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
		//GameInfo->EnemyCount[2]--;
	}
}

void Stage1Boss::Render()
{
	m_Boss->Render();
	for (int i = 0; i < 4; i++)
		Turret[i]->Render();

}

void Stage1Boss::OnCollision(Object* obj)
{
}

void Stage1Boss::Move()
{
}

void Stage1Boss::RotationTurret()
{
}

void Stage1Boss::Attack()
{
}
