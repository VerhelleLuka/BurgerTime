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
		//Platform(Float2 pos, float w) :position{ pos }, width{ w } {}
		Float2 position;
		float width;
		const float height{ 2.0f };
	};
	struct Ladder
	{
		Float2 position;
		float height;
		const float width = 10.0f;
	};
	//enum class CharacterState
	//{

	//};
}