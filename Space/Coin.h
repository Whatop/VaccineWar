#pragma once

class Coin : public Object
{
	Animation* LoopCoin;
	Sprite* m_Coin;

	float m_Speed;
	float AccTime; // ���ӵ� Ÿ��
public:
	Coin(Vec2 Pos);
	~Coin();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);
	
	void Move();
};

