#include <UtH/Engine/Scene.hpp>



class GameScene : public uth::Scene
{
public:

    GameScene();

    ~GameScene();



    virtual bool Init();

    virtual bool DeInit();

    virtual bool Update(float dt);

    virtual bool Draw();

};