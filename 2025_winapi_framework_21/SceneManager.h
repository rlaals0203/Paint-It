#pragma once
//class Scene;
#include "Scene.h"
class SceneManager
{
	DECLARE_SINGLE(SceneManager);
public:
	void Init();
	void Update();
	void Release();
	void FixedUpdate(float _fixedDT);
	void PhysicsSyncColliders();
	void Render(HDC _hdc);
public:
	void RequestDestroy(Object* _obj)
	{
		if (m_curScene)
			m_curScene->RequestDestroy(_obj);
	}
	void RegisterScene(const wstring& _name, std::shared_ptr<Scene> _scene);
	void LoadScene(const wstring& _name);
	void RequestLoadScene(const std::wstring& _name);
public:
	const std::shared_ptr<Scene>& GetCurScene() const
	{
		return m_curScene;
	}
private:
	//Scene* m_scene;
	std::wstring m_nextScene;
	std::shared_ptr<Scene> m_curScene;
	std::unordered_map<wstring, std::shared_ptr<Scene>> m_mapScenes;
	//vector<int> v;
};

