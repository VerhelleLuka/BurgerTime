
#include "MiniginPCH.h"
#include "TrayComponent.h"
#include "BurgerComponent.h"
#include <InputManager.h>


void dae::TrayComponent::OnOverlap(RigidBodyComponent* other)
{
	if (other->GetParent()->GetComponent<BurgerComponent>("BurgerComp"))
	{
		other->GetParent()->GetComponent<BurgerComponent>("BurgerComp")->SetCaught(true);
		if (other->GetParent()->GetComponent<SpriteComponent>("BurgerSprite")->GetAnimationName() == "Top_bun")
		{
			GameManager::GetInstance().BurgerCompleted();
		}
	}
}