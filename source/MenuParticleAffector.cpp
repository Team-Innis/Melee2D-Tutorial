#include <MenuParticleAffector.hpp>
#include <UtH/Engine/Particles/Particle.hpp>
#include <UtH/Engine/Particles/ParticleSystem.hpp>
#include <UtH/Core/Randomizer.hpp>


using namespace ns;

MenuParticleAffector::MenuParticleAffector()
    : m_sine(0.f)
{

}

MenuParticleAffector::~MenuParticleAffector()
{

}

void ns::MenuParticleAffector::InitParticle(uth::Particle& particle, const uth::ParticleTemplate& pt)
{
    // This lambda function initializes the particles in the way we want.
    // In this case the general direction of the vector is set to point somwehere in the lower left corner of the screen.

    particle.direction = pmath::Vec2(uth::Randomizer::GetFloat(-0.4f, -0.0f),
                              uth::Randomizer::GetFloat(0.3f, 0.6f));
    particle.direction.normalize();
    particle.direction *= uth::Randomizer::GetFloat(pt.minSpeed, pt.maxSpeed);

    // Set the desired scale.
    particle.SetScale(0.05f, 0.3f);
}

void MenuParticleAffector::Update(float dt)
{
    // Increase the sine.
    static const float pi = static_cast<float>(pmath::pi);
    m_sine += (dt * pi) / 1.8f;

    // If the offsets haven't been initialized, do it here.
    if (m_offsets.empty())
    {
        m_offsets.resize(GetSystem()->GetParticleLimit(), 0.f);
        for (auto& i : m_offsets)
            i = uth::Randomizer::GetFloat(0.f, pi);
    }
}

void MenuParticleAffector::UpdateParticle(uth::Particle& particle, const uth::ParticleTemplate& pt, float dt)
{
    // Rotate the particle according to it's direction.
    static const pmath::Vec2 upVec(0.f, -1.f);
    pmath::Vec2 normal = particle.direction;
    particle.SetRotation(pmath::radiansToDegrees(-std::acosf(upVec.dot(normal.normalize()))));

    // Rotate the direction vector by a random amount.
    const float sine = std::sinf(m_sine * m_offsets[GetSystem()->GetCurrentParticleNumber()]) / 140.f;
    const float rotCos = std::cos(sine);
    const float rotSin = std::sin(sine);

    particle.direction.x = rotCos * particle.direction.x - rotSin * particle.direction.y;
    particle.direction.y = rotSin * particle.direction.x + rotCos * particle.direction.y;

    // Add the particle's direction to its translation.
    particle.Move(particle.direction * dt);
}