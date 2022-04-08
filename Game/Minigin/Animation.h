#pragma once
#include <string>
#include "Texture2D.h"
#include "Structs.h"
namespace dae
{
	class Animation
	{
	public:
		Animation(int rows, int nrFrames);
		~Animation() = default;
		void Update(float deltaTime);
		void Render();

		void SetTexture(const std::string& fileName);
		void SetScale(float scale) { m_Scale = scale; }

		void SetPos(Float2 position);
		Float2 GetPos() const { return m_Position; }
		//Set all positions to the position of the sprite that is in use right now
		void SetGlobalPos(Float2 position) { m_Position = position; }
		void SetReversed(bool reversed) { m_IsReversed = reversed; }
	private:

		std::shared_ptr<Texture2D> m_pTexture;
		//No columns required, I will split up the given spritesheet into multiple ones
		int  m_Rows;
		int m_NrFrames, m_CurrentFrame;
		float m_FramesSec = 0.16f;
		float m_FrameChangeCounter = 0.f;
		Float2 m_Position;
		Float4 m_DstRect, m_SrcRect;
		float m_Scale {1.0f};
		//We need a member for deltatime to make our character move
		float m_DeltaTime;
		bool m_IsReversed = false;
	};
}