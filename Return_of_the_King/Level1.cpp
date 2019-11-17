#include "Level1.h"
//#include "Util.h"
#define LEVEL1_WIDTH 25
#define LEVEL1_HEIGHT 8

#define ENEMIES_COUNT 2


unsigned int level1_data[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,0,0,0,0,0,0,0,0,0,0,0,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,0,0,1,1,1,1,1,1,1,1,1,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,0,0,2,2,2,2,2,2,2,2,2,
};

Entity level1_enemies[ENEMIES_COUNT];
//Entity AOE_dmg_sprites[JOOMBA_COUNT * 2];


void Level1::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.height = 1.0f;
    state.player.width = 0.5f;
    state.player.position = glm::vec3(6, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("jackson1.png");
    state.player.cols = 19;
    state.player.rows = 1;
    state.player.walkRight = new int[7]{ 1, 2, 3, 4, 5, 6, 7 };
    state.player.walkLeft = new int[7]{ 13, 14, 15, 16, 17, 18, 19 };
    state.player.jumpUp = new int[1]{ 10 };
    state.player.currentAnim = state.player.walkRight;
    state.player.animFrames = 6;
    state.nextLevel = -1;
    /*
    for (int i = 0; i < JOOMBA_COUNT * 2; ++i) {
        AOE_dmg_sprites[i].entityType = AOE_DAMAGE;
        AOE_dmg_sprites[i].textureID = Util::LoadTexture("me.png");
        AOE_dmg_sprites[i].isStatic = true;
        AOE_dmg_sprites[i].isActive = false;
        AOE_dmg_sprites[i].position = glm::vec3(0, 0, 0);
        AOE_dmg_sprites[i].timer = 2.0f;
    }
    */
    state.enemies = level1_enemies;
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = Util::LoadTexture("papa.png");
    state.enemies[0].acceleration = glm::vec3(0, -9.81, 0);
    state.enemies[0].isStatic = false;
    state.enemies[0].position = glm::vec3(1, -2.25, 0);
    state.enemies[0].aiState = WALKING;
    state.enemies[0].aiType = PAPARAZZI;
    //state.enemies[0].aiType = PAPARAZZI;
    state.enemies[0].velocity = glm::vec3(1.0f, 0, 0);
    state.enemies[0].timer = 100.0f + rand() % 200 + 1;
    //state.enemies[0].effects = AOE_dmg_sprites;
    //state.enemies[0].effects_num = JOOMBA_COUNT * 2;
    
    
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = Util::LoadTexture("papa.png");
    state.enemies[1].acceleration = glm::vec3(0, -9.81f, 0);
    state.enemies[1].isStatic = false;
    state.enemies[1].position = glm::vec3(2, -2.25, 0);
    state.enemies[1].aiState = WALKING;
    state.enemies[1].aiType = PAPARAZZI;
    state.enemies[1].velocity = glm::vec3(1.0f, 0.001f, 0);

}

void Level1::Update(float deltaTime, int& lives) {
    state.player.Update(deltaTime, state.enemies, ENEMIES_COUNT, state.map, state.enemies, ENEMIES_COUNT);
    for (int i = 0; i < ENEMIES_COUNT; ++i) {
        state.enemies[i].Update(deltaTime, &state.player, 1, state.map, state.enemies, ENEMIES_COUNT);
    }
    /*
    for (int i = 0; i < JOOMBA_COUNT * 2; ++i) {
        AOE_dmg_sprites[i].Update(deltaTime, &state.player, 1, state.map, state.enemies, ENEMIES_COUNT);
    }
     */
    
    if(state.player.position.y <= -10)
    {
        state.player.isActive = false;
    }
    if(state.player.isActive == false){
        if(lives > 1){
            state.player.position = glm::vec3(6, 0, 0);
            state.player.isActive = true;
            lives -= 1;
        }
        else{
            if(lives ==1)
            {
                lives -= 1;
            }
        }
        
        //state.nextLevel = 1;
    }

    if (state.player.position.x > 23) {
        state.nextLevel = 2;
    }
}
void Level1::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player.Render(program);
    
    for (int i = 0; i < ENEMIES_COUNT; ++i) {
        if (state.enemies[i].isActive) {
            state.enemies[i].Render(program);
        }
        
    }
    /*
    for (int i = 0; i < JOOMBA_COUNT * 2; ++i) {
        if (AOE_dmg_sprites[i].isActive == true) {
            AOE_dmg_sprites[i].Render(program);
        }
        
    }
     */
}
