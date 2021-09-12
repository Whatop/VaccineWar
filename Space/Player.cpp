#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Missile.h"
#include "Torpedo.h"
#include "NavalProjectile.h"

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
	ColBox[LEFT]->SetScale(1, 0.3f);
	ColBox[RIGHT] = Sprite::Create(L"Painting/Player/Height.png");
	ColBox[RIGHT]->SetScale(1, 0.3f);
	ColBox[UP] = Sprite::Create(L"Painting/Player/Width.png");
	ColBox[UP]->SetScale(0.3f, 1);
	ColBox[DOWN] = Sprite::Create(L"Painting/Player/Width.png");
	ColBox[DOWN]->SetScale(0.3f, 1);
	ColBox[HIT] = Sprite::Create(L"Painting/Player/HitBox.png");
	ColBox[HIT]->SetScale(0.75f, 0.75f);
	Shield = Sprite::Create(L"Painting/Player/Shield.png");
	Shield->SetScale(0.75f, 0.75f);
	Shield->m_Visible = false;
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
			Shield->m_Visible = false;
			m_Player->R = 255;
			m_Player->G = 255;
			m_Player->B = 255;
			PlayerPlatform->SetAnimeColor();
		}
		if (!HitDelay) {
			Shield->m_Visible = true;
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
		if (!isSpeed) {
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
		}
		else {
			SpeedTime += dt;
			m_Speed = 750.f;
			if (SpeedTime > 5) {

				isSpeed = false;
				SpeedTime = 0.f;
			}
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
	if (isInvincible) {
		Shield->m_Visible = true;
		InvincibleTime += dt;
		if (InvincibleTime > 2) {
			Shield->m_Visible = false;
			isInvincible = false;
			InvincibleTime = 0.f;
		}
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
	Shield->Render();
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
	if (obj->m_Tag == "AddMachineGun")
	{
		if (GameInfo->Ammo[0]+30 <= 180) {
			GameInfo->Ammo[0] += 30;
		}
		else {
			GameInfo->Ammo[0] = 180;
		}
		obj->SetDestroy(true);
	}
	if (obj->m_Tag == "AddTorpedo")
	{
		if (GameInfo->Ammo[2] + 5 <= 15) {
			GameInfo->Ammo[2] += 5;
		}
		else {
			GameInfo->Ammo[2] = 15;
		}
		obj->SetDestroy(true);
	}
	if (obj->m_Tag == "AddMissile")
	{
		if (GameInfo->Ammo[3] + 3 <= 10) {
			GameInfo->Ammo[3] += 3;
		}
		else {
			GameInfo->Ammo[3] = 10;
		}
		obj->SetDestroy(true);
	}
	if (obj->m_Tag == "SpeedUp")
	{
		isSpeed = true;
		SpeedTime = 0.f;
		obj->SetDestroy(true);
	}
	if (obj->m_Tag == "Invincibility")
	{
		isInvincible = true;
		InvincibleTime = 0.f;
		obj->SetDestroy(true);
	}
	if (obj->m_Tag == "EnemyBullet") {
		RECT rc;
		if (IntersectRect(&rc, &ColBox[4]->m_Collision, &obj->m_Collision)) {
			if (!isInvincible) {
				GameInfo->PlayerHit = true;
				Damage_Received = obj->m_Atk;
			}
			obj->SetDestroy(true);
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
	GunType();
	// 기관총, 함포 , 어뢰, 미사일 
	if (INPUT->GetKey('Z') == KeyState::PRESS) {
		if (m_DelayTime > m_Rpm && !isReload) {
			if (GameInfo->Ammo[GameInfo->PlayerType] > 0) {
				if (GameInfo->PlayerType == 0) {
					ObjMgr->AddObject(new Bullet(), "Bullet");
					GameInfo->Ammo[GameInfo->PlayerType]--;
				}
				else if (GameInfo->PlayerType == 1) {
					for (int i = 0; i < GameInfo->Ammo[1]; i++) {
						ObjMgr->AddObject(new NavalProjectile(), "Bullet");
					}
					GameInfo->Ammo[GameInfo->PlayerType] = 0;
				}
				else if (GameInfo->PlayerType == 2) {
					ObjMgr->AddObject(new Torpedo(m_Position), "Bullet");
					GameInfo->Ammo[GameInfo->PlayerType]++;
					GameInfo->Ammo[GameInfo->PlayerType]--;
				}
				else if (GameInfo->PlayerType == 3) {
					ObjMgr->AddObject(new Missile(m_Position), "Bullet");
					GameInfo->Ammo[GameInfo->PlayerType]++;
					GameInfo->Ammo[GameInfo->PlayerType]--;
				}
			}
			m_DelayTime = 0.f;
		}
	}
	if (INPUT->GetKey('R') == KeyState::DOWN && !isReload&& GameInfo->Ammo[0] < GameInfo->MaxAmmo[0]
		&& GameInfo->PlayerType == 0) {
		isReload = true;
	}
	if (isReload) {
		ReloadTime += dt;
		if (ReloadTime > 5.f) {
			GameInfo->Ammo[0] = GameInfo->MaxAmmo[0];
			isReload = false;
			ReloadTime = 0.f;
		}
	}
	else {
		if (GameInfo->Ammo[GameInfo->PlayerType] <= 0) {
			isReload = true;
			ReloadTime += dt;
			if (ReloadTime > 5.f) {
				GameInfo->Ammo[0] = GameInfo->MaxAmmo[0];
				isReload = false;
				ReloadTime = 0.f;
			}
		}
	}
	GameInfo->isReload = isReload;

	if(GameInfo->Ammo[1] < 5)
		chargeTime += dt;
	else 
		chargeTime = 0.f;

	if (chargeTime > 1) {
		GameInfo->Ammo[1]++;
		chargeTime = 0.f;
	}
}

void Player::CollisionBox()
{
	ColBox[LEFT]->SetPosition(m_Position.x - m_Size.x / 2+78, m_Position.y);
	ColBox[RIGHT]->SetPosition(m_Position.x + m_Size.x / 2 - 78, m_Position.y);
	ColBox[UP]->SetPosition(m_Position.x, m_Position.y - m_Size.y / 2 );
	ColBox[DOWN]->SetPosition(m_Position.x, m_Position.y +m_Size.y / 2 );
	ColBox[HIT]->SetPosition(m_Position);
	m_ColBox->SetPosition(m_Position);
	Shield->SetPosition(m_Position);
}

void Player::GunType()
{
	if (GameInfo->PlayerType == 0) {
		if (GameInfo->SKILL_Focus_attck)
			m_Rpm = 0.25f / 4.f;
		else
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

}

void Player::Buff()
{
}

void Player::Skill()
{
	GameInfo->SKILL_Air_force = true;
	GameInfo->SKILL_Focus_attck = true;
}
