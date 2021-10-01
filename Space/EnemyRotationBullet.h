#pragma once
class EnemyRotationBullet : public Object
{
	Animation* m_Bolt;
	Sprite* m_Bullet;
	Vec2 m_Dire;
	float m_Speed;
	float m_AfterR;
public:
	EnemyRotationBullet(Vec2 Pos,float r,float afteR=0);
	~EnemyRotationBullet();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* obj);

	void Move();
};

