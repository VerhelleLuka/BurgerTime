#include "BurgerTime.h"
#include <vector>
#include "BurgerTimeStructs.h"
#include "LevelParser.h"
#include "PeterPepper.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "ResourceManager.h"
#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "PointsDisplayComponent.h"
#include "InputManager.h"
#include "PeterPepperCommand.h"
#include "Scene.h"
#include "PlatformComponent.h"
#include "LadderComponent.h"
#include "Renderer.h" 
#include "Sound.h"
#include "BurgerComponent.h"
#include "Enemy.h"
void dae::BurgerTime::Initialize()
{
}

void dae::BurgerTime::LoadGame() const
{
	auto& levelScene = SceneManager::GetInstance().CreateScene("Level");
	//auto& menuScene = SceneManager::GetInstance().CreateScene("MainMenu");

	//m_Minigin.GetPhysics()->AddScene();
	//m_Minigin.GetPhysics()->AddScene();
	Transform peterPepperSpawnPos = ParseLevel(levelScene, 0);
	CreatePeterPepperAndHUD(peterPepperSpawnPos, levelScene, 0, true, 0);
	CreateEnemy(levelScene, 0);
	//CreatePeterPepperAndHUD(peterPepperSpawnPos, menuScene, 0, false, 1);
	//CreateMenu(menuScene);
	SceneManager::GetInstance().SetActiveScene(&levelScene);
}
void dae::BurgerTime::CreateMenu(Scene& scene) const
{
	auto titleGo = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto textComp = std::make_shared<TextComponent>("BURGER TIME!!!!!!!", font);
	titleGo->AddComponent(textComp, "TextComp");
	titleGo->GetTransform().SetPosition(50, 0, 0);
	scene.Add(titleGo);

	auto buttonGo = std::make_shared<GameObject>();

	auto buttonAnim = std::make_shared<Animation>(1, 1);
	buttonAnim->SetTexture("Menu/Button.png");

	auto buttonTextComp = std::make_shared<TextComponent>("PLAY", font);
	buttonGo->AddComponent(buttonTextComp, "TextComp");
	buttonTextComp->SetGameObject(buttonGo.get());
	buttonTextComp->SetPosition(150, 100);

	auto buttonSprite = std::make_shared<SpriteComponent>();
	buttonSprite->SetGameObject(buttonGo.get());
	buttonSprite->AddAnimation(buttonAnim, "button");
	buttonSprite->SetActiveAnimation("button");
	buttonGo->AddComponent(buttonSprite, "ButtonSprite");

	auto buttonComp = std::make_shared<ButtonComponent>("Level");
	buttonGo->AddComponent(buttonComp, "ButtonComp");

	auto buttonRigidBody = std::make_shared<RigidBodyComponent>(buttonAnim->GetScaledWidth(), buttonAnim->GetScaledHeight(), false);
	buttonGo->AddComponent(buttonRigidBody, "ButtonRigidBody");
	buttonRigidBody->SetGameObject(buttonGo.get());
	buttonRigidBody->SetTransform(&buttonGo->GetTransform());
	auto sceneObjects = scene.GetSceneObjects();
	for (int i = 0; i < sceneObjects.size(); ++i)
	{
		if (dynamic_cast<GameObject*>(sceneObjects[i].get())->GetComponent<PeterPepperComponent>("PeterPepper").get())
		{
			dynamic_cast<GameObject*>(sceneObjects[i].get())->GetComponent<PeterPepperComponent>("PeterPepper")->AddObserver(buttonComp.get());
		}
	}
	buttonGo->SetTransform(150, 100, -1);
	m_Minigin.GetPhysics()->AddRigidBodyComponent(buttonRigidBody);
	scene.Add(buttonGo);
}

