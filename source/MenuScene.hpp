#pragma once
#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <Button.hpp>
#include <array>
#include <memory>


class MenuScene final : public uth::Scene
{
public:

    MenuScene();

    ~MenuScene() override;



    bool Init() override;

    bool DeInit() override;

    bool Update(float dt) override;

    bool Draw() override;



private:

    uth::Camera m_menuCamera;
    std::array<ns::Button*, 2> m_buttons;
    bool m_running;

};

#endif // MENUSCENE_HPP