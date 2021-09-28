	#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(Vec2 SpawnPoint, bool isboom)
{
	isMine = isboom;
	if (!isMine) {
		m_Obstacle = new Animation();
		m_Obstacle->Init(1.4f, true);
		m_Obstacle->SetParent(this);
		m_Obstacle->AddContinueFrame(L"Painting/Obstacle/", 1, 4);

		SetScale(2, 2);

		m_ColBox = Sprite::Create(L"Painting/Obstacle/1.png");
		m_ColBox->m_Visible = false;
		m_ColBox->SetScale(2, 2);
	}
	else {
		m_Mine = new Animation();
		m_Mine->Init(0.1f, true);
		m_Mine->SetParent(this);
		m_Mine->AddContinueFrame(L"Painting/Obstacle/Mine/", 0, 3);
		
		m_ColBox = Sprite::Create(L"Painting/Obstacle/Mine/ColBox.png");
		m_ColBox->SetParent(this);
		m_ColBox->A = 100.f;

	
		// 아래
		ColBox[1] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[1]->SetScale(2.1f, 1);

		ColBox[2] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[2]->SetScale(1.8f, 1);

		ColBox[3] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[3]->SetScale(1.4f, 1);

		ColBox[4] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[4]->SetScale(0.8f, 0.5f);

		//가운대
		ColBox[0] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[0]->SetScale(2.2f, 1);

		// 위
		ColBox[5] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[5]->SetScale(2.1f, 1);

		ColBox[6] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[6]->SetScale(1.8f, 1);

		ColBox[7] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[7]->SetScale(1.4f, 1);

		ColBox[8] = Sprite::Create(L"Painting/Obstacle/Mine/1ColBox.png");
		ColBox[8]->SetScale(0.8f, 0.5f);
		for (int i = 0; i < 9; i++) {
			ColBox[i]->m_Visible = false;
		}
	}
	SetPosition(SpawnPoint);

	isBoom = false;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(float deltaTime, float Time)
{
	if (!GameInfo->isPause) {
		
		ObjMgr->CollisionCheak(this, "Player");

		Move();
		if (!isMine) {
			m_Obstacle->A = 255;
			m_Obstacle->Update(deltaTime, Time);

			m_ColBox->m_Position = m_Position;
		}
		else {
			m_ColBox->A = 255;
			m_Mine->SetAnimeColor(200);
			m_Mine->Update(deltaTime, Time);
			ColBoxPos();
		}
		if (isBoom) {
			ObjMgr->RemoveObject(this);
			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Mine/", 1, 25, 0.075f, m_Position, 1, 1), "Effect");
			isBoom = false;

			if (isMine) {
				GameInfo->MineDamage = true; // 마인슬로우는 Player에서
				GameInfo->PlayerHit = true;
			}
			else {
				GameInfo->isTrash = true;
			}
		}
	}
	else {
		if (!isMine) {
			m_Obstacle->A = 255;
		}
		else {
			m_ColBox->A = 105;
			m_Mine->SetAnimeColor(105);
		}
	}
}

void Obstacle::Render()
{
	if (!isMine) {
		m_Obstacle->Render();
	}
	else {
		for(int i =0; i < 9; i++)
		ColBox[i]->Render();

		m_Mine->Render();
	}
	m_ColBox->Render();
}

void Obstacle::Move()
{
	m_Position.x -= 100 * dt;
}

void Obstacle::ColBoxPos()
{
	//가운데
	ColBox[0]->SetPosition(m_Position.x, m_Position.y );

	//아래
	ColBox[1]->SetPosition(m_Position.x, m_Position.y + ColBox[1]->m_Size.y/2);
	ColBox[2]->SetPosition(m_Position.x, m_Position.y + ColBox[1]->m_Size.y);
	ColBox[3]->SetPosition(m_Position.x, m_Position.y + ColBox[1]->m_Size.y*1.5f);
	ColBox[4]->SetPosition(m_Position.x, m_Position.y + ColBox[1]->m_Size.y*2.f);
	
	//위
	ColBox[5]->SetPosition(m_Position.x, m_Position.y - ColBox[1]->m_Size.y / 2);
	ColBox[6]->SetPosition(m_Position.x, m_Position.y - ColBox[1]->m_Size.y);
	ColBox[7]->SetPosition(m_Position.x, m_Position.y - ColBox[1]->m_Size.y * 1.5f);
	ColBox[8]->SetPosition(m_Position.x, m_Position.y - ColBox[1]->m_Size.y * 2.f);
}

void Obstacle::OnCollision(Object* obj)
{
	if (obj->m_Tag == "Player") {
		if (isMine) {
			RECT rc;
			for (int i = 0; i < 9; i++) {
				if (IntersectRect(&rc, &ColBox[i]->m_Collision, &GameInfo->PSprite->m_Collision)) {
					isBoom = true;
				}
			}
		}
		else {
			RECT rc;
			if (IntersectRect(&rc, &m_ColBox->m_Collision, &GameInfo->PSprite->m_Collision)) {
					isBoom = true;
			}
		}
	}
}
