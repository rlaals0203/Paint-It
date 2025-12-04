#pragma once
struct Vec2
{
public:
	//Vec2() {}
	Vec2() = default;
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vec2(const Vec2& _other) : x(_other.x), y(_other.y) {}
public:
	Vec2 operator + (const Vec2& _vOther) const
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	Vec2 operator - (const Vec2& _vOther) const
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator * (const Vec2& _vOther) const
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (float _val) const
	{
		return Vec2(x * _val, y * _val);
	}

	Vec2 operator / (float _val) const
	{
		return Vec2(x / _val, y / _val);
	}

	Vec2 operator -() const
	{
		return Vec2(-x, -y);
	}
	// º¸·ù
	//Vec2 operator / (const Vec2& _vOther)
	//{
	//	assert(!(0.f == _vOther.x || 0.f == _vOther.y));
	//	return Vec2(x / _vOther.x, y / _vOther.y);
	//}
	Vec2 Rotate(const Vec2& v, float angle)
	{
		float rad = angle * 3.141592f / 180.f;
		float cosA = cosf(rad);
		float sinA = sinf(rad);

		return Vec2(
			v.x * cosA - v.y * sinA,
			v.x * sinA + v.y * cosA
		);
	}
	Vec2 Rotate(float angle) const
	{
		float c = cosf(angle);
		float s = sinf(angle);
		return {
			x * c - y * s,
			x * s + y * c
		};
	}
	void operator+=(const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;
	}
	void operator-=(const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;
	}
	float LengthSquared()
	{
		return x * x + y * y;
	}
	float Length()
	{
		return ::sqrt(LengthSquared());
	}
	void Normalize()
	{
		float len = Length();
		if (len < FLT_EPSILON)
			return;
		x /= len;
		y /= len;
	}
	float Dot(Vec2 _other)
	{
		return x * _other.x + y * _other.y;
	}
	float Cross(Vec2 _other)
	{
		return x * _other.y - y * _other.x;
	}
	float Lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}
	Vec2 Reflect(Vec2& dir, Vec2& normal)
	{
		return dir - normal * (2.f * dir.Dot(normal));
	}
public:
	float x = 0.f;
	float y = 0.f;
};

using Vector2 = Vec2;