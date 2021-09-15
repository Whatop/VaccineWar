#include "stdafx.h"
#include "Stage1Boss.h"

Stage1Boss::Stage1Boss()
{
	m_Boss = Sprite::Create(L"Painting/Boss/Stage1/Boss");
	m_Boss->SetParent(this);

	Turret[0] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[1] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[2] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");
	Turret[3] = Sprite::Create(L"Painting/Boss/Stage1/Turret.png");

	// Attack
	float AttackTime;
	float DelayTime;

}

Stage1Boss::~Stage1Boss()
{
}

void Stage1Boss::Update(float deltaTime, float Time)
{
}

void Stage1Boss::Render()
{
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
