#include "stdafx.h"
#include "Torpedo.h"

Torpedo::Torpedo(Vec2 Pos)
{
	m_Torpedo = new Animation();
	m_Torpedo->Init(0.1f, true);
	m_Torpedo->SetParent(this);
	m_Torpedo->AddContinueFrame(L"Painting/Missile/missile", 0, 1);

	m_ColBox = Sprite::Create(L"Painting/Missile/ColBox.png");
	m_ColBox->SetParent(this);
	SetPosition(Pos);
	m_ColBox->m_Visible = false;

	m_Rotation = D3DXToRadian(0);;
	turnRadian = m_Rotation;
	vrad = 0.005f;
	Delay = 0.f;
	isHoming = false;
	HomingTime = 1.f;
	impellent = 1.f;
	m_Speed = 400.f;
	SetScale(2.f, 2.f);
	DestroyTime = 0.f;
	m_Atk = 100.f;
}

Torpedo::~Torpedo()
{
}

void Torpedo::Update(float deltaTime, float Time)
{
	if (!GameInfo->isPause) {
		DestroyTime += dt;
		m_Torpedo->A = 170;
		m_Torpedo->Update(deltaTime, Time);
		Move();
	}
	if (DestroyTime > 22.f || GameInfo->isScoreScene || m_Position.y < 451) {
		ObjMgr->RemoveObject(this);
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Big/", 1, 9, 0.1f, m_Position), "Effect");
	}
}

void Torpedo::Render()
{
	m_ColBox->Render();
	m_Torpedo->Render();
}

void Torpedo::OnCollision(Object* obj)
{
}

void Torpedo::Move()
{
	if (!isHoming) {
		HomingTime += dt;
		m_Position.y += 100 * HomingTime * dt;
		if (HomingTime > 1.7f) {
			isHoming = true;
		}
	}
	else {
		Enemy = GameInfo->CloseEnemy[1] - m_Position;

		D3DXVec2Normalize(&Dire, &Enemy);
	
		if (!GameInfo->EnemyCount[1]==0) {
			if (impellent < 2) {
				impellent += dt;
			}
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
			Translate(Dire.x * m_Speed * impellent * dt, Dire.y * m_Speed * impellent * dt);
		}
		else {
			if (impellent < 2) {
				impellent += dt;
			}
			Dire.y = sin(m_Rotation);
			Dire.x = cos(m_Rotation);
			D3DXVec2Normalize(&Dire, &Dire);
			Translate(Dire.x * m_Speed * impellent * dt, Dire.y * m_Speed * impellent * dt);
		}
	}
}
