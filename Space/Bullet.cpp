#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Vec2 spawnpoint, bool minibullet)
{
	m_Bolt = new Animation();
	m_Bolt->Init(0.1f, true);
	m_Bolt->AddContinueFrame(L"Painting/Bullet/Bolt/enemybolt",1,4);
	m_Bolt->SetParent(this);

	m_Bullet = Sprite::Create(L"Painting/Bullet/Spread.png");
	m_Bullet->SetParent(this);
	m_Bullet->m_Visible = false;
	Spawnpoint = Vec2(spawnpoint.x + (GetPlayer->m_Size.x * 0.4f) / 2, spawnpoint.y-2);

	SetPosition(Spawnpoint);
	m_Speed = 600.f;
	DelayTime = 1.f;
	DestroyTime = 0.f;
	m_Layer = 2;
	m_Atk = 10.f * GameInfo->Player_Coefficient;
	SetScale(1.f, 1.f);
	if (GameInfo->EnemyCount[0] > 0) {
		Vec2 Enemy = GameInfo->CloseEnemy[0] - m_Position;
		D3DXVec2Normalize(&Dire, &Enemy);
	}
	else {
		Vec2 B = Vec2(GetPlayer->m_Position.x + 500, GetPlayer->m_Position.y);
		Vec2 Enemy = B - m_Position;
		D3DXVec2Normalize(&Dire, &Enemy);
	}
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime, float Time)
{
	if (GameInfo->isScoreScene) {
		m_Bolt->A = 105;
	}
	if (!GameInfo->isPause) {
		DestroyTime += dt;
		if (DelayTime < 5)
			DelayTime += dt * 1.1f;
		Move();

		if (DestroyTime > 6)
			ObjMgr->RemoveObject(this);

		m_Bolt->Update(deltaTime, Time);
	}
}

void Bullet::Render()
{
	m_Bolt->Render();
	m_Bullet->Render();
}

void Bullet::OnCollision(Object* obj)
{

}

void Bullet::Move()
{

	m_Rotation = std::atan2f(Dire.y, Dire.x);
	Translate(Dire.x * m_Speed*DelayTime * dt, Dire.y * m_Speed* DelayTime * dt);
}
