#pragma once
#ifndef GAME_ENEMY_AFFECTOR_HPP
#define GAME_ENEMY_AFFECTOR_HPP

#include <UtH/Engine/Particles/Affector.hpp>


namespace ns
{
    class Player;

    class GameEnemyAffector final : public uth::Affector
    {
    public:

        GameEnemyAffector();

        ~GameEnemyAffector() override;


        void InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt) override;

        void UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt) override;

        void SetPlayerPtr(Player* playerPtr);

    private:

        Player* m_player;

    };
}

#endif // GAME_ENEMY_AFFECTOR_HPP