#include "pch.h"
#include "Component.h"

Component::Component()
	: m_owner(nullptr)
	, m_isActive(true)
{
}

Component::~Component()
{
}