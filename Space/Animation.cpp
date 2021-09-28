#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
	: m_AutoPlay(0)
	, m_CurrentFrame(0)
	, m_Delay(0.f)
	, m_FrameCount(0.f)
	, A(255)
	, R(255)
	, G(255)
	, B(255)
{
}

Animation::~Animation()
{
}

void Animation::AddContinueFrame(std::wstring fileName, int firstFrame, int lastFrame, D3DCOLOR ColorKey)
{
	if (firstFrame < lastFrame)
	{
		for (int i = firstFrame; i <= lastFrame; i++)
		{
			Sprite* sprite = Sprite::Create(fileName.c_str() + std::to_wstring(i) + L".png", ColorKey);
			sprite->SetParent(this);
			if (sprite)
				m_Anims.push_back(sprite);
		}
	}
}

void Animation::NextFrame()
{
	m_CurrentFrame++;
	m_FrameCount = 0.f;

	if (m_CurrentFrame > m_Anims.size() - 1)
	{
		m_CurrentFrame = 0;
	}
}

void Animation::BackFrame()
{
	m_CurrentFrame--;
	m_FrameCount = 0.f;

	if (m_CurrentFrame < 0)
	{
		m_CurrentFrame = m_Anims.size() - 1;
	}
}

void Animation::SetAnimeColor(int a, int r, int g, int b)
{
	m_Anims.at(m_CurrentFrame)->A = a;
	m_Anims.at(m_CurrentFrame)->R = r;
	m_Anims.at(m_CurrentFrame)->G = g;
	m_Anims.at(m_CurrentFrame)->B = b;
}

void Animation::Init(float delay, bool play)
{
	m_Delay = delay;
	m_AutoPlay = play;
}

void Animation::Update(float deltaTime, float time)
{
	m_FrameCount += dt;

	if (m_Destroy)
	{
		m_Anims.at(m_CurrentFrame)->SetDestroy(true);
	}

	if (m_AutoPlay == true)
	{
		if (m_FrameCount > m_Delay)
		{
			m_CurrentFrame++;
			m_FrameCount = 0.f;
		}
	}
	
	if (m_CurrentFrame > m_Anims.size() - 1)
	{
		m_CurrentFrame = 0;
	}
	m_Anims.at(m_CurrentFrame)->A = A;
	m_Anims.at(m_CurrentFrame)->R = R;
	m_Anims.at(m_CurrentFrame)->G = G;
	m_Anims.at(m_CurrentFrame)->B = B;

	m_Anims.at(m_CurrentFrame)->Update(deltaTime, time);
}

void Animation::Render()
{
	if (m_Parent)
	{
			SetRect(&m_Parent->m_Collision,
				(m_Parent->m_Position.x - (m_Size.x * m_Parent->m_Scale.x) / 2),
				(m_Parent->m_Position.y - (m_Size.y * m_Parent->m_Scale.y) / 2),
				(m_Parent->m_Position.x + (m_Size.x * m_Parent->m_Scale.x) / 2)
				, (m_Parent->m_Position.y + (m_Size.y * m_Parent->m_Scale.y) / 2));
		
		m_Parent->m_Size = m_Size;
	}
	else
	{
		SetRect(&m_Collision, m_Position.x - m_Size.x / 2, m_Position.y - m_Size.y / 2,
			m_Position.x + m_Size.x / 2, m_Position.y + m_Size.y / 2);
	}

	m_Anims.at(m_CurrentFrame)->Render();
}