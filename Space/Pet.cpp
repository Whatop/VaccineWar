#include "stdafx.h"
#include "Pet.h"
#include "Bullet.h"

Pet::Pet(int type, bool display)
{
	m_Pet = Sprite::Create(L"Painting/Skill/Player0.png");
	m_Pet->SetParent(this);
	
	SetPosition(GetPlayer->m_Position.x, GetPlayer->m_Position.x + 200);
	SetScale(0.2f, 0.2f);

	m_Speed = 300.f;
	Limit = 1.f;	

	GameInfo->PetCount++;
	Count = GameInfo->PetCount;
	m_Rotation = D3DXToRadian(90);
	// 펫 네마리까지
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
		Attack();
	}
	DelayDestroy(this,20);
	if (m_Destroy) {
		GameInfo->PetCount--;
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
	ShotTime += dt;
	if (ShotTime > 0.35f) {
		ObjMgr->AddObject(new Bullet(m_Position,true), "Bullet");
		ShotTime = 0.f;
	}
}
