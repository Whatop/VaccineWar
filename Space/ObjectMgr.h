#pragma once
#include <algorithm>

#define ObjMgr ObjectMgr::GetInst()
class ObjectMgr : public Singleton<ObjectMgr>
{
public:
	std::list<Object*> m_Objects;

public:
	ObjectMgr();
	~ObjectMgr();

	void Release();
	void DeleteCheak();
	void Update(float deltaTime, float time);
	void Render();

public:
	void AddObject(Object* obj, const std::string tag);
	void RemoveObject(Object* obj);
	void CollisionCheak(Object* obj, const std::string tag);
	void DeleteObject(std::string tag);

};

