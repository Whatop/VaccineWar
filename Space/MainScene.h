#pragma once
class MainScene : public Scene
{
	Sprite* Player;
	Animation* PlayerAnimation;

	Sprite* m_Title;
	Sprite* m_Blind;
	Sprite* m_Button[4];

	Sprite* m_BackGround[6][2];

		
	Sprite* HelpScene;
	float HelpScale;

	float ShackX;
	float acc1,acc2;

	//movePlayer
	bool isMovePlayer;
	float AccTime;

	//Rank
	Sprite* RankScene;
	float RankScale;

	Sprite* m_BG;

	TextMgr* m_First;
	TextMgr* m_Secend;
	TextMgr* m_Third;

	HWND m_Sound1;
	HWND m_Sound2;

	bool isRankScene;
	bool isHelpScene;
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

	void RankRender();
};

