#include <Player.hpp>
#include <PlayerSprite.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/UtHEngine.hpp>


namespace
{
    const float ns_shootCool = 0.25f;
    const float ns_hitCool = 0.25f;
}


namespace ns
{

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


    bool Player::CheckCollision(const uth::Transform& object)
    {
        if (m_hitCooldown > 0.f ||
            m_sprite->m_sprites[PlayerSprite::Right]->transform.GetBounds().intersects(object.GetBounds()))
        {
            uth::WriteLog("Hit 1");
            return true;
        }

        if (transform.GetBounds().intersects(object.GetBounds()))
        {
            m_health -= 1;
            uth::WriteLog("Hit 2");
            return true;
        }
        uth::WriteLog("No hit");

        return false;
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

        const float speed = 300.f * dt;

        transform.Move((uthInput.Keyboard.IsKeyDown(uth::Keyboard::D) -
                        uthInput.Keyboard.IsKeyDown(uth::Keyboard::A)) * speed,
                       (uthInput.Keyboard.IsKeyDown(uth::Keyboard::S) -
                        uthInput.Keyboard.IsKeyDown(uth::Keyboard::W)) * speed);
    }
}