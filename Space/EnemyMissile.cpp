#include "stdafx.h"
#include "EnemyMissile.h"

EnemyMissile::EnemyMissile(Vec2 Pos,float r)
{
	m_Missile = new Animation();
	m_Missile->Init(0.1f, true);
	m_Missile->SetParent(this);
	m_Missile->AddContinueFrame(L"Painting/Missile/missile", 0, 1);

	m_ColBox = Sprite::Create(L"Painting/Missile/ColBox.png");
	m_ColBox->SetParent(this);
	SetPosition(Pos);
	m_ColBox->m_Visible = false;

	vrad = 0.01f;
	Delay = 0.f;
	isHoming = false;
	HomingTime = 1.f;
	impellent = 1.f;
	m_Speed = 400.f;
	SetScale(1.f, 1.f);
	DestroyTime = 0.f;
	m_Atk = 20.f;
	
	one = false;

	m_Rotation = D3DXToRadian(180) + D3DXToRadian(rand() % 60 - 60);
	if(r!=370)
	m_Rotation = D3DXToRadian(r);
	turnRadian = m_Rotation;
	Enemy = GetPlayer->m_Position - m_Position;

	D3DXVec2Normalize(&Dire, &Enemy);
	Delay += dt;
	if (Delay > 0.1f) {
		vrad += dt * 0.01;
		Delay = 0;
	}
	float pi2 = D3DX_PI * 2;
	float diff = std::atan2f(Dire.y, Dire.x) - turnRadian;
	while (diff < -D3DX_PI) diff += pi2;
	while (diff >= D3DX_PI) diff -= pi2;

	if (abs(diff) < vrad)
		turnRadian += diff;
	else {
		turnRadian += (diff < 0 ? -vrad : vrad);
	}

	Dire.y = sin(turnRadian);
	Dire.x = cos(turnRadian);
	m_Rotation = std::atan2f(Dire.y, Dire.x);
}

EnemyMissile::~EnemyMissile()
{
}

void EnemyMissile::Update(float deltaTime, float Time)
{
	if (!GameInfo->isPause) {
		DestroyTime += dt;
		m_Missile->Update(deltaTime, Time);
		Move();
	}
	if (DestroyTime > 7.f || GameInfo->isScoreScene || m_Position.x > 2000.f) {
		ObjMgr->RemoveObject(this);
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Big/", 1, 9, 0.1f, m_Position), "Effect");
	}
}
void EnemyMissile::Render()
{
	m_ColBox->Render();
	m_Missile->Render();
}

void EnemyMissile::OnCollision(Object* other)
{
}

void EnemyMissile::Move()
{
	if (!isHoming) {
		HomingTime += dt;
		m_Position.y += 100 * HomingTime * dt;

		if (HomingTime > 1.7f) {
			isHoming = true;
			HomingTime = 0.f;
		}
	}
	else {
		if (impellent < 2) {
			impellent += dt;
		}

		int Limit = (sqrt(pow(GetPlayer->m_Position.x - m_Position.x, 2) + pow(GetPlayer->m_Position.y - m_Position.y, 2)) / m_Speed);
		if (Limit > 0.1f && !one) {
			Enemy = GetPlayer->m_Position - m_Position;

			D3DXVec2Normalize(&Dire, &Enemy);
			Delay += dt;
			if (Delay > 0.1f) {
				vrad += dt * 0.01;
				Delay = 0;
			}
			float pi2 = D3DX_PI * 2;
			float diff = std::atan2f(Dire.y, Dire.x) - turnRadian;
			while (diff < -D3DX_PI) diff += pi2;
			while (diff >= D3DX_PI) diff -= pi2;

			if (abs(diff) < vrad)
				turnRadian += diff;
			else {
				turnRadian += (diff < 0 ? -vrad : vrad);
			}

			Dire.y = sin(turnRadian);
			Dire.x = cos(turnRadian);
			m_Rotation = std::atan2f(Dire.y, Dire.x);
		}
		else
			one = true;

		Translate(Dire.x * m_Speed * impellent * dt, Dire.y * m_Speed * impellent * dt);
	}
}