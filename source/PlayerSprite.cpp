#include <PlayerSprite.hpp>
#include <UtH/Engine/Sprite.hpp>


using namespace ns;

PlayerSprite::PlayerSprite()
    : m_leftDelta(1.f),
      m_rightDelta(1.f)
{

}

PlayerSprite::~PlayerSprite()
{

}


void PlayerSprite::Init()
{
    // Load the textures.
    auto mainTex = uthRS.LoadTexture("body.png");
    auto leftTex = uthRS.LoadTexture("leftArm.png");
    auto rightTex = uthRS.LoadTexture("rightArm.png");

    // If any of the textures failed to load, emit an error and return.
    if (!mainTex || !leftTex || !rightTex)
    {
        uth::WriteError("Failed to load one or more player textures!");
        return;
    }

    // Create the body parts.
    for (auto& i : m_sprites)
    {
        i = new uth::GameObject();
        this->parent->AddChild(i);
    }

    // Add sprites for the body parts.
    m_sprites[Body]->AddComponent(new uth::Sprite(mainTex, "Body"));
    m_sprites[Left]->AddComponent(new uth::Sprite(leftTex, "Left"));
    m_sprites[Right]->AddComponent(new uth::Sprite(rightTex, "Right"));

    // Set their properties.
    m_sprites[Left]->transform.SetOrigin(uth::Origin::BottomCenter);
    m_sprites[Right]->transform.SetOrigin(uth::Origin::BottomCenter);
    m_sprites[Left]->transform.SetPosition(55.f, 15.f);
    m_sprites[Right]->transform.SetPosition(-45.f, 25.f);
    m_sprites[Right]->transform.SetRotation(40.f);
    m_initialLeftPos = m_sprites[Left]->transform.GetPosition();
    m_initialRightRot = m_sprites[Right]->transform.GetRotation();
}

void PlayerSprite::Update(float dt)
{
    // Animate the "hands".
    m_leftDelta = std::min(1.f, m_leftDelta + dt * 2.f);
    m_rightDelta = std::min(1.f, m_rightDelta + dt * 2.f);

    static const float halfPi = static_cast<float>(pmath::pi) / 2.f;
    static const float extent = 40.f;
    static const float rot = 70.f;

    m_sprites[Left]->transform.SetPosition(m_initialLeftPos.x,
                                         ((halfPi + (std::sinf(m_leftDelta * halfPi))) * extent) - m_initialLeftPos.y);
    m_sprites[Right]->transform.SetRotation(((halfPi + (std::sinf(m_rightDelta * halfPi))) * rot) + m_initialRightRot);
}

void ns::PlayerSprite::HitAnim()
{
    m_rightDelta = 0.f;
}

void ns::PlayerSprite::ShootAnim()
{
    m_leftDelta = 0.f;
}