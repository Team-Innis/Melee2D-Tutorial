#include <GameScene.hpp>
#include <UtH/UtHEngine.hpp>


namespace
{
    enum Layers
    {
        Game = 1,
        Background = 0,
        Menu = 2
    };
}

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
    uthEngine.GetWindow().SetCamera(&m_camera);

    CreateLayer(Background);
    CreateLayer(Game);
    CreateLayer(Menu);

    // Create the player.
    m_player = AddGameObjectToLayer(Game, new ns::Player());

    // Initialize the enemies.
    m_enemyBatch = new uth::SpriteBatch(false);
    m_enemies.reserve(100); // Max amount of enemies.
    
    return true;
}

bool GameScene::DeInit()
{
    return true;
}

bool GameScene::Update(float dt)
{
    if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Escape))
        m_paused = !m_paused;

    m_camera.SetPosition(m_player->transform.GetPosition());

    if (!m_paused)
    {
        UpdateLayers(dt, Background);
        UpdateLayers(dt, Game);
    }
    else
    {
        uthEngine.GetWindow().SetCamera(nullptr);
        UpdateLayers(dt, Menu);
        uthEngine.GetWindow().SetCamera(&m_camera);
    }

    return true;
}

bool GameScene::Draw()
{
    static auto& wndw = uthEngine.GetWindow();

    DrawLayers(wndw, Background);
    DrawLayers(wndw, Game);

    if (m_paused)
    {
        uthEngine.GetWindow().SetCamera(nullptr);
        DrawLayers(wndw, Menu);
        uthEngine.GetWindow().SetCamera(&m_camera);
    }

    return true;
}