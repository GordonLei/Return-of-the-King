#include "Scene.h"
class StartScreen : public Scene {
    
public:
    void Initialize() override;
    void Update(float deltaTime, int& lives) override;
    void Render(ShaderProgram* program) override;
};
