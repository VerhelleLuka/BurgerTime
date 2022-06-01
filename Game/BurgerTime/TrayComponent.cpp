
#include "MiniginPCH.h"
#include "TrayComponent.h"
#include "BurgerComponent.h"


void dae::TrayComponent::OnOverlap(RigidBodyComponent* other)
{
	if (other->GetParent()->GetComponent<BurgerComponent>("BurgerComp"))
	{
		other->GetParent()->GetComponent<BurgerComponent>("BurgerComp")->SetCaught(true);
	}
}