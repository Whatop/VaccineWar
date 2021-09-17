#pragma once
class MainScene : public Scene
{
	Sprite* m_Title;
	Sprite* m_MainScene;
	Sprite* m_Blind;
	Sprite* m_Button[4];

	float ShackX;
	float acc1,acc2;

public:
	MainScene();
	~MainScene();

	void Init();
	void Release();

	void Update(float deltaTime,float time);
	void Render();
};

