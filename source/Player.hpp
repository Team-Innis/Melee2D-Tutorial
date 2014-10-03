#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <UtH/Engine/GameObject.hpp>
#include <PlayerProjectile.hpp>


namespace ns
{
    class PlayerSprite;
    class PlayerProjectile;

    class Player final : public uth::GameObject
    {
    public:

        Player();

        ~Player() override;


        bool CheckCollision(const uth::Transform& object);


    private:

        void update(float dt) override;

        void draw(uth::RenderTarget& target) override;


        // Member data
        PlayerSprite* m_sprite;
        PlayerProjectile m_projectile;
        float m_hitCooldown;
        float m_shootCooldown;
        int m_health;
        unsigned int m_kills;
    };
}

#endif // PLAYER_HPP