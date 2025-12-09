#include "pch.h"
#include "OriginPoint.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceManager.h"

OriginPoint::OriginPoint(float aniTime, float endTime, float waitTime)
	: Object()
	, m_aniTime(aniTime)
	, m_endTime(endTime)
	, m_waitTime(waitTime)
{
	m_animator = AddComponent<Animator>();
	m_pointTex = GET_SINGLE(ResourceManager)->GetTexture(L"originpoint");
	
	m_originName = L"origin";
	//m_originEndName = L"originEnd";

	m_animator->CreateAnimation(
		m_originName, m_pointTex,
		{ 0.f,0.f }, { 64.f, 64.f },
		{ 64.f,0.f }, 4, aniTime);

	//m_animator->CreateAnimation(
	//	m_originEndName, m_pointTex,
	//	{ 192.f,0.f }, { 64.f, 64.f },
	//	{ 64.f,0.f }, 1, endTime);

	m_animator->Play(m_originName, PlayMode::Once);
}

OriginPoint::~OriginPoint()
{
}

void OriginPoint::Update()
{
	m_waitTime -= fDT;
	if (m_waitTime > 0)
	{
		return;
	}

	m_endTime -= fDT;
	if (m_endTime > 0)
	{
		return;
	}

	m_isDie = true;
}

void OriginPoint::Render(HDC _hdc)
{
	Object::ComponentRender(_hdc);
}
