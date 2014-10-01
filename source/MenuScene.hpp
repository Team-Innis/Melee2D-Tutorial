#pragma once
#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Renderer/RenderAttributes.hpp>
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

    void Update(float dt) override;

    void Draw(uth::RenderTarget& target, uth::RenderAttributes attributes = uth::RenderAttributes()) override;



private:

    uth::Camera m_menuCamera;
    std::array<ns::Button*, 2> m_buttons;

};

#endif // MENUSCENE_HPP