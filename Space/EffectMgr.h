#pragma once
class EffectMgr : public Object
{
	Animation* Effect;
public:
	EffectMgr(std::wstring filename, int start, int end, float speed, Vec2 Pos,float scalex=1,float scaley=1, D3DXCOLOR Color = D3DCOLOR_XRGB(0, 248, 0));
	~EffectMgr();

	int Start;
	int End;

	void Update(float deltaTime, float time);
	void Render();
	void OnCollision(Object* other);
};

