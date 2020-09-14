#ifndef VECTOR_2D_HEADER
#define VECTOR_2D_HEADER

struct Vector2D
{
	Vector2D() : x(0.0f), y(0.0f) {};
	Vector2D(const float& anX, const float& aY) : x(anX), y(aY) {};

	float x;
	float y;
};
#endif