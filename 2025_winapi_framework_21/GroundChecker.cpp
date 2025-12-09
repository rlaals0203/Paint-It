#include "pch.h"
#include "GroundChecker.h"
#include "Collider.h"

GroundChecker::GroundChecker()
{
    auto* col = AddComponent<Collider>();
    col->SetSize({ 40.f, 2.f });
    col->SetName(L"GroundChecker");
}

GroundChecker::~GroundChecker()
{
}

void GroundChecker::EnterCollision(Collider* _other)
{
    if (_other->GetName() == L"Ground")
    {
        SetIsGround(true);
        m_callback(true);
    }
}

void GroundChecker::ExitCollision(Collider* _other)
{
    if (_other->GetName() == L"Ground")
    {
        SetIsGround(false);
        m_callback(false);
    }
}