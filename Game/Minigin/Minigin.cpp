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
//#include <steam_api.h>
#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "RigidBodyComponent.h"
#include "LevelParser.h"
#include "MovementComponent.h"
#include "Sound.h"
#include "SDL_mixer.h"

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
	//m_SteamApi = SteamAPI_Init();
	//if (!m_SteamApi)
	//{
	//	std::cerr << "Fatal error - steam must be running to play this game (SteamAPI_Init() failed)\n";
	//}

	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO |SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	//AUDIO INITIALIZATION

	// Set up the audio stream
	int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	if (result < 0)
	{
		fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
		exit(-1);
	}

	result = Mix_AllocateChannels(4);
	if (result < 0)
	{
		fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
		exit(-1);
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

	m_pPhysics = new Physics();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level1");

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//FPS counter
	//auto fpsCounter = std::make_shared<FpsComponent>();
	//auto fpsText = std::make_shared<TextComponent>("Fps: ", font);

	//auto fpsCounterGo = std::make_shared<GameObject>();
	//fpsCounterGo->AddComponent(fpsCounter, "fpsCounter");
	//fpsCounterGo->AddComponent(fpsText, "text");
	//fpsCounter->SetGameObject(fpsCounterGo.get());
	//fpsText->SetGameObject(fpsCounterGo.get());
	//scene.Add(fpsCounterGo);
	//===========

	Transform peterPepperSpawnPos = ParseLevel(scene);
	CreatePeterPepperAndHUD(peterPepperSpawnPos, scene, 0);
	//CreatePeterPepperAndHUD(peterPepperSpawnPos, scene, 1);
}

void dae::Minigin::CreatePeterPepperAndHUD(Transform spawnPos, Scene& scene, int playerNr) const
{
	float hudX, hudY;
	hudX = 0;
	hudY = 420;
	if (playerNr == 1)
	{
		hudX = 400;
	}

	//Create gameobject and components
	auto peterPepperGo = std::make_shared<GameObject>();
	//Transform transform{};
	//transform.SetPosition(50.f, 50.f, 0.f);
	peterPepperGo->SetTransform(spawnPos);
	auto peterPepper = std::make_shared<PeterPepperComponent>(3, m_SteamApi);
	auto peterPSprite = std::make_shared<SpriteComponent>();

	float animationScale = 2.f;
	//Create animations 
	// 	//Down
	auto peterPAnimationDown = std::make_shared<Animation>(3, 3);
	peterPAnimationDown->SetTexture("PeterPepper/ClimbDownSprite.png");
	peterPAnimationDown->SetScale(animationScale);
	//Right
	auto peterPAnimationRight = std::make_shared<Animation>(3, 3);
	peterPAnimationRight->SetTexture("PeterPepper/LeftRightSprite.png");
	peterPAnimationRight->SetScale(animationScale);

	//Left
	auto peterPAnimationLeft = std::make_shared<Animation>(3, 3);
	peterPAnimationLeft->SetTexture("PeterPepper/LeftRightSprite.png");
	peterPAnimationLeft->SetScale(animationScale);
	//Up
	auto peterPAnimationUp = std::make_shared<Animation>(3, 3);
	peterPAnimationUp->SetTexture("PeterPepper/ClimbUpSprite.png");
	peterPAnimationUp->SetScale(animationScale);
	//Idle
	auto peterPAnimationIdle = std::make_shared<Animation>(1, 1);
	peterPAnimationIdle->SetTexture("PeterPepper/IdleSprite.png");
	peterPAnimationIdle->SetScale(animationScale);
	//Add animation to sprite
	peterPSprite->AddAnimation(peterPAnimationRight, "RunRight");
	peterPAnimationRight->SetReversed(true);
	peterPSprite->AddAnimation(peterPAnimationLeft, "RunLeft");
	peterPSprite->AddAnimation(peterPAnimationUp, "Climb");
	peterPSprite->AddAnimation(peterPAnimationDown, "Descend");
	peterPSprite->AddAnimation(peterPAnimationIdle, "Idle");


	peterPSprite->SetGameObject(peterPepperGo.get());
	peterPSprite->SetActiveAnimation("RunRight");

	//RigidbodyComponent
	auto pRigidBody = std::make_shared<RigidBodyComponent>(peterPSprite->GetAnimation().GetScaledWidth(),
		peterPSprite->GetAnimation().GetScaledHeight(),
		true);
	pRigidBody->SetGameObject(peterPepperGo.get());
	pRigidBody->SetTransform(&peterPepperGo->GetTransform());
	m_pPhysics->AddRigidBodyComponent(pRigidBody);

	//Movementcomponent
	//auto pMovement = std::make_shared<MovementComponent>();

	//Add everything to scene
	peterPepperGo->AddComponent(peterPSprite, "Sprite");
	peterPepperGo->AddComponent(peterPepper, "PeterPepper");
	peterPepperGo->AddComponent(pRigidBody, "RigidBody");
	//peterPepperGo->AddComponent(pMovement, "Movement");

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



	auto pointsDisplay = std::make_shared<GameObject>();
	auto pointComp = std::make_shared<PointsDisplayComponent>(pointsDisplay);
	auto textCompPts = std::make_shared<TextComponent>("Points: 0", smallFont);
	pointsDisplay->AddComponent(pointComp, "PointsComponent");
	pointsDisplay->AddComponent(textCompPts, "TextComponent");
	textCompPts->SetPosition(hudX, hudY + 20);
	scene.Add(pointsDisplay);

	//Observers
	peterPepper->AddObserver(lifeComp.get());
	peterPepper->AddObserver(peterPSprite.get());
	peterPepper->AddObserver(pointComp.get());

	auto& input = InputManager::GetInstance();
	input.AddCommand(ControllerButton::ButtonA, new Damage, KeyState::PRESSED, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::ButtonB, new GainPoints, KeyState::PRESSED, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadRight, new MoveRight, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadLeft, new MoveLeft, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadDown, new MoveDown, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadUp, new MoveUp, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::Nothing, new Idle, KeyState::NOTHING, peterPepperGo.get(), playerNr);

	//peterPepperGo->SetTransform(0, 400, 0);
}

