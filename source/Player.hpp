#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <UtH/Engine/GameObject.hpp>


namespace ns
{
    class PlayerSprite;

    class Player final : public uth::GameObject
    {
    public:

        Player();

        ~Player() override;


        bool CheckCollision(const uth::Transform& object);


    private:

        void update(float dt) override;


        // Member data
        PlayerSprite* m_sprite;
        float m_hitCooldown;
        float m_shootCooldown;
        int m_health;
    };
}

#endif // PLAYER_HPP