void dae::BurgerTime::CreateEnemy(Scene& scene, int sceneNr) const
{
	const float animationScale = 1.75f;
	auto enemyGo = std::make_shared<GameObject>();

	auto climbAnim = std::make_shared<Animation>(2, 2);
	climbAnim->SetTexture("Enemies/Sausage_Climb.png");
	climbAnim->SetScale(animationScale);

	auto descendAnim = std::make_shared<Animation>(2, 2);
	descendAnim->SetTexture("Enemies/Sausage_Descend.png");
	descendAnim->SetScale(animationScale);

	auto walkLeftAnim = std::make_shared<Animation>(2, 2);
	walkLeftAnim->SetTexture("Enemies/Sausage_Walk.png");
	walkLeftAnim->SetScale(animationScale);

	auto walkRightAnim = std::make_shared<Animation>(2, 2);
	walkRightAnim->SetTexture("Enemies/Sausage_Walk.png");
	walkRightAnim->SetScale(animationScale);
	walkRightAnim->SetReversed(true);

	auto enemySprite = std::make_shared<SpriteComponent>();
	enemySprite->SetGameObject(enemyGo.get());
	enemySprite->AddAnimation(climbAnim, "Climb");
	enemySprite->AddAnimation(descendAnim, "Descend");
	enemySprite->AddAnimation(walkRightAnim, "WalkRight");

	enemySprite->AddAnimation(walkLeftAnim, "WalkLeft");

	enemySprite->SetActiveAnimation("WalkLeft");
	enemyGo->AddComponent(enemySprite, "EnemySprite");

	//RigidbodyComponent
	auto pRigidBody = std::make_shared<RigidBodyComponent>(enemySprite->GetAnimation().GetScaledWidth(),
		enemySprite->GetAnimation().GetScaledHeight(),
		true);
	pRigidBody->SetGameObject(enemyGo.get());
	pRigidBody->SetTransform(&enemyGo->GetTransform());

	AddRigidBodyToPhysics(sceneNr, pRigidBody);

	enemyGo->AddComponent(pRigidBody, "RigidBody");

	//Enemy component
	auto enemy = std::make_shared<Enemy>();
	enemy->SetGameObject(enemyGo.get());
	enemy->Initialize();
	enemy->SetOverlapEvent();
	enemy->SetOnTriggerExitEvent();
	enemyGo->AddComponent(enemy, "Enemy");
	enemyGo->SetTransform(150, 70, 0);

	scene.Add(enemyGo);
}

void dae::BurgerTime::AddRigidBodyToPhysics(int sceneNr, std::shared_ptr<RigidBodyComponent> rB) const
{
	m_Minigin.GetPhysics()->SetSceneNr(sceneNr);
	m_Minigin.GetPhysics()->AddRigidBodyComponent(rB);
}
void dae::BurgerTime::CreatePeterPepperAndHUD(Transform spawnPos, Scene& scene, int playerNr, bool andHUD, int sceneNr) const
{
	float hudX, hudY;
	hudX = 0;
	hudY = 440;
	if (playerNr == 1)
	{
		hudX = 400;
	}

	//Create gameobject and components
	auto peterPepperGo = std::make_shared<GameObject>();
	//Transform transform{};
	//transform.SetPosition(50.f, 50.f, 0.f);
	peterPepperGo->SetTransform(spawnPos);
	auto peterPepper = std::make_shared<PeterPepperComponent>(3);
	auto peterPSprite = std::make_shared<SpriteComponent>();

	float animationScale = 1.75f;
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
	pRigidBody->SetOffset(Float2{ 0.f,-3.f });

	AddRigidBodyToPhysics(sceneNr, pRigidBody);
	//m_Minigin.GetPhysics()->AddRigidBodyComponent(pRigidBody);

	//Add everything to scene
	peterPepperGo->AddComponent(peterPSprite, "Sprite");

	peterPepperGo->AddComponent(peterPepper, "PeterPepper");

	peterPepperGo->AddComponent(pRigidBody, "RigidBody");
	//peterPepperGo->AddComponent(pMovement, "Movement");

	peterPepper->SetGameObject(peterPepperGo.get());
	peterPepper->SetOverlapEvent();
	peterPepper->SetOnTriggerExitEvent();

	scene.Add(peterPepperGo);

	if (andHUD)
	{

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

		peterPepper->AddObserver(lifeComp.get());
		peterPepper->AddObserver(pointComp.get());
	}

	peterPepper->AddObserver(peterPSprite.get());
	//MakeCommands(playerNr,peterPepperGo.get(), andHUD);
	auto& input = InputManager::GetInstance();

	input.AddCommand(ControllerButton::DPadRight, new MoveRight, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadLeft, new MoveLeft, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadDown, new MoveDown, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::DPadUp, new MoveUp, KeyState::DOWN, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::Nothing, new Idle, KeyState::NOTHING, peterPepperGo.get(), playerNr);
	input.AddCommand(ControllerButton::ButtonX, new ChangeScene, KeyState::PRESSED, peterPepperGo.get(), playerNr);

	if (!andHUD)
	{
		input.AddCommand((ControllerButton::ButtonA), new Select, KeyState::RELEASED, peterPepperGo.get(), playerNr);
	}
	else
	{
		peterPepper->SetInMenu(false);
	}
	//input.SetPlayer(peterPepperGo.get(), playerNr);
	peterPepperGo->SetTransform(100, 20, 0);
	if (!andHUD)
	{
		peterPepperGo->SetTransform(150, 20, 0);
	}
}