dae::Transform dae::Minigin::ParseLevel(Scene& scene) const
{

	std::vector<Platform> platforms;
	std::vector<Ladder> ladders;
	std::vector<Float2> spawnPositions;
	ParseLevelFile("../Data/Level/Level1.txt", platforms, ladders, spawnPositions);

	//Every two platforms, the platfors get pushed 16 pixels further away because of the bug platform.
	//This scalingIncrease goes +16 every 2 platforms
	//And it gets reset when the rowNumber changes
	//Same goes for the ladders

	//int rowNumber = platforms[0].row;
	//int columnNumber = platforms[0].column;
	int levelScale = 2;
	//Is half 
	int scalingIncrease = 8 * levelScale;
	float platformWidth = 16.f * levelScale;

	for (int i{}; i < platforms.size(); ++i)
	{
		//if (rowNumber != platforms[i].row)
		//{
		//	rowNumber = platforms[i].row;
		//	scalingIncrease = 0;
		//}
		auto platform = std::make_shared<GameObject>();
		auto platformSprite = std::make_shared<SpriteComponent>();
		auto platformAnimation = std::make_shared<Animation>(1, 1);

		platformSprite->SetGameObject(platform.get());
		Transform transform;
		if (platforms[i].column % 2 == 0)
		{
			platformAnimation->SetTexture("Level/SmallPlatform.png");
			transform.SetPosition((platforms[i].column) * platformWidth + scalingIncrease * platforms[i].column, (platforms[i].row + 1) * platformWidth, 0.f);
		}
		else
		{
			platformAnimation->SetTexture("Level/BigPlatform.png");
			transform.SetPosition((platforms[i].column) * platformWidth + scalingIncrease * (platforms[i].column - 1), (platforms[i].row + 1) * platformWidth, 0.f);
		}
		platformSprite->AddAnimation(platformAnimation, "Platform");
		platformSprite->SetActiveAnimation("Platform");
		platformAnimation->SetScale((float)levelScale);

		platform->SetTransform(transform);

		//RigidbodyComponent
		auto pRigidBody = std::make_shared<RigidBodyComponent>(platformSprite->GetAnimation().GetScaledWidth(),
			platformSprite->GetAnimation().GetScaledHeight(),
			false);
		pRigidBody->SetGameObject(platform.get());

		platform->AddComponent(platformSprite, "Platform");
		platform->AddComponent(pRigidBody, "PlatformRigidBody");
		pRigidBody->SetTransform(&platform->GetTransform());

		m_pPhysics->AddRigidBodyComponent(pRigidBody);

		scene.Add(platform);
	}

	scalingIncrease;
	//Depending on the column, the ladder will have to be shifted forwards or backward in order to center it
	//In the files, this is a 2 pixel shift
	int ladderShift = 2 * levelScale;


	 //New ladder position calculation
	for (int i{}; i < ladders.size(); ++i)
	{
		auto ladder = std::make_shared<GameObject>();
		std::shared_ptr<SpriteComponent>ladderSprite = std::make_shared<SpriteComponent>();

		auto ladderAnimation = std::make_shared<Animation>(1, 1);
		ladderAnimation->SetTexture("Level/Ladder.png");
		ladderAnimation->SetScale((float)levelScale);

		ladderSprite->SetGameObject(ladder.get());

		ladderSprite->AddAnimation(ladderAnimation, "Ladder");
		ladderSprite->SetActiveAnimation("Ladder");

		Transform transform;
		//+4 because the ladders are otherwise off center
		transform.SetPosition(ladders[i].column * platformWidth + ((platformWidth * ladders[i].column / 2)) + ladderShift, (ladders[i].row + 1) * platformWidth, 0.f);
		ladder->SetTransform(transform);
		ladder->AddComponent(ladderSprite, "Ladder");

		//RigidbodyComponent
		auto pRigidBody = std::make_shared<RigidBodyComponent>(ladderSprite->GetAnimation().GetScaledWidth(),
			ladderSprite->GetAnimation().GetScaledHeight(),
			false);
		pRigidBody->SetGameObject(ladder.get());

		ladder->AddComponent(pRigidBody, "LadderRigidBody");
		pRigidBody->SetTransform(&ladder->GetTransform());

		m_pPhysics->AddRigidBodyComponent(pRigidBody);

		scene.Add(ladder);
	}


	//for now just one spawn position
	Transform transform;
	transform.SetPosition((platforms[0].column) * platformWidth + scalingIncrease * platforms[0].column, (platforms[0].row + 1) * platformWidth, 0.f);
	return transform;
}
void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	//SteamAPI_Shutdown();
	delete m_pPhysics;
	m_pPhysics = nullptr;
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
		bool doContinue = true;

		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		float fixedTimeStep = 0.02f;

		ServiceLocator::RegisterSoundSystem(new sound_system());

		ServiceLocator::GetSoundSystem().Play(0,100);
		//ss.Play(1, 100);
		//ss.Play(0, 100);
		while (doContinue)
		{
			//SteamAPI_RunCallbacks();

			const auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			input.Update();
			sceneManager.Update(deltaTime);

			while (lag >= fixedTimeStep)
			{
				sceneManager.FixedUpdate(fixedTimeStep);
				m_pPhysics->FixedUpdate(fixedTimeStep);
				lag -= fixedTimeStep;

			}
			renderer.Render();
		}
	}

	Cleanup();
}
