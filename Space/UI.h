#pragma once
class UI : public Singleton<UI>
{
	// HpBar
	Sprite* PlayerBar;
	Sprite* BossBar;
	Sprite* BossBackGround;
	
	//StateWindow
	Sprite* StateWindow;
	Sprite* ScoreImage;
	Sprite* HpImage[2];
	Sprite* TimeLmitImage;
	Sprite* SpeedImage;
	Sprite* SpeedFrameImage;

	// Text
	TextMgr* TestText;
	TextMgr* ScoreText;
	TextMgr* ResultScoreText;
	TextMgr* Timelimit;
	TextMgr* AmmoText;
	TextMgr* ReloadText;
	TextMgr* CoolTimeText;

	TextMgr* BuffCoolTime;
	
	//delay
	float DelayCoolTime;
	bool isDelay;

	//Buff : ���ǵ�, ����, ���� ����
	Sprite* BuffState[3];

	//Cover
	Sprite* UIScoreFrame;

	//��ǥ
	Sprite* UIAim;

	//Skill Air Attack
	Sprite* Skill_1[2];// 0 Skill 1 CoolDown
	Sprite* Skill_2[2];

	// KILL, ITEM, BONUS, ALL
	float limit[4];
	float ScoredaleyTime;

	//03:00:00
	float Time[6];

	//MiniMap 0=BACKGROUND 1=PLAYER
	Sprite* MiniMap[2];

	//Gun
	//MachineGun, NavalProjectile, Torpedo, Missile;
	Sprite* GunTpye;


	Sprite* ScoreScene;
	Sprite* ScoreNameText;

	float ScaleScene;
	float ScaleText;
	//Reload
	float Reload;
	std::string a;

public:
	UI();
	~UI();

	void Init();
	void Release();

	void Update();
	void Render();

	void ScoreUI();

	void ScoreTextUI();

	void Timer();
	void Bar();
	void Text();

	void NextScene();
};

