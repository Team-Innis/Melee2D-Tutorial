#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/DefaultScene.hpp> //Default Scene. (Empty)

#include <MenuScene.hpp> //Your scene header.
#include <GameScene.hpp>

//Names and IDs for all scenes
enum SceneName
{
    DEFAULT = UTHDefaultScene,
    MENU = 0,
    GAME = 1,
    COUNT // Keep this last, it tells how many scenes there are
};

// Create function for a new scene, having a case for every user made scene
// Makes sure uthSceneM.GoToScene() pickes right scene with ID
uth::Scene* NewSceneFunc(int SceneID)
{
    switch (SceneID)
    {
        case MENU:
            return new MenuScene();
        case GAME:
            return new GameScene();
        default:
            return new uth::DefaultScene();
    }
}

// Basic computer main loop.
// Android version is hidden at UtHEngine/android/jni/main.cpp
int main()
{
    uthSceneM.registerNewSceneFunc(NewSceneFunc, COUNT);

    uthEngine.Init();

    while (uthEngine.Running())
    {
        uthEngine.Update();

        uthEngine.Draw();
    }

    return 0;
}