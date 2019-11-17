//#pragma once
//#define GL_SILENCE_DEPRECATION
//
//#ifdef _WINDOWS
//#include <GL/glew.h>
//#endif
//
//#include <SDL.h>
//#include <SDL_opengl.h>
//#include "glm/mat4x4.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "ShaderProgram.h"
//
//#include "Map.h"
//
//enum EntityType { PLAYER, PLATFORM, ENEMY, AOE_DAMAGE };
////enum  lastCollisionEntityType { PLAYER, PLATFORM, ENEMY, BULLET, LETTER};
//enum AIState { IDLE, WALKING, RUNNING, SLOW_DOWN, AOE };
//enum AIType { PAPARAZZI, JOOMBA };
//
//
//class Entity {
//public:
//
//    EntityType entityType;
//    AIState aiState;
//    AIType aiType;
//
//    Entity* effects;
//    int effects_num;
//
//    bool isStatic;
//    bool isActive;
//    bool isInvincible;
//
//    glm::vec3 position;
//    glm::vec3 velocity;
//    glm::vec3 acceleration;
//
//    float width;
//    float height;
//
//    float speed;
//    float timer;
//
//    GLuint textureID;
//
//    int cols;
//    int rows;
//    int* walkRight;
//    int* walkLeft;
//    int* jumpUp;
//    int* currentAnim;
//    int animFrames;
//    int animIndex;
//    float animTime;
//
//    Entity();
//
//    bool CheckCollision(Entity other);
//
//    void CheckCollisionsX(Map* map);
//    void CheckCollisionsY(Map* map);
//
//    void CheckCollisionsX(Entity *objects, int objectCount);
//    void CheckCollisionsY(Entity *objects, int objectCount);
//
//    void DrawSpriteFromTextureAtlas(ShaderProgram* program, int index);
//
//    void Update(float deltaTime, Entity *objects, int objectCount, Map *map, Entity* enemies, int enemyCount);
//    void Render(ShaderProgram *program);
//
//    bool CheckPartialOnLedge(Map* map);
//
//    void Jump();
//    void AI(Entity player, Map* map);
//    void AIPaparazzi(Entity player, Map* map);
//    void AIJoomba(Entity player, Map* map);
//
//    bool collidedTop;
//    bool collidedBottom;
//    bool collidedLeft;
//    bool collidedRight;
//
//};

#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Map.h"

enum  EntityType { PLAYER, PLATFORM, ENEMY, AOE_DAMAGE, LIFE };
//enum  lastCollisionEntityType { PLAYER, PLATFORM, ENEMY, BULLET, LETTER};
enum AIState { IDLE, WALKING, RUNNING, SLOW_DOWN, AOE };
enum AIType { PAPARAZZI, JOOMBA };


class Entity {
public:
    
    EntityType entityType;
    EntityType lastCollisionType;
    AIState aiState;
    AIType aiType;
    
    Entity* effects;
    int effects_num;
    GLuint textureID;
    
    int cols;
    int rows;
    int* walkRight;
    int* walkLeft;
    int* jumpUp;
    int* currentAnim;
    int animFrames;
    int animIndex;
    float animTime;
    bool isStatic;
    bool isActive;
    bool isInvincible;
    
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    
    float width;
    float height;
    
    float speed;
    float timer;
    
    
    Entity();
    
    bool CheckCollision(Entity& other);
    
    void CheckCollisionsX(Map* map);
    void CheckCollisionsY(Map* map);
    
    bool CheckPartialOnLedge(Map* map);
    void CheckSlideOffLedge(Map* map);
    
    void CheckCollisionsX(Entity* objects, int objectCount);
    void CheckCollisionsY(Entity* objects, int objectCount);
    
    void Update(float deltaTime, Entity* objects, int objectCount, Map* map, Entity* enemies, int enemyCount);
    void Render(ShaderProgram* program);
    
    void Jump();
    void Moonwalk();
    //void AI(Entity player, Map* map, Entity* effects_sprites, int ef_s_size);
    void AI(Entity player, Map* map);
    void AIPaparazzi(Entity player, Map* map);
    void AIJoomba(Entity player, Map* map);
    
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, int index);
    
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
};

