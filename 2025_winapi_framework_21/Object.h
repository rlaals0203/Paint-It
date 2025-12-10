#pragma once
class Component;
class Collider;
class Object
{
public:
	Object();
	~Object();
public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hdc);
	void ComponentRender(HDC _hdc);
	virtual void EnterCollision(Collider* _other){}
	virtual void StayCollision(Collider* _other) {}
	virtual void ExitCollision(Collider* _other) {}
public:
	virtual void SetPos(Vec2 _pos) { m_pos = _pos; }
	virtual void SetSize(Vec2 _size) { m_size = _size; }
	float GetRotation() const { return m_rotation; }
	void SetRotation(float rot) { m_rotation = rot; }
public:
	bool GetIsDead() const { return m_isDie; }
	void SetDead() { m_isDie = true; }
	const Vec2& GetPos() const { return m_pos; }
	const Vec2& GetSize()const { return m_size; }

	void OnHit();
	void SetCanOutofBounds(bool canOut) { m_canOutofbounds = canOut; }
	void SetDontDestroy() { m_dontDestroyOnComplete = true; }
protected:
	void Translate(Vec2 _delta)
	{
		m_pos.x += _delta.x;
		m_pos.y += _delta.y;
	}
	void Scale(Vec2 _s)
	{
		if (_s.x <= 0.f || _s.y <= 0.f)
			return;
		m_size.x *= _s.x;
		m_size.y *= _s.y;
	}
public:
	template<typename T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Component로부터 상속받아야 함");
		T* compo = new T;
		compo->SetOwner(this);
		compo->Init(); // 선택
		m_vecComponents.push_back(compo);
		return compo;
	}
	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* com : m_vecComponents)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
private:
	bool CheckOutofbounds()
	{
		Vec2 pos = GetPos();
		return (m_canOutofbounds && (pos.x > WINDOW_WIDTH + 500 || pos.x < -500
			|| pos.y > WINDOW_HEIGHT + 500 || pos.y < -500));
	}
protected:
	bool m_isDie;
	bool m_isRight; //오른쪽을 보고 있는지
	bool m_isBlink;
	bool m_dontDestroyOnComplete;
private:
	float m_rotation;
	Vec2 m_pos;
	Vec2 m_size;
	vector<Component*> m_vecComponents;
	float m_blinkDur;
	float m_blinkTime;
	bool m_canOutofbounds;
};

