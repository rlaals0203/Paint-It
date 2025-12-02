#include "pch.h"
#include "Object.h"
#include "InputManager.h"
#include "Component.h"
Object::Object()
	: m_pos{}
	, m_size{}
	, m_isDie(false)
	, m_isBlink(false)
	, m_canOutofbounds(true)
	, m_isRight(false)
	, m_blinkDur(0.08f)
	, m_blinkTime(0.f)
	,m_rotation(0.f)
{

}

Object::~Object()
{
	for (Component* com : m_vecComponents)
		SAFE_DELETE(com);
	m_vecComponents.clear();
}

void Object::Update()
{
	if (CheckOutofbounds()) //화면 밖으로 나가면 삭제
	{
		//m_isDie = true;
	}

	if (m_isBlink)
	{
		m_blinkTime -= fDT;
		if (m_blinkTime <= 0.f)
			m_isBlink = false;
	}

	if (GET_KEY(KEY_TYPE::T))
	{
		OnHit();
	}
}

void Object::LateUpdate()
{
	for (Component* com : m_vecComponents)
	{
		if (com != nullptr)
			com->LateUpdate();
	}

}

void Object::Render(HDC _hdc)
{
	RECT_RENDER(_hdc, m_pos.x, m_pos.y, m_size.x, m_size.y);
	RECT_RENDER(_hdc, m_pos.x, m_pos.y, m_size.x, m_size.y);
}

void Object::ComponentRender(HDC _hdc)
{
	for (Component* com : m_vecComponents)
	{
		if (com != nullptr)
			com->Render(_hdc);
	}
}

void Object::OnHit()
{
	m_isBlink = true;
	m_blinkTime = m_blinkDur;
}
