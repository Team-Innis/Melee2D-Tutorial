#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <UtH/Engine/GameObject.hpp>
#include <functional> // Needed for std::function

namespace uth
{
    // RenderTarget forward declaration. If we only use pointers and/or references to a class in a header,
    // we won't need the full definition (No need to include the file). 
    class RenderTarget;
    class Texture;
}

namespace ns
{
    class Button : public uth::GameObject
    {
    public:

        // Button requires knowledge of the render target this button is used with to transform
        // mouse coordinates to world coordinates.
        Button(const uth::RenderTarget& target, uth::Texture* texture);

        void update(float dt) override;

        void setCallback(std::function<void()> callback);

    private:

        const uth::RenderTarget& m_target;
        std::function<void()> m_callback;

    };
}

#endif // BUTTON_HPP