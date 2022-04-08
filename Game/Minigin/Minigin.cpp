#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include <chrono>
#include <ctime>
#include <ratio>
#include <steam_api.h>
#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "SpriteComponent.h"
#include "Animation.h"
using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	m_SteamApi = SteamAPI_Init();
	if (!m_SteamApi)
	{
		std::cerr << "Fatal error - steam must be running to play this game (SteamAPI_Init() failed)\n";
	}


	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto fpsCounter = std::make_shared<FpsComponent>();
	auto fpsText = std::make_shared<TextComponent>("Fps: ", font);

	auto fpsCounterGo = std::make_shared<GameObject>();
	fpsCounterGo->AddComponent(fpsCounter, "fpsCounter");
	fpsCounterGo->AddComponent(fpsText, "text");
	fpsCounter->SetGameObject(fpsCounterGo.get());
	fpsText->SetGameObject(fpsCounterGo.get());

	CreatePeterPepperAndHUD(0);
	//CreatePeterPepperAndHUD(1);

	scene.Add(fpsCounterGo);
}

void dae::Minigin::CreatePeterPepperAndHUD(int playerNr) const
{
	float hudX, hudY;
	hudX =0;
	hudY = 420;
	if (playerNr == 1)
	{
		hudX = 400;
	}
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto peterPepper = std::make_shared<PeterPepperComponent>(3, m_SteamApi);
	auto peterPSprite = std::make_shared<SpriteComponent>();

	auto peterPAnimation = std::make_shared<Animation>(3, 3,"leftRight");
	peterPAnimation->SetTexture("PeterPepper/LeftRightSprite.png");
	peterPAnimation->SetScale(2.f);
	auto peterPepperGo = std::make_shared<GameObject>();
	peterPSprite->SetAnimation(peterPAnimation);
	peterPepperGo->AddComponent(peterPSprite, "Sprite");
	peterPepperGo->AddComponent(peterPepper, "PeterPepper");
	peterPepper->SetGameObject(peterPepperGo.get());
	scene.Add(peterPepperGo);


	auto livesDisplay = std::make_shared<GameObject>();
	auto smallFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto lifeComp = std::make_shared<LivesDisplayComponent>(livesDisplay);
	auto textComp = std::make_shared<TextComponent>("Lives: 3", smallFont);
	livesDisplay->AddComponent(lifeComp, "LifeComponent");
	livesDisplay->AddComponent(textComp, "TextComponent");
	textComp->SetPosition(hudX, hudY);
	scene.Add(livesDisplay);
	peterPepper->AddObserver(lifeComp.get());

	auto pointsDisplay = std::make_shared<GameObject>();
	auto pointComp = std::make_shared<PointsDisplayComponent>(pointsDisplay);
	auto textCompPts = std::make_shared<TextComponent>("Points: 0", smallFont);
	pointsDisplay->AddComponent(pointComp, "PointsComponent");
	pointsDisplay->AddComponent(textCompPts, "TextComponent");
	textCompPts->SetPosition(hudX, hudY + 20);
	scene.Add(pointsDisplay);
	peterPepper->AddObserver(pointComp.get());
	
	auto& input = InputManager::GetInstance();
	input.AddCommand(ControllerButton::ButtonA, new Damage, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::ButtonB, new GainPoints, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadRight, new MoveRight, peterPepperGo.get(), playerNr);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SteamAPI_Shutdown();

	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		int nrOfPlayers = 2;
		//float fixedTimeStep = 0.02f;
		while (doContinue)
		{
			SteamAPI_RunCallbacks();

			const auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);

			//fpsCounter

			for (int i{}; i < nrOfPlayers; ++i)
			{
				input.HandleCommand(ControllerButton::ButtonA, KeyState::DOWN, i);
				input.HandleCommand(ControllerButton::ButtonB, KeyState::DOWN, i);
				input.HandleCommand(ControllerButton::DPadRight, KeyState::PRESSED, i);
			}


			//I will implement this once I actually need the fixedUpdate
			//while (lag >= fixedTimeStep)
			//{
			//	sceneManager.FixedUpdate(fixedTimeStep);
			//	lag -= fixedTimeStep;
			//}
			renderer.Render();
		}
	}

	Cleanup();
}
