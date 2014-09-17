#include <Button.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Engine/Sprite.hpp>


using namespace ns;

Button::Button(const uth::RenderTarget& target, uth::Texture* texture)
    : GameObject(),
      m_target(target)
{
    // Create a new Sprite component with the loaded texture.
    this->AddComponent(new uth::Sprite(texture));
}

void Button::update(float)
{
    // First check if a click happened.
    if (uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
    {
        // Transform the mouse position into world coordinates.
        auto clickPos = m_target.pixelToCoords(uthInput.Mouse.Position());

        // Check if the mouse position is inside the bounds of this object and a click actually happened.
        // Also check callback validity (has it been set?).
        if (transform.GetBounds().contains(clickPos) && m_callback)
            m_callback();
    }
}

void Button::setCallback(std::function<void()> callback)
{
    m_callback = callback;
}