#include "StartScreen.h"
#define START_WIDTH 14
#define START_HEIGHT 8

#define ENEMIES_COUNT 0

unsigned int StartScreen_data[] =
{
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

void StartScreen::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(START_WIDTH, START_HEIGHT, StartScreen_data, mapTextureID, 1.0f, 4, 1);
    /*state.player.entityType = PLAYER;
     state.player.isStatic = false;
     state.player.isActive = false;
     state.player.width = 1.0f;
     state.player.position = glm::vec3(5, 0, 0);
     state.player.acceleration = glm::vec3(0, -9.81f, 0);
     state.player.textureID = Util::LoadTexture("jackson1.png");
     state.player.cols = 19;
     state.player.rows = 1;
     state.player.walkRight = new int[7]{ 1, 2, 3, 4, 5, 6, 7 };
     state.player.walkLeft = new int[7]{ 13, 14, 15, 16, 17, 18, 19 };
     state.player.jumpUp = new int[1]{ 10 };
     state.player.currentAnim = state.player.walkRight;
     state.player.animFrames = 6;*/
    state.nextLevel = -1;
}
void StartScreen::Update(float deltaTime, int& lives) {
    /*state.player.Update(deltaTime, NULL, 0, state.map, state.enemies, ENEMIES_COUNT);
     if (state.player.velocity.y > 0)
     {
     state.nextLevel = 1;
     }*/
}
void StartScreen::Render(ShaderProgram* program) {
    state.map->Render(program);
    //state.player.Render(program);
}
