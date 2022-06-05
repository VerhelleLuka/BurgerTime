#pragma once
#include <string>
#include "Texture2D.h"
#include "Structs.h"
#include "Transform.h"
namespace dae
{
	class Animation
	{
	public:
		Animation(int rows, int nrFrames);
		~Animation() = default;
		void Update(float deltaTime,Transform transform);
		void Render();

		void SetTexture(const std::string& fileName);
		void SetScale(float scale) { m_Scale = scale; }

		void SetPos(Float2 position);
		Float2 GetPos() const { return m_Position; }
		float GetWidth() const { return (float)m_Width; }
		float GetHeight() const { return (float)m_Height; }

		float GetScaledWidth() const{ return (float)m_Width * m_Scale; }
		float GetScaledHeight() const{ return (float)m_Height * m_Scale; }
		//Set all positions to the position of the sprite that is in use right now
		void SetGlobalPos(Float2 position) { m_Position = position; }
		void SetReversed(bool flipped) { m_IsFlipped = flipped; }

		//void SetIsDirty(bool isDirty) { m_IsDirty = isDirty; }
		//bool GetIsDirty() { return m_IsDirty; }

		int GetFrameNr() const { return m_CurrentFrame; }
		void SetFrameNr(int frame) { m_CurrentFrame = frame; }
		int GetNrFrames() const { return m_NrFrames; }
	private:

		std::shared_ptr<Texture2D> m_pTexture;
		//No columns required, I will split up the given spritesheet into multiple ones where there are 
		//no columns
		int  m_Rows;
		int m_NrFrames, m_CurrentFrame;
		float m_FramesSec = 0.16f;
		float m_FrameChangeCounter = 0.f;
		Float2 m_Position;
		Float4 m_DstRect, m_SrcRect;
		float m_Scale{ 1.0f };
		bool m_IsFlipped = false;

		int m_Width{0}, m_Height{ 0 };
		//bool m_IsDirty;

	};
}