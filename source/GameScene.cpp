#include <GameScene.hpp>
#include <UtH/UtHEngine.hpp>


GameScene::GameScene()
    : m_paused(true),
      // Initially we'll use the default camera view.
      m_camera(uthEngine.GetWindow().GetCamera())
{
    
}

GameScene::~GameScene()
{
    
}


bool GameScene::Init()
{
    // Create the player.
    m_player = uth::Layer::AddChild(new ns::Player()).get();
    
    // Initialize the enemies.
    // We don't want the batch to delete the object, so false must be passed to its constructor.
    m_enemyBatch = new uth::SpriteBatch(false);
    m_enemies.reserve(100); // Maximum amount of enemies.

    return true;
}

bool GameScene::DeInit()
{
    return true;
}

void GameScene::Update(float dt)
{
    if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Escape))
        m_paused = !m_paused;

    m_camera.SetPosition(m_player->transform.GetPosition());


    uth::Layer::Update(dt);
}

void GameScene::Draw(uth::RenderTarget& target, uth::RenderAttributes attributes)
{
    static auto& wndw = uthEngine.GetWindow();

    uth::Layer::Draw(target);
}