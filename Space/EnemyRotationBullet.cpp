#include "stdafx.h"
#include "EnemyRotationBullet.h"

EnemyRotationBullet::EnemyRotationBullet(Vec2 Pos, float r,  float afteR)
{

	m_Bolt = new Animation();
	m_Bolt->Init(0.1f, true);
	m_Bolt->AddContinueFrame(L"Painting/Bullet/Spread/Spread", 1, 5);
	m_Bolt->SetParent(this);

	m_Bullet = Sprite::Create(L"Painting/Bullet/Spread/Spread5.png");
	m_Bullet->SetParent(this);
	SetPosition(Pos);

	m_Rotation=r;
	m_AfterR = afteR;
	m_Layer = 2;
	m_Speed = 500.f;
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

EnemyRotationBullet::~EnemyRotationBullet()
{
}

void EnemyRotationBullet::Update(float deltaTime, float Time)
{
	if (GameInfo->isScoreScene) {
		m_Bolt->A = 105;
		m_Bullet->A = 105;
	}
	if (!GameInfo->isPause) {
		Move();
			if (GameInfo->m_Scene == StageScene::STAGE1) 
				DelayDestroy(this, 4);
			else {
				if (GameInfo->isBossSpawn) 
					DelayDestroy(this, 4);

				else
					DelayDestroy(this, 4);

			}
		m_Bolt->Update(deltaTime, Time);
	}

}

void EnemyRotationBullet::Render()
{
	m_Bullet->Render();
	m_Bolt->Render();
}

void EnemyRotationBullet::OnCollision(Object* obj)
{
}

void EnemyRotationBullet::Move()
{
	if (GameInfo->m_Scene == StageScene::STAGE2) {
		if (!GameInfo->isBossSpawn) {
			if (m_Position.y > 1080 - m_Size.y / 2)
				m_Rotation = m_Rotation * -1;
			else if (m_Position.y < 73 + m_Size.y / 2)
				m_Rotation = m_Rotation * -1;
			else if (m_Position.x > Camera::GetInst()->m_Position.x + App::GetInst()->m_Width - m_Size.x / 2)
				m_Rotation = m_Rotation * -1.5f;
			else if (m_Position.x < Camera::GetInst()->m_Position.x + m_Size.x / 2)
				m_Rotation = m_Rotation * -0.5f;
		}
		else{
			if (m_Position.y < 73 + m_Size.y / 2)
				m_Rotation = m_AfterR;
		}

	}
	m_Dire.y = sin(m_Rotation);
	m_Dire.x = cos(m_Rotation);
	D3DXVec2Normalize(&m_Dire, &m_Dire);
	Translate(m_Dire.x * m_Speed * dt, m_Dire.y * m_Speed * dt);
}
