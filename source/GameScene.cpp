#include <GameScene.hpp>
#include <GameEnemyAffector.hpp>
#include <UtH/UtHEngine.hpp>


GameScene::GameScene()
    // Initially we'll use the default camera view.
    : m_camera(uthEngine.GetWindow().GetCamera()),
      m_gameLayer(nullptr),
      m_menuLayer(nullptr),
      m_map(),
      m_menuCamera(),
      m_player(nullptr),
      m_enemySystem(nullptr),
      m_enemyTimer(0.f)
{
    
}

GameScene::~GameScene()
{
    
}


bool GameScene::Init()
{
    m_gameLayer = AddChild(new uth::Object()).get();
    m_gameLayer->SetActive(true);
    m_menuLayer = AddChild(new uth::Object()).get();
    m_menuLayer->SetActive(false);

    // Create the map.
    m_map = new uth::TMX::Map();
    m_gameLayer->AddChild(m_map);
    m_map->LoadFromFile("desert.tmx");
    m_map->transform.SetPosition(m_map->transform.GetSize() / 2.f);

    // Create the player.
    m_player = m_gameLayer->AddChild(new ns::Player()).get();
    
    #pragma region Enemies
    // Initialize the enemy particle system. 
    m_enemySystem = new uth::ParticleSystem(200);
    auto aff = new ns::GameEnemyAffector();

    // Set the pointer to the player using the function we created in the affector.
    aff->SetPlayerPtr(static_cast<ns::Player*>(m_player));

    // Add the affector into the system.
    m_enemySystem->AddAffector(aff);

    uth::ParticleTemplate pt;

    // Passing a negative value as the life time the particles will live indefinitely.
    pt.SetLifetime(-1.f);

    // Set a constant speed.
    pt.SetSpeed(100.f);

    auto tex = uthRS.LoadTexture("enemy.png");
    pt.SetTexture(tex);
    
    m_enemySystem->SetTemplate(pt);

    // Emitting will be done manually, so auto emit must be off.
    m_enemySystem->SetEmitProperties(false);

    m_gameLayer->AddChild(m_enemySystem);

    #pragma endregion Enemies
    
    return true;
}

bool GameScene::DeInit()
{
    // Objects added as children to this scene will be deleted automatically.

    return true;
}

void GameScene::Update(float dt)
{
    // If the pause key is pressed (Escape in this case) the active-flags of the
    // parent objects are toggled.
    if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Escape))
    {
        m_gameLayer->SetActive(false);
        m_menuLayer->SetActive(true);
    }

    // Emit an enemy every two seconds.
    if ((m_enemyTimer += dt) >= 2.f)
    {
        auto& camPos = m_camera.GetPosition();
        auto camSize = m_camera.GetSize();

        // Generate a random point outside of the camera view.
        switch (uth::Randomizer::GetInt(1, 4))
        {
            case 1: // Left
                m_enemySystem->transform.SetPosition(camPos.x - camSize.x / 2.f - 100.f, uth::Randomizer::GetFloat(camPos.y - camSize.y / 2.f, camPos.y + camSize.y / 2.f));
                break;
            case 2: // Right
                m_enemySystem->transform.SetPosition(camPos.x + camSize.y / 2.f + 100.f, uth::Randomizer::GetFloat(camPos.y - camSize.y / 2.f, camPos.y + camSize.y / 2.f));
                break;
            case 3: // Top
                m_enemySystem->transform.SetPosition(uth::Randomizer::GetFloat(camPos.x - camSize.x / 2.f, camPos.x + camSize.x / 2.f), camPos.y - camSize.y / 2.f - 100.f);
                break;
            default: // Bottom
                m_enemySystem->transform.SetPosition(uth::Randomizer::GetFloat(camPos.x - camSize.x / 2.f, camPos.x + camSize.x / 2.f), camPos.y + camSize.y / 2.f + 100.f);
        }

        m_enemySystem->Emit(1);
        m_enemyTimer -= 2.f;
    }

    uth::Layer::Update(dt);

    // The camera follows the player.
    m_camera.SetPosition(m_player->transform.GetPosition());
}