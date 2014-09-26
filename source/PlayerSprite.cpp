#include <PlayerSprite.hpp>
#include <UtH/Engine/Sprite.hpp>


using namespace ns;

PlayerSprite::PlayerSprite()
    : m_leftDelta(0.f),
      m_rightDelta(0.f)
{

}

PlayerSprite::~PlayerSprite()
{

}


void PlayerSprite::Init()
{
    auto mainTex = uthRS.LoadTexture("body.png");
    auto leftTex = uthRS.LoadTexture("leftArm.png");
    auto rightTex = uthRS.LoadTexture("rightArm.png");

    if (!mainTex || !leftTex || !rightTex)
    {
        uth::WriteError("Failed to load one or more player textures!");
        return;
    }

    m_sprites[Body].AddComponent(new uth::Sprite(mainTex, "Body"));
    m_sprites[Left].AddComponent(new uth::Sprite(leftTex, "Left"));
    m_sprites[Right].AddComponent(new uth::Sprite(rightTex, "Right"));

    // TODO: set parent and positions
    //for (auto& i : m_sprites)
    //    i.parent = this->parent;

    m_initialLeftPos = m_sprites[Left].transform.GetPosition();
    m_initialRightRot = m_sprites[Right].transform.GetRotation();
}

void PlayerSprite::Update(float dt)
{
    m_leftDelta = std::min(1.f, m_leftDelta + dt);
    m_rightDelta = std::min(1.f, m_rightDelta + dt);

    static const float halfPi = static_cast<float>(pmath::pi);
    static const float extent = 50.f;
    static const float rot = 40.f;

    m_sprites[Left].transform.SetPosition(m_initialLeftPos.x,
                                          (halfPi + (m_leftDelta * halfPi)) * extent + m_initialLeftPos.y);
    m_sprites[Right].transform.SetRotation((halfPi + (m_rightDelta * halfPi)) * rot + m_initialRightRot);
}

void PlayerSprite::Draw(uth::RenderTarget& target)
{
    for (auto& i : m_sprites)
        i.Draw(target);
}

void ns::PlayerSprite::HitAnim()
{
    m_rightDelta = 0.f;
}

void ns::PlayerSprite::ShootAnim()
{
    m_leftDelta = 0.f;
}