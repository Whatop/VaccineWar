#pragma once
class MainScene : public Scene
{
	Sprite* Player;
	Animation* PlayerAnimation;

	Sprite* m_Title;
	Sprite* m_MainScene;
	Sprite* m_Blind;
	Sprite* m_Button[4];

	Sprite* m_BackGround[6][2];

	float ShackX;
	float acc1,acc2;

	//movePlayer
	bool isMovePlayer;
	float AccTime;

public:
	MainScene();
	~MainScene();

	void Init();
	void Release();

	void Update(float deltaTime,float time);
	void Render();

	void BGInit();

	void MoveBG();
	void ResetBG();
};

