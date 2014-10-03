#include <Player.hpp>
#include <PlayerSprite.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/UtHEngine.hpp>


namespace
{
    const float ns_shootCooldown = 0.5f;
    const float ns_hitCooldown = 0.25f;
}


namespace ns
{

    Player::Player()
        : uth::GameObject("Player"),
          m_sprite(new PlayerSprite()),
          m_projectiles(),
          m_hitCooldown(ns_hitCooldown),
          m_shootCooldown(ns_shootCooldown),
          m_health(5),
          m_kills(0)
    {
        AddComponent(m_sprite);
        m_sprite->SetActive(true);
    }

    Player::~Player()
    {

    }


    bool Player::CheckCollision(const uth::Transform& object)
    {
        if (m_hitCooldown > 0.f &&
            m_sprite->m_sprites[PlayerSprite::Right]->transform.GetTransformedBounds().contains(object.GetPosition()))
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

        m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), [](const std::unique_ptr<PlayerProjectile>& p)
        {
            return !p->IsActive();
        }), m_projectiles.end());

        for (auto& i : m_projectiles)
        {
            if (object.GetBounds().intersects(i->transform.GetBounds()))
            {
                i->SetActive(false);

                uth::WriteLog("Hit 3");
                return true;
            }
        }

        return false;
    }

    void Player::update(float dt)
    {
        if ((m_shootCooldown -= dt) <= 0.f && uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
        {
            m_sprite->ShootAnim();
            m_projectiles.emplace_back(new PlayerProjectile(transform.GetRotation(), 400.f));
            m_projectiles.back()->transform.SetPosition(transform.GetPosition());
            m_shootCooldown = ns_shootCooldown;
        }
        if ((m_hitCooldown -= dt) <= 0.f && uthInput.Mouse.IsButtonPressed(uth::Mouse::RIGHT))
        {
            m_sprite->HitAnim();
            m_hitCooldown = ns_hitCooldown;
        }

        auto mousePos = uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position());
        auto targetVec = (mousePos - transform.GetPosition()).unitVector();
        static const pmath::Vec2 upVec(0.f, -1.f);

        const bool cannotmathtodayihasthedumb = mousePos.x >= transform.GetPosition().x;
        transform.SetRotation((cannotmathtodayihasthedumb ? 180.f : 0.f) + pmath::acos(upVec.dot(cannotmathtodayihasthedumb ? targetVec : -targetVec)));

        const float speed = 300.f * dt;

        transform.Move((uthInput.Keyboard.IsKeyDown(uth::Keyboard::D) -
                        uthInput.Keyboard.IsKeyDown(uth::Keyboard::A)) * speed,
                       (uthInput.Keyboard.IsKeyDown(uth::Keyboard::S) -
                        uthInput.Keyboard.IsKeyDown(uth::Keyboard::W)) * speed);

        for (auto& i : m_projectiles)
            i->Update(dt);
    }

    void Player::draw(uth::RenderTarget& target)
    {
        for (auto& i : m_projectiles)
            i->Draw(target);
    }
}