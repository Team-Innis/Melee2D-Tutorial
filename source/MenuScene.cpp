#include <MenuScene.hpp>
#include <MenuParticleAffector.hpp>
#include <UtH/UtHEngine.hpp>


MenuScene::MenuScene()
{
    
}

MenuScene::~MenuScene()
{
    
}


bool MenuScene::Init()
{
    // Set the randomizer seed, just in case it hasn't been set before.
    uth::Randomizer::SetSeed();

    #pragma region Camera
    // Create a short named reference to the window so we don't have to call
    // uthEngine.GetWindow() every time.
    auto& wndw = uthEngine.GetWindow();
    
    // Set a new camera for the window. When the camera gets deleted, it will
    // automatically be unbound from the target.
    wndw.SetCamera(&m_menuCamera);

    // We'll use a constant 16:9 resolution for the view. This will cause stretching if the window is ever
    // resized or uses a different aspect ratio, but it also ensures that objects will stay in the
    // same relative position, no matter the window resolution.
    m_menuCamera.SetSize(1280, 720);

    // Modify the camera so that the origin of the world is in the upper left corner of the screen.
    // By default the center of the camera is in the center of the screen.
    m_menuCamera.SetPosition(m_menuCamera.GetSize() / 2.f);
    #pragma endregion Camera

    #pragma region Buttons
    std::array<uth::Texture*, 2> buttonTextures =
    {
        uthRS.LoadTexture("startButton.png"),
        uthRS.LoadTexture("exitButton.png")
    };
    
    // Handle failed texture load.
    for (auto i : buttonTextures)
    {
        if (!i)
        {
            uth::WriteError("Failed to load texture!");
            return false;
        }
    }

    // Allocate the buttons.
    m_buttons[0] = new ns::Button(wndw, buttonTextures[0]);
    m_buttons[1] = new ns::Button(wndw, buttonTextures[1]);

    // Set the callbacks.
    m_buttons[0]->setCallback([]()
    {
        // In our case, id 1 is the game scene.
        uthSceneM.GoToScene(1);
    });
    m_buttons[1]->setCallback([]()
    {
        uthEngine.Exit();
    });
    
    for (size_t i = 0; i < m_buttons.size(); ++i)
    {
        auto b = m_buttons[i];
        
        // We'll set the origin of the buttons so it's in the upper left corner.
        // By default it's in the middle.
        b->transform.SetOrigin(uth::Origin::TopLeft);

        b->transform.SetPosition(100.f, 100.f + (i * 50.f) + (i * b->transform.GetSize().y));

        uth::Layer::AddChild(b);
    }
    #pragma endregion Buttons
    
    #pragma region Particles
    {
        auto texture = uthRS.LoadTexture("menuParticle.png");

        // Check that the texture was loaded successfully
        if (!texture)
            return false;

        // Create a new particle system and give it the properties it needs.
        auto ps = new uth::ParticleSystem(150);
        ps->transform.SetPosition(m_menuCamera.GetSize().x, -250.f);
        ps->SetEmitProperties(true, 0.05f, 0.1f, 1, 1);
        
        // Create a ParticleTemplate
        uth::ParticleTemplate pt;
        pt.SetLifetime(8.f);
        pt.SetTexture(texture);
        pt.SetSpeed(200.f, 300.f);

        // Set the particle system template.
        ps->SetTemplate(pt);

        // Add the custom affector.
        ps->AddAffector(new ns::MenuParticleAffector());

        // We can add the particle system onto a layer.
        uth::Layer::AddChild(ps);
    }
    #pragma endregion Particles

    return true;
}

bool MenuScene::DeInit()
{
    return true;
}

void MenuScene::Update(float dt)
{
    static const float pi = static_cast<float>(pmath::pi);

    /* Button floating animation */
    /**/ static float sine = 0.f;
    /**/ static const float initial0 = m_buttons[0]->transform.GetPosition().y,
                            initial1 = m_buttons[1]->transform.GetPosition().y;
    /**/ sine += dt * (pi / 2.f);
    /**/
    /**/ m_buttons[0]->transform.SetPosition(m_buttons[0]->transform.GetPosition().x, initial0 + 10.f * std::sinf(sine));
    /**/ m_buttons[1]->transform.SetPosition(m_buttons[1]->transform.GetPosition().x, initial1 + 10.f * std::sinf(sine + (pi / 2.f)));
    /******************/

    // Update all layers.
    uth::Layer::Update(dt);
}

// The RenderTarget passed into the Scene Draw function will always be the window.
void MenuScene::Draw(uth::RenderTarget& target, uth::RenderAttributes)
{
    // Draw all layers.
    uth::Layer::Draw(target);
}