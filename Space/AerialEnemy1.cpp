#include "stdafx.h"
#include "AerialEnemy1.h"
#include "EnemyRotationBullet.h"
#include "Item.h"
#include "EnemyMissile.h"

AerialEnemy1::AerialEnemy1(Vec2 Pos, int enemyCount)
{
	m_AerialEnemy1 = Sprite::Create(L"Painting/Enemy/AerialEnemy1/Enemy0.png");
	m_AerialEnemy1->SetParent(this);
	m_AerialEnemy1->m_Visible = false;

	HelicopterWing = new Animation();
	HelicopterWing->Init(0.1f, true);
	HelicopterWing->SetParent(this);
	HelicopterWing->AddContinueFrame(L"Painting/Enemy/AerialEnemy1/", 0, 1,COLORKEY_GREEN);
	
	HelicopterBackWing = new Animation();
	HelicopterBackWing->Init(0.1f, true);
	HelicopterBackWing->SetParent(this);
	HelicopterBackWing->AddContinueFrame(L"Painting/Enemy/AerialEnemy1/Enemy", 0, 1,COLORKEY_GREEN);

	SetPosition(Pos);
	m_Hp = 150;
	m_Speed = 450.f;
	m_LastMoveTime = 2.f;
	SpawnMove = 0.f;
	m_Layer = 2;
	std::cout << "적 공군 1 생성" << std::endl;

	EnemyAirTag = GameInfo->EnemyTag[2];
	EnemyAllTag = GameInfo->EnemyTag[0];
	GameInfo->EnemyCount[0]++;
	GameInfo->EnemyCount[2]++;
	GameInfo->EnemyTag[0]++;
	GameInfo->EnemyTag[2]++;


	GameInfo->AllEnemyPos.push_back(Vec2(9999, 9999));
	GameInfo->AerialPos.push_back(Vec2(9999, 9999));
	ones = true;
	SetScale(1.5f, 1.5f);
	random = rand() % 300;
}

AerialEnemy1::~AerialEnemy1()
{
}

void AerialEnemy1::Update(float deltaTime, float Time)
{
	GameInfo->AllEnemyPos.at(EnemyAllTag) = m_Position;
	GameInfo->AerialPos.at(EnemyAirTag) = m_Position;
	if (!GameInfo->isPause) {
		SpawnMove += dt;

		if (SpawnMove < 2) {
			m_Position.x -= (100 + random) * dt;
			ObjMgr->CollisionCheak(this, "Bullet");
			HelicopterWing->Update(deltaTime, Time);
			HelicopterBackWing->Update(deltaTime, Time);
		}
		else {
			if (ones) {
				//519~1041
				m_RandomPosition = Vec2((rand() % 920 + 1000), (rand() % 432 + 123));
				ones = false;
				GameInfo->AllEnemyPos.at(EnemyAllTag) = m_Position;
				GameInfo->AerialPos.at(EnemyAirTag) = m_Position;
			}
			ObjMgr->CollisionCheak(this, "Bullet");
			m_LastMoveTime += dt;
			if (m_LastMoveTime >= 4)
				Move();

			m_AerialEnemy1->A = 255;
			HelicopterWing->SetAnimeColor();
			HelicopterBackWing->SetAnimeColor();
			HelicopterWing->Update(deltaTime, Time);
			HelicopterBackWing->Update(deltaTime, Time);
		}
	}
	else {
		m_AerialEnemy1->A = 105;
		HelicopterWing->SetAnimeColor(105);
		HelicopterBackWing->SetAnimeColor(105);
	}
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
	}
}

void AerialEnemy1::Render()
{
	m_AerialEnemy1->Render();
	HelicopterBackWing->Render();
	HelicopterWing->Render();
}

void AerialEnemy1::OnCollision(Object* obj)
{
	if (obj->m_Tag == "Bullet") {
		m_Hp -= obj->m_Atk;
		float randx = (rand() % (int)m_Size.x * m_Scale.x) + m_Position.x - m_Size.x / 2 * m_Scale.x;
		float randy = (rand() % (int)m_Size.y * m_Scale.y) + m_Position.y - m_Size.y / 2 * m_Scale.y;
		obj->SetDestroy(true);
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Explosion/", 1, 9, 0.1f, Vec2(randx, randy)), "Effect");
	}
}

void AerialEnemy1::Move()
{
	Vec2 A, B, Dire;
	const int EPSILON = 10;

	A = m_Position;
	B = m_RandomPosition;

	Dire = B - A;

	D3DXVec2Normalize(&Dire, &Dire);

	if (abs(m_Position.x - m_RandomPosition.x) > EPSILON && abs(m_Position.y - m_RandomPosition.y) > EPSILON)
	{
		if (m_Position.x > Camera::GetInst()->m_Position.x + App::GetInst()->m_Width / 2 &&
			m_Position.x < Camera::GetInst()->m_Position.x + App::GetInst()->m_Width - 100)

			m_Position.x += Dire.x * m_Speed * dt;

		m_Position.y += Dire.y * m_Speed * dt;
	}
	else
	{
		if (m_Position.y < 777.5f)
			m_RandomPosition = Vec2((rand() % 920 + 1000), (rand() % 432 + 123));

		else
			m_RandomPosition = Vec2((rand() % 920 + 1000), (rand() % 432 + 123));

		m_LastMoveTime = 2.f;

		Vec2 C, D, Dir;
		C = m_Position;
		D = GameInfo->GetPlayerInfo()->m_Position;

		Dir = D - C;

		D3DXVec2Normalize(&Dir, &Dir);

		ObjMgr->AddObject(new EnemyRotationBullet(Vec2(m_Position.x - 10, m_Position.y), std::atan2(Dir.y, Dir.x)), "EnemyBullet");
		ObjMgr->AddObject(new EnemyRotationBullet(Vec2(m_Position.x - 10, m_Position.y), std::atan2(Dir.y, Dir.x)+ D3DXToRadian(30)), "EnemyBullet");
		ObjMgr->AddObject(new EnemyRotationBullet(Vec2(m_Position.x - 10, m_Position.y), std::atan2(Dir.y, Dir.x) - D3DXToRadian(30)), "EnemyBullet");
		
		
		ObjMgr->AddObject(new EnemyMissile(Vec2(m_Position.x - 30, m_Position.y)), "EnemyBullet");
		ObjMgr->AddObject(new EnemyMissile(Vec2(m_Position.x - 30, m_Position.y+40)), "EnemyBullet");
		ObjMgr->AddObject(new EnemyMissile(Vec2(m_Position.x , m_Position.y)), "EnemyBullet");
		ObjMgr->AddObject(new EnemyMissile(Vec2(m_Position.x , m_Position.y+40)), "EnemyBullet");

	}
}
