#pragma once
#ifndef MENU_PARTICLE_AFFECTOR_HPP
#define MENU_PARTICLE_AFFECTOR_HPP

#include <UtH/Engine/Particles/Affector.hpp>
#include <vector>

namespace ns
{
    class MenuParticleAffector : public uth::Affector
    {
    public:

        MenuParticleAffector();

        ~MenuParticleAffector() override;


        void InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt) override;

        void Update(float dt) override;

        void UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt) override;

    private:

        float m_sine;
        std::vector<float> m_offsets;

    };
}

#endif // MENU_PARTICLE_AFFECTOR_HPP