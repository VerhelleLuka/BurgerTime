#pragma once
#include <string>
#include "Texture2D.h"
#include "Structs.h"
namespace dae
{
	class Animation
	{
	public:
		Animation(int rows, int nrFrames, std::string name);
		~Animation() = default;
		void Update(float deltaTime);
		void Render();

		void SetTexture(const std::string& fileName);
		void SetScale(float scale) { m_Scale = scale; }
	private:

		std::shared_ptr<Texture2D> m_pTexture;
		//No columns required, I will split up the given spritesheet into multiple ones
		int  m_Rows;
		std::string m_Name;
		int m_NrFrames, m_CurrentFrame;
		float m_FramesSec = 0.16f;
		float m_FrameChangeCounter = 0.f;
		Float2 m_Position;
		Float4 m_DstRect, m_SrcRect;
		float m_Scale {1.0f};
	};
}