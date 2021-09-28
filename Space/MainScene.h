#pragma once
class MainScene : public Scene
{

	Sprite* m_BackGround[6][2];
	Sprite* m_Title;
	Sprite* m_Button[4];

	Sprite* Player;
	Animation* PlayerAnimation;


	//Title
	float TM_Time;
	float TM_Up;
	float TM_Down;

	//movePlayer
	bool isMovePlayer;
	float AccTime;

	//Rank
	Sprite* RankScene;
	float RankScale;
	bool isRankScene;
	TextMgr* m_RankText;

	//Help
	Sprite* HelpScene;
	float HelpScale;
	bool isHelpScene;
public:
	MainScene();
	~MainScene();

	void Init();
	void Release();

	void Update(float deltaTime, float time);
	void Render();

	void BGInit();

	void MoveBG();
	void ResetBG();

	void RankRender();
};

