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
        // Add a sprite component during construction.
        AddComponent(m_sprite);
        m_sprite->SetActive(true);
    }

    Player::~Player()
    {
        // nothing to do here.
    }


    bool Player::CheckCollision(const uth::Transform& object)
    {
        // The collision detection here is so inaccurate it pretty much doesn't work at all.
        // There will be a much better method in the future. Please do not take this as reference. 

        // Check collision with the right "hand".
        if (m_hitCooldown > 0.f &&
            m_sprite->m_sprites[PlayerSprite::Right]->transform.GetTransformedBounds().contains(object.GetPosition()))
        {
            return true;
        }

        // Check collision with the main body and decrease health if true.
        if (transform.GetBounds().intersects(object.GetBounds()))
        {
            m_health -= 1;
            return true;
        }

        // Erase inactive projectiles. Using this method involving remove_if is more efficient than erasing the elements individually.
        // More at https://en.wikipedia.org/wiki/Erase-remove_idiom
        m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), [](const std::unique_ptr<PlayerProjectile>& p)
        {
            return !p->IsActive();
        }), m_projectiles.end());

        // Update the projectiles.
        for (auto& i : m_projectiles)
        {
            // Check collision.
            if (object.GetBounds().intersects(i->transform.GetBounds()))
            {
                i->SetActive(false);
                return true;
            }
        }

        return false;
    }

    void Player::update(float dt)
    {
        // Check if there's no cooldown left and if the left mouse button was pressed.
        // Shoot projectile if both true. Also reset the cooldown.
        if ((m_shootCooldown -= dt) <= 0.f && uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
        {
            m_sprite->ShootAnim();
            m_projectiles.emplace_back(new PlayerProjectile(transform.GetRotation(), 400.f));
            m_projectiles.back()->transform.SetPosition(transform.GetPosition());
            m_shootCooldown = ns_shootCooldown;
        }

        // Same as above but for the right "hand".
        if ((m_hitCooldown -= dt) <= 0.f && uthInput.Mouse.IsButtonPressed(uth::Mouse::RIGHT))
        {
            m_sprite->HitAnim();
            m_hitCooldown = ns_hitCooldown;
        }

        // The following code will be improved at some point.

        // Apply rotation to player by checking its position against the mouse coordinates. 
        auto mousePos = uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position());
        auto targetVec = (mousePos - transform.GetPosition()).unitVector();
        static const pmath::Vec2 upVec(0.f, -1.f);

        const bool cannotmathtodayihasthedumb = mousePos.x >= transform.GetPosition().x;
        transform.SetRotation((cannotmathtodayihasthedumb ? 180.f : 0.f) + pmath::acos(upVec.dot(cannotmathtodayihasthedumb ? targetVec : -targetVec)));

        const float speed = 300.f * dt;

        // Translate the player according to the inputs. (Yes, booleans are perfectly functional with negation and multiplication.)
        transform.Move((uthInput.Keyboard.IsKeyDown(uth::Keyboard::D) -
                        uthInput.Keyboard.IsKeyDown(uth::Keyboard::A)) * speed,
                       (uthInput.Keyboard.IsKeyDown(uth::Keyboard::S) -
                        uthInput.Keyboard.IsKeyDown(uth::Keyboard::W)) * speed);

        // Update all the active projectiles.
        for (auto& i : m_projectiles)
            i->Update(dt);
    }

    void Player::draw(uth::RenderTarget& target)
    {
        // Draw the projectiles.
        for (auto& i : m_projectiles)
            i->Draw(target);
    }
}