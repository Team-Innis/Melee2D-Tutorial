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
    m_menuLayer = AddChild(new uth::Object()).get();

    // Create the player.
    m_player = m_gameLayer->AddChild(new ns::Player()).get();
    
    #pragma region Enemies
    // Initialize the enemies. 
    m_enemySystem = new uth::ParticleSystem(200);
    auto aff = new ns::GameEnemyAffector();
    aff->SetPlayerPtr(static_cast<ns::Player*>(m_player));
    m_enemySystem->AddAffector(aff);

    uth::ParticleTemplate pt;
    pt.SetLifetime(999.f);
    pt.SetSpeed(100.f);

    auto tex = uthRS.LoadTexture("enemy.png");
    pt.SetTexture(tex);
    
    m_enemySystem->SetTemplate(pt);
    m_enemySystem->SetEmitProperties(false);

    m_gameLayer->AddChild(m_enemySystem);

    #pragma endregion Enemies

    return true;
}

bool GameScene::DeInit()
{
    return true;
}

void GameScene::Update(float dt)
{
    if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Escape))
    {
        m_gameLayer->SetActive(!m_gameLayer->IsActive());
        m_menuLayer->SetActive(!m_menuLayer->IsActive());
    }

    if ((m_enemyTimer += dt) >= 2.f)
    {
        auto& camPos = m_camera.GetPosition();
        auto camSize = m_camera.GetSize();

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

    m_camera.SetPosition(m_player->transform.GetPosition());
}

void GameScene::Draw(uth::RenderTarget& target, uth::RenderAttributes attributes)
{
    static auto& wndw = uthEngine.GetWindow();

    uth::Layer::Draw(target);
}