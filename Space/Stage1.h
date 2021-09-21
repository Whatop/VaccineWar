#pragma once
class Stage1 : public Scene
{
	Sprite* m_BackGround[6][2];

	Sprite* m_Cover;

	Sprite* UpWall;
	Sprite* DownWall;
	Sprite* Right_Limit;
	Sprite* Left_Limit;

	bool one;
	float sdTime;
public:
	Stage1();
	~Stage1();

	void Init();
	void Release();

	void Update(float deltaTime, float time);
	void Render();

	void BGInit();

	void MoveBG();
	void ResetBG();
	void OnCollisionCard();
};

