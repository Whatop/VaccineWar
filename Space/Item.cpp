#include "stdafx.h"
#include "Item.h"

Item::Item(Vec2 Pos, bool bonus)
{
	ItemCode = rand() % 5 + 0;
	if (bonus) { // ���� ���� ��� ŰƮ
		ItemCode = 999;
		DestroyTime = 10.f;
	}
	m_Item = Sprite::Create(L"Painting/Item/"+std::to_wstring(ItemCode)+L".png");
	
	m_ColBox = Sprite::Create(L"Painting/Item/Item.png");
	m_ColBox->SetParent(this);
	m_ColBox->m_Visible = false;
	SetPosition(Pos);
	m_Speed = 300.f;
	m_Rotation = D3DXToRadian(rand()%360+0);
	Under = false;
	Over = true;
	m_Layer = 2;
	DestroyTime = 0.f;
}

Item::~Item()
{
}

void Item::Update(float deltaTime, float Time)
{
	if (GameInfo->isScoreScene) {
		m_Item->m_Visible = false;
	}
	//MachineGun, NavalProjectile, Torpedo, Missile;
	if (ItemCode == 0) {
		m_Tag = "AddMachineGun";
	}
	else if (ItemCode == 1) {
		m_Tag = "AddMissile";
	}
	else if (ItemCode == 2) {
		m_Tag = "AddTorpedo";
	}
	else if (ItemCode == 3) {
		m_Tag = "Invincibility";
	}
	else if (ItemCode == 4) {
		m_Tag = "SpeedUp";
	}
	else if (ItemCode == 999) {
		m_Tag = "Bonus";
	}
	if (!GameInfo->isPause) {
		ObjMgr->CollisionCheak(this, "Player");
		DestroyTime += dt;
		Move();
		if (m_Position.y > 1071 - m_Size.y / 2)
			m_Rotation = m_Rotation * -1;
		if (m_Position.y < 549 + m_Size.y / 2)
			m_Rotation = m_Rotation * -1;
		if (m_Position.x > Camera::GetInst()->m_Position.x + App::GetInst()->m_Width - m_Size.x / 2)
			m_Rotation = m_Rotation * -1.5f;
		if (m_Position.x < Camera::GetInst()->m_Position.x + m_Size.x / 2)
			m_Rotation = m_Rotation * -0.5f;
		if (DestroyTime > 15.f) {
			ObjMgr->RemoveObject(this);
		}
		if (DestroyTime > 10.f) {
			if (m_Item->A <= 0) {
				Under = true;
				Over = false;
			}
			if (m_Item->A >= 255) {
				Under = false;
				Over = true;
			}

			if (Under) {
				m_Item->A += 20;
			}
			if (Over) {
				m_Item->A -= 20;
			}
		}
	}
}
void Item::Render()
{
	m_Item->Render();
	m_ColBox->Render();
}

void Item::OnCollision(Object obj)
{
}

void Item::Move()
{
		m_Dire.x = cos(m_Rotation);
		m_Dire.y = sin(m_Rotation);

	m_Rotation = std::atan2f(m_Dire.y, m_Dire.x);
	Translate(m_Dire.x * m_Speed * dt, m_Dire.y * m_Speed * dt);
	m_Item->SetPosition(m_Position);
}
