#pragma once

namespace dae
{
	struct Float4
	{
		float x{}, y{}, z{}, w{};
	};
	struct Float2
	{
		float x{}, y{};

		Float2 operator+=(Float2& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;

			return *this;
		}
	};

	struct Platform
	{
		int row, column;
	};
	struct Ladder
	{
		int row, column;
	};
	struct Burger
	{
		int row, column;
		std::string partName;
	};
}