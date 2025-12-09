#include "pch.h"
#include "Floor.h"
#include "Collider.h"
Floor::Floor()
{
	auto* col = AddComponent <Collider>();
	col->SetSize({ 2000.f, 100.f });
	col->SetName(L"Ground");

}

Floor::~Floor()
{
}

void Floor::Update()
{
}

void Floor::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}
