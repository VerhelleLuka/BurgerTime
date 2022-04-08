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

		Float2 operator+=(const Float2& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;

			return *this;
		}
	};
}