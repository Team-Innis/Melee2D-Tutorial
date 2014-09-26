#pragma once
#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/TMX/Map.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <Player.hpp>


class GameScene final : public uth::Scene
{
public:

    GameScene();

    ~GameScene() override;



    bool Init() override;

    bool DeInit() override;

    bool Update(float dt) override;

    bool Draw() override;



private:

    uth::TMX::Map m_map;
    uth::Camera m_camera;
    bool m_paused;

    uth::GameObject* m_player;
    uth::SpriteBatch* m_enemyBatch;
    std::vector<uth::Transform> m_enemies;

};

#endif // GAMESCENE_HPP