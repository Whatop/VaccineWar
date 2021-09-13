#include "stdafx.h"
#include "AirForce.h"
#include "Missile.h"

AirForce::AirForce()
{
	m_AirForce = Sprite::Create(L"Painting/Skill/Player1.png");
	m_AirForce->SetParent(this);
	SetPosition(-m_Size.x , 300);
	SetScale(1.5f, 1.5f);

	AttackDelay = 0.15f;
}

AirForce::~AirForce()
{
}

void AirForce::Update(float deltaTime, float Time)
{
	DestroyTime += 5*dt;
	AttackTime += dt;
	Move();
	if (DestroyTime> 30.f) {
		ObjMgr->RemoveObject(this);
		GameInfo->SKILL_CoolTime[0] = 40.f;
		std::cout << "Áö¿öÁü!" << std::endl;
	}
	Attack();
}

void AirForce::Render()
{
	m_AirForce->Render();
}

void AirForce::OnCollision(Object* obj)
{
}

void AirForce::Move()
{
	m_Position.x += 100*dt* (DestroyTime+4);
}

void AirForce::Attack()
{
	if (AttackTime > AttackDelay && DestroyTime < 7.f) {
		ObjMgr->AddObject(new Missile(m_Position,true), "Bullet");
		
		AttackTime = 0.f;
	}
}
