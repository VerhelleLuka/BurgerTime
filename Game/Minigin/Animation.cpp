#include "MiniginPCH.h"
#include "Animation.h"
#include "Structs.h"
#include "Renderer.h"
#include "ResourceManager.h"
dae::Animation::Animation(int rows, int nrFrames)
	:m_Rows(rows),
	m_NrFrames(nrFrames),
	m_CurrentFrame(0)//,
	//m_DeltaTime(0.f),
	//m_IsDirty(false)
{
}
void dae::Animation::Update(float elapsedSec, Transform transform)
{
	//m_DeltaTime = elapsedSec;
	int width, height;
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &width, &height);
	//SDL_RenderCopy(Renderer::GetInstance().GetSDLRenderer(), )
	width /= m_NrFrames;
	m_DstRect = Float4
	{
		transform.GetPosition().x,
		transform.GetPosition().y,
		(float)width * m_Scale,
		(float)height* m_Scale

	};

	//if (!m_IsFlipped)
	//{
		m_SrcRect = Float4
		{
			(m_DstRect.z / m_Scale) * m_CurrentFrame,
			0,
			(m_DstRect.z / m_Scale),
			(m_DstRect.w / m_Scale)
		};
	//}
	//else
	//{
	//	m_SrcRect = Float4
	//	{
	//		(m_DstRect.z / m_Scale) * m_CurrentFrame + (m_DstRect.z / m_Scale),
	//		0,
	//		(m_DstRect.z / m_Scale)* m_CurrentFrame,
	//		(m_DstRect.w / m_Scale)
	//	};
	//}

	m_FrameChangeCounter += elapsedSec;
	if (m_FrameChangeCounter >= m_FramesSec)
	{
		m_FrameChangeCounter = 0.f;
		if (m_CurrentFrame < m_NrFrames -1 )
		{
			m_CurrentFrame++;
		}
		else
			m_CurrentFrame = 0;

	}
}
void dae::Animation::Render()
{
	if (m_IsFlipped)
	{
		
	}
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_SrcRect, m_DstRect, m_IsFlipped);
}

void dae::Animation::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void dae::Animation::SetPos(Float2 pos)
{
	m_Position.x += pos.x;
	m_Position.y += pos.y;
}
