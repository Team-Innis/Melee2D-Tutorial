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

    void Update(float dt) override;

    void Draw(uth::RenderTarget& target, uth::RenderAttributes attributes = uth::RenderAttributes()) override;



private:

    uth::TMX::Map m_map;
    uth::Camera& m_camera;
    uth::Camera m_menuCamera;
    bool m_paused;

    uth::GameObject* m_player;
    uth::SpriteBatch* m_enemyBatch;
    std::vector<uth::Transform> m_enemies;

};

#endif // GAMESCENE_HPP