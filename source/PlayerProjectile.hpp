#pragma once
#ifndef PLAYERPROJECTILE_HPP
#define PLAYERPROJECTILE_HPP

#include <UtH/Engine/GameObject.hpp>


namespace ns
{
    class PlayerProjectile : public uth::GameObject
    {
    public:

        PlayerProjectile(const float direction, const float speed);


    private:

        void update(float dt) override;


        float m_timer;
        pmath::Vec2 m_direction;

    };
}

#endif