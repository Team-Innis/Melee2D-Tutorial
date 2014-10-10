#include <GameEnemyAffector.hpp>
#include <Player.hpp>
#include <UtH/Engine/Particles/Particle.hpp>
#include <UtH/Engine/Particles/ParticleTemplate.hpp>

namespace ns
{

    GameEnemyAffector::GameEnemyAffector()
        : m_player(nullptr)
    {

    }

    GameEnemyAffector::~GameEnemyAffector()
    {

    }

    void GameEnemyAffector::InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt)
    {
        particle.direction.x = 100.f;
    }

    void GameEnemyAffector::UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt)
    {
        if (m_player)
        {
            static const float speed = static_cast<float>(particle.direction.length());

            // Move the particle(enemy) towards the player.
            auto targetVec = (m_player->transform.GetPosition() - particle.GetPosition()).normalize();

            particle.Move(targetVec.x * speed * dt, targetVec.y * speed * dt);
            
            // When collision with a player happened, set the lifetime to a positive value so this particle will be cleaned up.
            if (m_player->CheckCollision(particle))
                particle.lifetime = 1.f;
        }
    }

    void GameEnemyAffector::SetPlayerPtr(Player* playerPtr)
    {
        m_player = playerPtr;
    }
}