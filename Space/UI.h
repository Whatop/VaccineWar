#pragma once
class UI : public Singleton<UI>
{
	// HpBar
	Sprite* PlayerBar;
	Sprite* BossBar;
	Sprite* MiniBossBar;
	
	//StateWindow
	Sprite* StateWindow;
	Sprite* ScoreImage;
	Sprite* HpImage;
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
	

	//Cover
	Sprite* UIScoreFrame;

	//Skill
	Sprite* Skill_1;
	Sprite* Skill_2;

	// KILL, ITEM, BONUS, ALL
	float limit[4];
	float ScoredaleyTime;

	//03:00:00
	float Time[6];

	//MiniMap
	Sprite* MiniMap;

	//Gun
	//MachineGun, NavalProjectile, Torpedo, Missile;
	Sprite* GunTpye;

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
};

