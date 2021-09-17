#include "stdafx.h"
#include "EnemyDirBullet.h"

EnemyDirBullet::EnemyDirBullet(Vec2 Pos, Vec2 Dir)
{
	m_Bolt = new Animation();
	m_Bolt->Init(0.1f, true);
	m_Bolt->AddContinueFrame(L"Painting/Bullet/Long/", 0, 1);
	m_Bolt->SetParent(this);


	m_Bullet = Sprite::Create(L"Painting/Bullet/BigBullet.png");
	m_Bullet->SetParent(this);
	m_Bullet->m_Visible = false;
	SetPosition(Pos);
	m_Dire = Dir;
	m_Speed = 500.f;
	m_Rotation = (std::atan2(m_Dire.y, m_Dire.x));
	m_Atk = 15.f;
	if (GameInfo->m_Scene == StageScene::STAGE1)
	{
		m_Bolt->R = 51;
		m_Bolt->G = 51;
		m_Bolt->B = 51;
	}
	else {
		m_Bolt->R = 255;
		m_Bolt->G = 255;
		m_Bolt->B = 255;
	}
}

EnemyDirBullet::~EnemyDirBullet()
{
}

void EnemyDirBullet::Update(float deltaTime, float Time)
{
	ObjMgr->CollisionCheak(this, "Player");
	if (GameInfo->isScoreScene) {
		m_Bolt->A = 105;
		m_Bullet->A = 105;
	}
	if (!GameInfo->isPause) {
		Move();
		DelayDestroy(this, 4);
		m_Bolt->Update(deltaTime, Time);
	}
}

void EnemyDirBullet::Render()
{
	m_Bullet->Render();
	m_Bolt->Render();
}

void EnemyDirBullet::OnCollision(Object* obj)
{
}

void EnemyDirBullet::Move()
{
	D3DXVec2Normalize(&m_Dire, &m_Dire);
	Translate(m_Dire.x * m_Speed * dt, m_Dire.y * m_Speed * dt);
}

