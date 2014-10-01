#include <Player.hpp>
#include <PlayerSprite.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/UtHEngine.hpp>


using namespace ns;

namespace
{
    const float ns_shootCool = 0.25f;
    const float ns_hitCool = 0.25f;
}

Player::Player()
    : uth::GameObject("Player"),
      m_sprite(new PlayerSprite()),
      m_hitCooldown(0.25f),
      m_shootCooldown(0.25f)
{
    AddComponent(m_sprite);
    m_sprite->SetActive(true);
}

Player::~Player()
{
    
}


void Player::update(float dt)
{
    if ((m_shootCooldown -= dt) <= 0.f && uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
    {
        m_sprite->ShootAnim();
        m_shootCooldown = ns_shootCool;
    }
    if ((m_hitCooldown -= dt) <= 0.f && uthInput.Mouse.IsButtonPressed(uth::Mouse::RIGHT))
    {
        m_sprite->HitAnim();
        m_hitCooldown = ns_hitCool;
    }
    
    auto mousePos = uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position());
    auto targetVec = (mousePos - transform.GetPosition()).unitVector();
    static const pmath::Vec2 upVec(0.f, -1.f);

    const bool rightMouse = mousePos.x >= transform.GetPosition().x;
    transform.SetRotation((rightMouse ? 180.f : 0.f) + pmath::acos(upVec.dot(rightMouse ? targetVec : -targetVec)));
    
    const float speed = 50.f * dt;

    transform.Move((uthInput.Keyboard.IsKeyDown(uth::Keyboard::A) -
                    uthInput.Keyboard.IsKeyDown(uth::Keyboard::D)) * speed,
                   (uthInput.Keyboard.IsKeyDown(uth::Keyboard::W) -
                    uthInput.Keyboard.IsKeyDown(uth::Keyboard::S)) * speed);
}