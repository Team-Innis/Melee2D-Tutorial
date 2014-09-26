#include <Player.hpp>
#include <PlayerSprite.hpp>
#include <UtH/Platform/Input.hpp>


using namespace ns;

namespace
{
    const float ns_shootCool = 0.25f;
    const float ns_hitCool = 0.25f;
}

Player::Player()
    : uth::GameObject("Player"),
      m_sprite(nullptr),
      m_hitCooldown(0.25f),
      m_shootCooldown(0.25f)
{
    m_sprite = new PlayerSprite();
    AddComponent(m_sprite);
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
}