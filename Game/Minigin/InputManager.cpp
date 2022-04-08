#include "MiniginPCH.h"
#include "InputManager.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <thread>
#pragma comment(lib, "xinput.lib")
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl2.h>

#define NrOfPlayers 2
//pImpl try
class dae::InputManager::Impl
{

	XINPUT_STATE m_CurrentState[NrOfPlayers]{};
	XINPUT_STATE m_PreviousState[NrOfPlayers]{};

	std::map<ControllerButton, std::unique_ptr<Command>> m_ButtonCommands[NrOfPlayers];

public:

	Impl() {};
	~Impl() = default;
	std::map<ControllerButton, std::unique_ptr<Command>>& GetButtonCommands(int idx) { return m_ButtonCommands[idx]; }
	bool ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) {

			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {

			}
			ImGui_ImplSDL2_ProcessEvent(&e);
		}



		for (int i{}; i < NrOfPlayers; ++i)
		{
			CopyMemory(&m_PreviousState[i], &m_CurrentState[i], sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
			XInputGetState(i, &m_CurrentState[i]);

		}
		return true;
	};
	bool IsDown(ControllerButton button, int playerIdx) const
	{
		if (((m_PreviousState[playerIdx].Gamepad.wButtons & int(button)) == 0))
		{
			return((m_CurrentState[playerIdx].Gamepad.wButtons & int(button)) != 0);
		}
		return false;
	};
	bool IsReleased(ControllerButton button, int playerIdx) const
	{
		if (((m_PreviousState[playerIdx].Gamepad.wButtons & int(button)) != 0))
		{
			return((m_CurrentState[playerIdx].Gamepad.wButtons & int(button)) == 0);
		}
		return false;
	};
	bool IsPressed(ControllerButton button, int playerIdx) const
	{
		return((m_CurrentState[playerIdx].Gamepad.wButtons & int(button)) != 0);
	}


};
dae::InputManager::InputManager()
	:pImpl(new Impl())
{

}
dae::InputManager::~InputManager()
{
	delete pImpl;
	pImpl = nullptr;
}


bool dae::InputManager::ProcessInput()
{
	return pImpl->ProcessInput();
}

bool dae::InputManager::IsDown(ControllerButton button, int playerIdx) const
{

	return pImpl->IsDown(button, playerIdx);

}

bool dae::InputManager::IsReleased(ControllerButton button, int playerIdx) const
{
	return pImpl->IsReleased(button, playerIdx);
}
bool dae::InputManager::IsPressed(ControllerButton button, int playerIdx) const
{
	return pImpl->IsPressed(button, playerIdx);
}
void dae::InputManager::AddCommand(ControllerButton button, Command* commandButton, GameObject* gameObject, int playerIdx)
{
	pImpl->GetButtonCommands(playerIdx)[button].reset(commandButton);
	pImpl->GetButtonCommands(playerIdx)[button]->SetGameObject(gameObject);
}

void dae::InputManager::HandleCommand(ControllerButton button, KeyState keyState, int playerIdx)
{
	switch (keyState)
	{
	case KeyState::DOWN:
		if (IsDown(button, playerIdx))
		{
			pImpl->GetButtonCommands(playerIdx)[button]->Execute();
		}
		break;
	case KeyState::RELEASED:
		if (IsReleased(button, playerIdx))
		{
			pImpl->GetButtonCommands(playerIdx)[button]->Execute();
		}
		break;
	case KeyState::PRESSED:
		if (IsPressed(button, playerIdx))
		{

			pImpl->GetButtonCommands(playerIdx)[button]->Execute();
		}
		break;
	}
}