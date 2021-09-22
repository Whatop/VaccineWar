#pragma once
class RankScene : public Scene
{
	
public:
	RankScene();
	~RankScene();

	void Init();
	void Release();

	void Update(float deltaTime, float Time);
	void Render();
};

