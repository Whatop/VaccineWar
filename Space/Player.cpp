#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Missile.h"

Player::Player(float hp)
{
	PlayerPlatform = new Animation();
	PlayerPlatform->Init(0.2f, true);
	PlayerPlatform->SetParent(this);
	PlayerPlatform->AddContinueFrame(L"Painting/Player/", 0, 3);

	m_Player = Sprite::Create(L"Painting/Player/Player0.png");
	m_Player->SetParent(this);

	m_ColBox = Sprite::Create(L"Painting/Player/CatchBox.png");

	LEFT = 0;
	RIGHT = 1;
	UP = 2;
	DOWN = 3;
	HIT = 4;

	ColBox[LEFT] = Sprite::Create(L"Painting/Player/Height.png");
	ColBox[LEFT]->SetScale(1, 0.5f);
	ColBox[RIGHT] = Sprite::Create(L"Painting/Player/Height.png");
	ColBox[RIGHT]->SetScale(1, 0.5f);
	ColBox[UP] = Sprite::Create(L"Painting/Player/Width.png");
	ColBox[UP]->SetScale(0.3f, 1);
	ColBox[DOWN] = Sprite::Create(L"Painting/Player/Width.png");
	ColBox[DOWN]->SetScale(0.3f, 1);
	ColBox[HIT] = Sprite::Create(L"Painting/Player/HitBox.png");
	ColBox[HIT]->SetScale(0.75f, 0.75f);
	m_ColBox->SetScale(0.5f, 0.7f);
	for (int i = 0; i < 5; i++) {
		ColBox[i]->m_Visible = false;
		m_ColBox->m_Visible = false;
	}

	SetPosition(200, 700);
	SetScale(0.55f, 0.55f);

	m_Speed = 500.f;
	m_MaxHp = hp;
	m_Hp = m_MaxHp;
	GameInfo->PlayerUpdate(this);
	GameInfo->PlayerHpUpdate(m_MaxHp, m_Hp);

	//MachineGun, NavalProjectile, Torpedo, Missile;
	GameInfo->PlayerType = 0;
	defenseTime = 0.f;
	HitDelay = true;	
	Damage_Received = 10.f;
	
	//공속
	m_Rpm = 0.f;
	
	//슬로우
	SlowTime = 0.f;
	GameInfo->PlayerSlow = false;
	m_DelayTime = 0.f;

	//재장전
	isReload = false;
	ReloadTime = 0.f;
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update(float deltaTime, float Time)
{
	GameInfo->SpriteUpdate(ColBox[HIT]); // 지뢰 충돌 판정
	if (GameInfo->m_DebugMode) {
		for (int i = 0; i < 5; i++) {
			ColBox[i]->m_Visible = true;
			m_ColBox->m_Visible = true;
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			ColBox[i]->m_Visible = false;
			m_ColBox->m_Visible = false;
		}
	}
	if (!GameInfo->isPause) {
		isLeft = false;
		isRight = false;
		isUp = false;
		isDown = false;
		isHit = false;

		ObjMgr->CollisionCheak(this, "Wall");
		ObjMgr->CollisionCheak(this, "EnemyBullet");
		GameInfo->PlayerUpdate(this);

		Attack();
		Move();
		m_Player->A = 255;
		PlayerPlatform->SetAnimeColor();
		PlayerPlatform->Update(deltaTime, Time);

		CollisionBox();

		if (GameInfo->isTrash) {
			Camera::GetInst()->ShakeTimeX = 0.3f;
			GameInfo->isTrash = false;
			GameInfo->PlayerSlow = true;
		}
		if (GameInfo->PlayerHit) {
			if (!GameInfo->CK_GodMode) {
				if (HitDelay) {
						if (GameInfo->MineDamage) {
							m_Hp -= 35.f;
							GameInfo->MineDamage = false;
							GameInfo->PlayerSlow = true;
						}
						else if (!GameInfo->MineDamage)
							m_Hp -= Damage_Received;
				
					float randx = (rand() % (int)m_Size.x * m_Scale.x) + m_Position.x - m_Size.x / 2 * m_Scale.x;
					float randy = (rand() % (int)m_Size.y * m_Scale.y) + m_Position.y - m_Size.y / 2 * m_Scale.y;

					ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Explosion/", 1, 9, 0.1f, Vec2(randx, randy)), "Effect");
					Camera::GetInst()->ShakeTimeX = 0.3f;

					HitDelay = false;
				}
			}
		}
		if (HitDelay) {
			//Defense->m_Visible = false;
			m_Player->R = 255;
			m_Player->G = 255;
			m_Player->B = 255;
			PlayerPlatform->SetAnimeColor();
		}
		if (!HitDelay) {
			//Defense->m_Visible = true;
			defenseTime += dt;
			if (defenseTime > 2.f) {
				HitDelay = true;
				GameInfo->PlayerHit = false;
				defenseTime = 0.f;
			}
			m_Player->R = 255;
			m_Player->G = 30;
			m_Player->B = 30;
			PlayerPlatform->SetAnimeColor(255,255,30,30);
		}
		if (GameInfo->PlayerSlow) {
			SlowTime += dt;
			if (SlowTime > 2) {
				SlowTime = 0.f;
				GameInfo->PlayerSlow = false;
			}
			m_Speed = 250.f;
		}
		else {
			m_Speed = 500.f;
		}
		if (m_Hp < 0) {
			m_Hp = 0.f; // 게이지 UI때문에 해놈
		}
		if (m_Hp <= 0) {
			//폭파후 Fail..
		}
		GameInfo->PlayerHpUpdate(m_MaxHp, m_Hp);
	}
	else {
		m_Player->A = 105;
		PlayerPlatform->SetAnimeColor(105);
	}
}

void Player::Render()
{
	PlayerPlatform->Render();
	m_Player->Render();
	m_ColBox->Render();

	ColBox[LEFT]->Render();
	ColBox[RIGHT]->Render();
	ColBox[UP]->Render();
	ColBox[DOWN]->Render();
	ColBox[HIT]->Render();
}

void Player::OnCollision(Object* obj)
{
	if (obj->m_Tag == "Wall")
	{
		RECT rc;
		if (IntersectRect(&rc, &ColBox[0]->m_Collision, &obj->m_Collision))
			isLeft = true;
		if (IntersectRect(&rc, &ColBox[1]->m_Collision, &obj->m_Collision))
			isRight = true;
		if (IntersectRect(&rc, &ColBox[2]->m_Collision, &obj->m_Collision))
			isUp = true;
		if (IntersectRect(&rc, &ColBox[3]->m_Collision, &obj->m_Collision))
			isDown = true;
	}
	if (obj->m_Tag == "EnemyBullet")
	{
		RECT rc;
		if (IntersectRect(&rc, &ColBox[HIT]->m_Collision, &obj->m_Collision)) {
			Damage_Received = obj->m_Atk;
			GameInfo->PlayerHit = true;
		}
	}

}

void Player::Move()
{
	if (!isUp && INPUT->GetKey(VK_UP) == KeyState::PRESS) {
		m_Position.y -= m_Speed * dt;
	}
	if (!isDown && INPUT->GetKey(VK_DOWN) == KeyState::PRESS) {
		m_Position.y += m_Speed * dt;
	}
	if (!isLeft && INPUT->GetKey(VK_LEFT) == KeyState::PRESS) {
		m_Position.x -= m_Speed * dt;
	}
	if (!isRight && INPUT->GetKey(VK_RIGHT) == KeyState::PRESS) {
		m_Position.x += m_Speed * dt;
	}
}

void Player::Attack()
{
	//MachineGun, NavalProjectile, Torpedo, Missile;
	m_DelayTime += dt;
	if (GameInfo->PlayerType == 0) {
		m_Rpm = 0.25f;
	}
	else if (GameInfo->PlayerType == 1) {
		m_Rpm = 0.9f;
	}
	else if (GameInfo->PlayerType == 2) {
		m_Rpm = 0.7f;
	}
	else {
		m_Rpm = 0.7f;
	}
	
	if (INPUT->GetKey('Z') == KeyState::PRESS) {
		if (m_DelayTime > m_Rpm && !isReload) {
			if (GameInfo->Ammo[GameInfo->PlayerType] > 0) {
				if (GameInfo->PlayerType == 0) {
					ObjMgr->AddObject(new Bullet(), "Bullet");
				}
				else if (GameInfo->PlayerType == 1) {
					ObjMgr->AddObject(new Missile(m_Position), "Bullet");
				}
				else if (GameInfo->PlayerType == 2) {
					ObjMgr->AddObject(new Bullet(), "Bullet");
				}
				else if (GameInfo->PlayerType == 3) {
					ObjMgr->AddObject(new Bullet(), "Bullet");
				}
				GameInfo->Ammo[GameInfo->PlayerType]--;
			}
			m_DelayTime = 0.f;
		}
	}
	if (INPUT->GetKey('R') == KeyState::DOWN && !isReload) {
		isReload = true;
	}
	if (isReload) {
		ReloadTime += dt;
		if (ReloadTime > 5.f) {
			GameInfo->Ammo[GameInfo->PlayerType] = GameInfo->MaxAmmo[GameInfo->PlayerType];
			isReload = false;
		}
	}
	else {
		if (GameInfo->Ammo[0] <= 0) {
			isReload = true;
			ReloadTime += dt;
			if (ReloadTime > 5.f) {
				GameInfo->Ammo[0] = GameInfo->MaxAmmo[0];
				isReload = false;
			}
		}
	}
	GameInfo->isReload = isReload;
}

void Player::CollisionBox()
{
	ColBox[LEFT]->SetPosition(m_Position.x - m_Size.x / 2+78, m_Position.y);
	ColBox[RIGHT]->SetPosition(m_Position.x + m_Size.x / 2 - 78, m_Position.y);
	ColBox[UP]->SetPosition(m_Position.x, m_Position.y - m_Size.y / 2 );
	ColBox[DOWN]->SetPosition(m_Position.x, m_Position.y +m_Size.y / 2 );
	ColBox[HIT]->SetPosition(m_Position);
	m_ColBox ->SetPosition(m_Position);
}

void Player::GunType()
{
}

void Player::Buff()
{
}
