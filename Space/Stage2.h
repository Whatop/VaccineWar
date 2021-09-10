#pragma once
class Stage2 : public Scene
{
	Sprite* m_BackGround[6][2];

	Sprite* m_Cover;

	Sprite* UpWall;
	Sprite* DownWall;
	Sprite* Right_Limit;
	Sprite* Left_Limit;

	Sprite* m_Choice;
	Sprite* ChoicePack[3];

	Sprite* ScoreScene;
	Sprite* ScoreText;

	float ScaleScene;
	float ScaleText;
	int RCrad[3];


public:
	Stage2();
	~Stage2();

	void Init();
	void Release();

	void Update(float deltaTime, float time);
	void Render();

	void BGInit();

	void MoveBG();
	void ResetBG();
	void OnCollisionCard();
	void NextScene();
};