void dae::BurgerTime::MakeCommands(int playerNr, GameObject* go, bool andHUD) const
{
	auto& input = InputManager::GetInstance();

	input.AddCommand(ControllerButton::DPadRight, new MoveRight, KeyState::DOWN, go, playerNr);
	input.AddCommand(ControllerButton::DPadLeft, new MoveLeft, KeyState::DOWN, go, playerNr);
	input.AddCommand(ControllerButton::DPadDown, new MoveDown, KeyState::DOWN, go, playerNr);
	input.AddCommand(ControllerButton::DPadUp, new MoveUp, KeyState::DOWN, go, playerNr);
	input.AddCommand(ControllerButton::Nothing, new Idle, KeyState::NOTHING, go, playerNr);
	if (andHUD)
	{
		input.AddCommand((ControllerButton::ButtonA), new Select, KeyState::RELEASED, go, playerNr);
	}
}
dae::Transform dae::BurgerTime::ParseLevel(Scene& scene, int sceneNr) const
{

	std::vector<Platform> platforms;
	std::vector<Ladder> ladders;
	std::vector<Float2> spawnPositions;
	std::vector<Burger> burgers;
	ParseLevelFile("../Data/Level/Level1.txt", platforms, ladders, spawnPositions, burgers);

	int levelScale = 2;
	//Is half 
	int scalingIncrease = 8 * levelScale;
	float platformWidth = 16.f * levelScale;
	MakeLaddersAndPlatforms(scene, ladders, platforms, sceneNr);
	MakeBurgers(scene, burgers, sceneNr);
	//for now just one spawn position
	Transform transform{};
	transform.SetPosition((platforms[0].column) * platformWidth + scalingIncrease * platforms[0].column, ((platforms[0].row + 1) * platformWidth), 0.f);
	return transform;
}

