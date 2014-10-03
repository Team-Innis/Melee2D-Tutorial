#include <PlayerProjectile.hpp>
#include <UtH/Engine/Sprite.hpp>


namespace ns
{

    PlayerProjectile::PlayerProjectile(const float direction, const float speed)
        : uth::GameObject(),
          m_timer(0.f),
          m_direction()
    {
        auto tex = uthRS.LoadTexture("enemy.png");

        AddComponent(new uth::Sprite(tex));

        SetActive(true);

        const float sine = pmath::sin(direction);
        m_direction.x = sine * 1.f;
        m_direction.y = sine * m_direction.x + pmath::cos(direction) * 1.f;

        m_direction.normalize();
        m_direction.x *= speed;
        m_direction.y *= speed;
    }


    void PlayerProjectile::update(float dt)
    {
        transform.Move(m_direction * dt);

        if ((m_timer += dt) >= 1.5f)
            SetActive(false);
    }
}