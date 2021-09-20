#include "stdafx.h"
#include "EffectMgr.h"

EffectMgr::EffectMgr(std::wstring filename, int start, int end, float speed, Vec2 Pos,float scalex,float scaley, D3DXCOLOR Color)
{
	Effect = new Animation();
	Effect->AddContinueFrame(filename, start, end, Color);
	Effect->Init(speed, true);
	Effect->SetParent(this);
	m_Position = Pos;
	SetScale(scalex, scaley);

	Start = start;
	End = end;
	m_Layer = 3;
}

EffectMgr::~EffectMgr()
{
}

void EffectMgr::Update(float deltaTime, float time)
{
	if (GameInfo->isScoreScene) {
	}
	if (Effect->m_CurrentFrame >= End - 1)
	{
		ObjMgr->RemoveObject(this);
	}
	if (!GameInfo->isPause) {
		Effect->Update(deltaTime, time);
	}
	if (GameInfo->isPause || GameInfo->isScoreScene) {
		Effect->SetAnimeColor(105);
	}
}

void EffectMgr::Render()
{
	Effect->Render();
}

void EffectMgr::OnCollision(Object* other)
{
}
