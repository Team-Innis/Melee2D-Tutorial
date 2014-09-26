#pragma once
#ifndef PLAYERSPRITE_HPP
#define PLAYERSPRITE_HPP

#include <UtH/Engine/Component.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <array>
#include <memory>

namespace ns
{
    class PlayerSprite final : public uth::Component
    {

        enum BodyPart
        {
            Body,
            Left,
            Right
        };

    public:

        PlayerSprite();

        ~PlayerSprite() override;



        void Init() override;

        void Update(float dt) override;

        void Draw(uth::RenderTarget& target) override;


        void HitAnim();

        void ShootAnim();
        

    private:

        // Member data
        std::array<uth::GameObject, 3> m_sprites;
        float m_leftDelta,
              m_rightDelta;

        pmath::Vec2 m_initialLeftPos;
        float m_initialRightRot;

    };
}

#endif // PLAYERSPRITE_HPP