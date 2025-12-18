#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
#include "Rigidbody.h"
#include "DOTweenCompo.h"

void Scene::FixedUpdate(float _fixedDT)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
		{
			if (obj && !obj->GetIsDead())
			{
				if (auto rb = obj->GetComponent<Rigidbody>())
				{
					if (rb != nullptr)
						rb->FixedUpdate(_fixedDT);
				}
			}
		}
	}
}

Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Update()
{
	if (m_isEnd)
		return;
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		if (m_isEnd)
			return;
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
		{
			if (m_isEnd)
				return;
			if (!obj->GetIsDead())
				obj->Update();
		}
	}
}

void Scene::LateUpdate()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];

		auto iter = vec.begin();
		while (iter != vec.end())
		{
			if ((*iter)->GetIsDead())
			{
				delete (*iter);
				(*iter) = nullptr;
				iter = vec.erase(iter);
			}
			else
			{
				(*iter)->LateUpdate();
				++iter;
			}
		}
	}
}

void Scene::Render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
		{
			if (!obj->GetIsDead())
				obj->Render(_hdc);
		}
	}
}

void Scene::Release()
{
	m_isEnd = true;
	FlushEvent();

	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
		{
			if (auto tween = obj->GetComponent<DOTweenCompo>())
				tween->KillAllTweens();

			if (obj)
				delete obj;
		}
		vec.clear();
	}
	GET_SINGLE(CollisionManager)->CheckReset();
}

void Scene::RequestDestroy(Object* obj)
{
	if (obj == nullptr)
		return;

	if (!obj->GetIsDead())
	{
		obj->SetDead();
	}
}

void Scene::FlushEvent()
{
	for (auto& spawn : m_spawnObject)
	{
		AddObject(spawn.obj, spawn.type);
	}
	m_spawnObject.clear();
}

void Scene::ClearScene()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
		{
			if (obj->IsDestroyOnComplete())
				obj->SetDead();
		}
	}
}

void Scene::RequestSpawn(Object* _obj, Layer _type)
{
	SpawnObject newObj;
	newObj.obj = _obj;
	newObj.type = _type;
	m_spawnObject.push_back(newObj);
}

void Scene::RemoveObject(Object* _obj)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& v = m_vecObj[i];
		auto iter = std::find(v.begin(), v.end(), _obj);
		if (iter != v.end())
		{
			v.erase(iter);
			return;
		}
	}
}