#pragma once
class Obstacle : public Object
{
	Animation* m_Mine;
	Animation* m_Obstacle;
	Sprite* m_ColBox;
	Sprite* ColBox[20];
	bool isMine;
	bool isBoom;
public:
	Obstacle(Vec2 SpawnPoint,bool isboom = false);
	~Obstacle();

	void Update(float deltaTime, float Time);
	void Render();
	void Move();
	void ColBoxPos();
	void OnCollision(Object* obj);
};

