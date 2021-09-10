#include "stdafx.h"
#include "Pet.h"
#include "Bullet.h"

Pet::Pet(int type, bool display)
{
	m_Pet = Sprite::Create(L"Painting/Player/Player0.png");
	m_Pet->SetParent(this);
	
	SetPosition(GetPlayer->m_Position.x, GetPlayer->m_Position.x + 200);
	SetScale(0.4f, 0.4f);

	m_Speed = 300.f;
	Limit = 1.f;	

	GameInfo->PetCount++;
	Count = GameInfo->PetCount;
	std::cout << "Æê »ý¼º" << std::endl;
	m_Rotation = D3DXToRadian(90);
	// Æê ³×¸¶¸®±îÁö
	Gun = type;
}

Pet::~Pet()
{
}

void Pet::Update(float deltaTime, float Time)
{
	if (GameInfo->isScoreScene) {
		m_Pet->A = 105;
	}
	if (!GameInfo->isPause) {
		Move(); 
		if (!(!GameInfo->isBossSpawn && !GameInfo->isOneBoss)) {
			Attack();
		}
	}
}

void Pet::Render()
{
	m_Pet->Render();
}

void Pet::OnCollision(Object* obj)
{
}

void Pet::Move()
{
	Vec2 A, B;
	float X;
	float Y;
	if (Count == 1) {
		X = -50;
		Y = 60;
	}
	else if (Count == 2) {
		X = -50;
		Y = -60;
	}
	else if (Count == 3) {
		X = -100;
		Y = 120;
	}
	else if (Count == 4) {
		X = -100;
		Y = -120;
	}
	else {
		X = -100;
		Y = 0;
	}

	A = m_Position;


	B = Vec2(GetPlayer->m_Position.x + X, GetPlayer->m_Position.y + Y);

	Dire = B - A;
	Limit = (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2))/m_Speed);

	D3DXVec2Normalize(&Dire, &Dire);
	Translate(Dire.x * m_Speed * Limit * dt * 3, Dire.y * m_Speed * Limit * dt * 3);
}

void Pet::Attack()
{
	// ¾ÕÀ¸·Î ³ª°¡´Â ÃÑÅº, À¯µµÅº, 
	ShotTime += dt;
	if (Gun == 0) {
		if (ShotTime > 0.35f) {
			ObjMgr->AddObject(new Bullet(m_Position,true), "Bullet");
			ShotTime = 0.f;
		}
	}
	else if (Gun == 1) {
		if (ShotTime > 0.35f) {
			Gun++;
			ShotTime = 0.f;
		}
	}
	else if (Gun == 2) {
		if (ShotTime > 0.4f) {
			ShotTime = 0.f;
			Gun++;
		}
	}
	else if (Gun == 3) {
		if (ShotTime > 0.4f) {

			ShotTime = 0.f;
		}
	}
	else if (Gun == 4) {
		if (ShotTime > 0.5f) {
			ShotTime = 0.f;
		}
	}
	else if (Gun == 5) {
		if (ShotTime > 0.3f) {
			ShotTime = 0.f;
		}
	}
}
