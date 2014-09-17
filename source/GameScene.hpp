#pragma once
#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/TMX/Map.hpp>


class GameScene : public uth::Scene
{
public:

    GameScene();

    ~GameScene();



    bool Init() override;

    bool DeInit() override;

    bool Update(float dt) override;

    bool Draw() override;



private:

    uth::TMX::Map m_map;

};

#endif // GAMESCENE_HPP