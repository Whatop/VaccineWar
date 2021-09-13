#include "stdafx.h"
#include "NavalProjectile.h"

NavalProjectile::NavalProjectile(Vec2 spawnpoint, bool minibullet)
{
	m_Bolt = new Animation();
	m_Bolt->Init(0.1f, true);
	m_Bolt->AddContinueFrame(L"Painting/Bullet/Bolt/enemybolt", 1, 4);
	m_Bolt->SetParent(this);

	m_Bullet = Sprite::Create(L"Painting/Bullet/Spread.png");
	m_Bullet->SetParent(this);
	m_Bullet->m_Visible = false;
	Spawnpoint = Vec2(spawnpoint.x + (GetPlayer->m_Size.x * 0.4f) / 2, spawnpoint.y - 2);

	SetPosition(Spawnpoint);
	m_Speed = 550.f;
	DelayTime = 1.f;
	DestroyTime = 0.f;
	m_Layer = 2;
	m_Atk = 20.f * GameInfo->Player_Coefficient;
	
	SetScale(0.75f, 0.75f);
	if (GameInfo->EnemyCount > 0) {
		Vec2 Enemy =
			Vec2(GameInfo->CloseEnemy[0].x + rand() % 100
				, GameInfo->CloseEnemy[0].y + rand() % 100) - m_Position;
		D3DXVec2Normalize(&Dire, &Enemy);
	}
	else {
		Vec2 Enemy =
			Vec2(GetPlayer->m_Position.x + 500 + rand() % 50
				, GetPlayer->m_Position.y + rand() % 50) - m_Position;
		D3DXVec2Normalize(&Dire, &Enemy);
	}
}

NavalProjectile::~NavalProjectile()
{
}

void NavalProjectile::Update(float deltaTime, float Time)
{
	if (GameInfo->isScoreScene) {
		m_Bolt->A = 105;
	}
	if (!GameInfo->isPause) {
		DestroyTime += dt;
		DelayTime += dt * 2.1f;


		Move();

		if (DestroyTime > 6)
			ObjMgr->RemoveObject(this);

		m_Bolt->Update(deltaTime, Time);
	}
}

void NavalProjectile::Render()
{
	m_Bolt->Render();
	m_Bullet->Render();
}

void NavalProjectile::OnCollision(Object* obj)
{

}

void NavalProjectile::Move()
{
	m_Rotation = std::atan2f(Dire.y, Dire.x);
	Translate(Dire.x * m_Speed  * dt, Dire.y * m_Speed  * dt);
}
