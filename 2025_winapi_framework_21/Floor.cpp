#include "pch.h"
#include "Floor.h"
#include "Collider.h"
Floor::Floor()
{
	auto* col = AddComponent <Collider>();
	col->SetSize({ 2000.f, 50.f });
	col->SetName(L"Floor");
}

Floor::~Floor()
{
}

void Floor::Update()
{
}

void Floor::Render(HDC _hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 100, 100));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, hBrush);
	RECT_RENDER(_hdc, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 75, WINDOW_WIDTH, 150);
	SelectObject(_hdc, oldBrush);
	DeleteObject(hBrush);
	ComponentRender(_hdc);

}