void dae::BurgerTime::MakeLaddersAndPlatforms(Scene& scene, const std::vector<Ladder>& ladders, const std::vector<Platform>& platforms, int sceneNr) const
{

	//Every two platforms, the platfors get pushed 16 pixels further away because of the bug platform.
	//This scalingIncrease goes +16 every 2 platforms
	//And it gets reset when the rowNumber changes
	//Same goes for the ladders

	int levelScale = 2;
	//Is half 
	int scalingIncrease = 8 * levelScale;
	float platformWidth = 16.f * levelScale;

	for (size_t i{}; i < platforms.size(); ++i)
	{

		auto platform = std::make_shared<GameObject>();
		auto platformSprite = std::make_shared<SpriteComponent>();
		auto platformAnimation = std::make_shared<Animation>(1, 1);

		platformSprite->SetGameObject(platform.get());
		Transform transform{};
		if (platforms[i].column % 2 == 0)
		{
			platformAnimation->SetTexture("Level/SmallPlatform.png");
			transform.SetPosition((platforms[i].column) * platformWidth + scalingIncrease * platforms[i].column, (platforms[i].row + 1) * platformWidth , 0.f);
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

		//Platform component
		auto pPlatform = std::make_shared<PlatformComponent>();
		//If this platform has one in the column left to it, set it's previous platform to true
		if (platforms[i].column != 0 && platforms.size() > 1 && i != 0)
		{
			//If the row is the same
			if (platforms[i - 1].row == platforms[i].row && platforms[i - 1].column == platforms[i].column - 1)
			{
				pPlatform->SetHasPrevious(true);
			}
		}
		//Kind of redundant since it gets initialized to false anyway, but whatever
		else
		{
			pPlatform->SetHasPrevious(false);
		}
		//Same for the right and next platform
		if (platforms[i].column != 11 && i != platforms.size() - 1)
		{
			if (platforms[i].row == platforms[i + 1].row && platforms[i].column + 1 == platforms[i + 1].column)
			{
				pPlatform->SetHasNext(true);
			}
		}
		else
		{
			pPlatform->SetHasNext(false);
		}
		platform->AddComponent(pPlatform, "PlatformComp");
		platform->AddComponent(platformSprite, "PlatformSprite");
		platform->AddComponent(pRigidBody, "PlatformRigidBody");
		pRigidBody->SetTransform(&platform->GetTransform());

		AddRigidBodyToPhysics(sceneNr, pRigidBody);
		//m_Minigin.GetPhysics()->AddRigidBodyComponent(pRigidBody);

		scene.Add(platform);
	}
	//std::cout << nextPlatforms << "\n";
	//Depending on the column, the ladder will have to be shifted forwards or backward in order to center it
	//In the files, this is a 2 pixel shift
	int ladderShift = 2 * levelScale;


	//New ladder position calculation
	for (size_t i{}; i < ladders.size(); ++i)
	{
		auto ladder = std::make_shared<GameObject>();
		std::shared_ptr<SpriteComponent>ladderSprite = std::make_shared<SpriteComponent>();

		auto ladderAnimation = std::make_shared<Animation>(1, 1);
		ladderAnimation->SetTexture("Level/Ladder.png");
		ladderAnimation->SetScale((float)levelScale);

		ladderSprite->SetGameObject(ladder.get());

		ladderSprite->AddAnimation(ladderAnimation, "Ladder");
		ladderSprite->SetActiveAnimation("Ladder");

		Transform transform{};
		//+4 because the ladders are otherwise off center
		transform.SetPosition(ladders[i].column * platformWidth + ((platformWidth * ladders[i].column / 2)) + ladderShift, (ladders[i].row + 1) * platformWidth , 0.f);
		ladder->SetTransform(transform);
		ladder->AddComponent(ladderSprite, "Ladder");

		//RigidbodyComponent
		auto pRigidBody = std::make_shared<RigidBodyComponent>(ladderSprite->GetAnimation().GetScaledWidth(),
			ladderSprite->GetAnimation().GetScaledHeight(),
			false);
		pRigidBody->SetGameObject(ladder.get());

		ladder->AddComponent(pRigidBody, "LadderRigidBody");
		pRigidBody->SetTransform(&ladder->GetTransform());

		AddRigidBodyToPhysics(sceneNr, pRigidBody);
		//m_Minigin.GetPhysics()->AddRigidBodyComponent(pRigidBody);

		//ladder component
		auto pLadder = std::make_shared<LadderComponent>();

		for (int k{}; k < ladders.size(); ++k)
		{
			for (int j{}; j < ladders.size(); ++j)
			{
				//If they're not the same ladder
				if (&ladders[j] != &ladders[k])
				{
					//Check for ladders higher
					if (i != 0)
					{
						if (ladders[i].column == ladders[j].column)
						{
							if (ladders[i].row - 1 == ladders[j].row)
							{
								pLadder->SetHasUp(true);
							}
						}
					}
					if (j != 0)
					{
						if (ladders[j].column == ladders[i].column)
						{
							if (ladders[j].row + 1 == ladders[i].row)
							{
								pLadder->SetHasUp(true);
							}
						}
					}
				}
			}
		}
		ladder->AddComponent(pLadder, "LadderComp");
		//std::cout << "Does ladder have up: " << pLadder->GetHasUp() << ". Does ladder have down: " << pLadder->GetHasDown() << "\n";
		scene.Add(ladder);
	}
}

void dae::BurgerTime::MakeBurgers(Scene& scene, const std::vector<Burger>& burgers, int sceneNr) const
{
	int levelScale = 2;
	//Is half 
	int scalingIncrease = 8 * levelScale;
	float platformWidth = 16.f * levelScale;
	//int nextPlatforms = 0;
	for (size_t i{}; i < burgers.size(); ++i)
	{
		if (burgers[i].partName != "")
		{
			auto burger = std::make_shared<GameObject>();
			auto burgerSprite = std::make_shared<SpriteComponent>();
			auto burgerAnimation = std::make_shared<Animation>(1, 1);

			burgerSprite->SetGameObject(burger.get());
			Transform transform{};

			std::string burgerPart = "Hamburger/";
			burgerPart.append(burgers[i].partName);
			burgerPart += ".png";

			burgerAnimation->SetTexture(burgerPart);
			transform.SetPosition((burgers[i].column) * platformWidth + scalingIncrease * (burgers[i].column - 1) + 1, ((burgers[i].row + 1) * platformWidth ) - 7 * levelScale, 0.f);
			//transform.SetPosition(burgers[i].column * platformWidth + (((platformWidth/2) * burgers[i].column / 2)), ((burgers[i].row + 1) * platformWidth * 1.5f) - 7 * levelScale, 0.f);

			burgerSprite->AddAnimation(burgerAnimation, "Burger");
			burgerSprite->SetActiveAnimation("Burger");
			burgerAnimation->SetScale((float)levelScale);



			burger->SetTransform(transform);

			//RigidbodyComponent
			auto pRigidBody = std::make_shared<RigidBodyComponent>(burgerSprite->GetAnimation().GetScaledWidth(),
				burgerSprite->GetAnimation().GetScaledHeight(),
				true);
			pRigidBody->SetGameObject(burger.get());
			//Burger component
			auto pBurger = std::make_shared<BurgerComponent>();

			burger->AddComponent(burgerSprite, "BurgerSprite");
			burger->AddComponent(pRigidBody, "RigidBody");
			burger->AddComponent(pBurger, "BurgerComp");
			pRigidBody->SetTransform(&burger->GetTransform());
			pBurger->SetGameObject(burger.get());
			pBurger->Initialize();
			pBurger->SetOverlapEvent();

			AddRigidBodyToPhysics(sceneNr, pRigidBody);
			//m_Minigin.GetPhysics()->AddRigidBodyComponent(pRigidBody);

			scene.Add(burger);
		}
	}
}
void dae::BurgerTime::Run()
{

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	m_Minigin.Initialize();
	Initialize();
	LoadGame();

	{
		m_Minigin.Run();
	}
	Cleanup();
}

void dae::BurgerTime::Cleanup()
{
}