#pragma once

//class Texture;
class Animation : public Object
{
private:
	std::vector<Sprite*>m_Anims;

	float m_Delay;
	bool m_AutoPlay;
	float m_FrameCount;

public:
	int m_CurrentFrame;
	int A, R, G, B;

public:
	Animation();
	~Animation();

	void AddContinueFrame(std::wstring fileName, int firstFrame, int lastFrame, D3DCOLOR ColorKey = COLORKEY_GREEN);
	void NextFrame();
	void BackFrame();

	void SetAnimeColor(int a = 255,int r = 255,int g = 255,int b = 255);

	void Init(float delay, bool play);
	void Update(float deltaTime, float time);
	void Render();
};

