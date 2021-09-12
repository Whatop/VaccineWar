#include "stdafx.h"
#include "Oceanic1.h"
#include "EnemyDirBullet.h"
#include "Item.h"

Oceanic1::Oceanic1(Vec2 Pos,int enemyCount)
{
	m_Oceanic1 = Sprite::Create(L"Painting/Enemy/Oceanic1/Temp.png");
	m_Oceanic1->SetParent(this);
	
	//WaterEffect = new Animation();
	//WaterEffect->Init(0.2f, true);
	//WaterEffect->SetParent(this);
	//WaterEffect->AddContinueFrame(L"Painting/Enemy/Oceanic1/", 0, 4);

	SetPosition(Pos);
	m_Hp = 100;
	m_Speed = 450.f;
	m_LastMoveTime = 2.f;
	SpawnMove = 0.f;
	m_Layer = 2;
	std::cout << "적 해군 1 생성" << std::endl;

	EnemyOcTag = enemyCount;
	GameInfo->EnemyCount++;

	GameInfo->AllEnemyPos.push_back(Vec2(9999, 9999));
	GameInfo->OceanicPos.push_back(Vec2(9999, 9999));
	ones = true;
	SetScale(2,2);
	random = rand() % 300;
}

Oceanic1::~Oceanic1()
{
}

void Oceanic1::Update(float deltaTime, float Time)
{
	GameInfo->AllEnemyPos.at(EnemyOcTag) = m_Position;
	GameInfo->OceanicPos.at(EnemyOcTag) = m_Position;
	if (!GameInfo->isPause) {
		SpawnMove += dt;

		if (SpawnMove < 2) {
			m_Position.x -= (100 + random) * dt;
			ObjMgr->CollisionCheak(this, "Bullet");
		}
		else {
			if (ones) {
				//519~1041
				m_RandomPosition = Vec2((rand() % 920 + 1000), (rand() % 519 + 520));
				ones = false;
			}
			ObjMgr->CollisionCheak(this, "Bullet");
			m_LastMoveTime += dt;
			if (m_LastMoveTime >= 4)
				Move();

			m_Oceanic1->A = 255;
			//WaterEffect->SetAnimeColor();
			//WaterEffect->Update(deltaTime, Time);
			
			
		}
	}
	else {
		m_Oceanic1->A = 105;
		//WaterEffect->SetAnimeColor(105);
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
		GameInfo->AllEnemyPos.at(EnemyOcTag) = Vec2(9999, 9999);
		GameInfo->EnemyCount--;
	}
}

void Oceanic1::Render()
{
	m_Oceanic1->Render();
	//WaterEffect->Render();
}

void Oceanic1::OnCollision(Object* obj)
{
	if (obj->m_Tag == "Bullet") {
		m_Hp -= obj->m_Atk;
		float randx = (rand() % (int)m_Size.x * m_Scale.x) + m_Position.x - m_Size.x / 2 * m_Scale.x;
		float randy = (rand() % (int)m_Size.y * m_Scale.y) + m_Position.y - m_Size.y / 2 * m_Scale.y;
		obj->SetDestroy(true);
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Explosion/", 1, 9, 0.1f, Vec2(randx, randy)), "Effect");
	}
}

void Oceanic1::Move()
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
			m_RandomPosition = Vec2((rand() % 920 + 1000), (rand() % 522 + 519));

		else
			m_RandomPosition = Vec2((rand() % 920 + 1000), (rand() % 522 + 519));

		m_LastMoveTime = 2.f;
	
		Vec2 C, D, Dir;
		C = m_Position;
		D = GameInfo->GetPlayerInfo()->m_Position;

		Dir = D - C;

		D3DXVec2Normalize(&Dir, &Dir);

		ObjMgr->AddObject(new EnemyDirBullet(Vec2(m_Position.x - 10, m_Position.y), Dir), "EnemyBullet");
	}
}
