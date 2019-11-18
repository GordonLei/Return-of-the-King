#include "Entity.h"

Entity::Entity()
{
    entityType = PLATFORM;
    isStatic = true;
    isActive = true;
    position = glm::vec3(0);
    speed = 0;
    width = 1;
    height = 1;
}

bool Entity::CheckCollision(Entity& other)
{
    if (isStatic == true) return false;
    if (isActive == false || other.isActive == false) return false;
    
    float xdist = fabs(position.x - other.position.x) - ((width + other.width) / 2.0f);
    float ydist = fabs(position.y - other.position.y) - ((height + other.height) / 2.0f);
    
    if (xdist < 0 && ydist < 0)
    {
        
        return true;
    }
    
    return false;
}

void Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity& object = objects[i];
        
        if (CheckCollision(object))
        {
            float ydist = fabs(position.y - object.position.y);
            float penetrationY = fabs(ydist - (height / 2) - (object.height / 2));
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;
                collidedTop = true;
                
                if (entityType == PLAYER && object.entityType == ENEMY)
                {
                    //std :: cout << "No" << std::endl;
                    isActive = false;
                }
                if (entityType == ENEMY && object.entityType == PLAYER)
                {
                    //std :: cout << "YES" << std::endl;
                    isActive = false;
                }
            }
            else if (velocity.y < 0) {
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;
                
                if (entityType == PLAYER && object.entityType == ENEMY)
                {
                    //std :: cout << "YES" << std::endl;
                    object.isActive = false;
                }
            }
        }
        /*
        std :: cout << collidedBottom << std :: endl;
        if(entityType == PLAYER && object.entityType == ENEMY && collidedBottom){
            std :: cout << "collidedBottom" << std :: endl;
            object.isActive = false;
        }
         */
    }
}

void Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity& object = objects[i];
        
        if (CheckCollision(object))
        {
            float xdist = fabs(position.x - object.position.x);
            float penetrationX = fabs(xdist - (width / 2) - (object.width / 2));
            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;
                
                if (entityType == PLAYER && object.entityType == ENEMY)
                {
                    //std :: cout << "No" << std::endl;
                    isActive = false;
                }
            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
                
                if (entityType == PLAYER && object.entityType == ENEMY)
                {
                    //std :: cout << "No" << std::endl;
                    isActive = false;
                }
            }
        }
    }
}

void Entity::CheckCollisionsX(Map* map)
{
    // Probes for tiles
    glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
    glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);
    
    float penetration_x = 0;
    float penetration_y = 0;
    if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        
        if(entityType == ENEMY){
            if (aiType == PAPARAZZI && aiState == RUNNING){
                Jump();
            }
            else{
                velocity *= -1;
            }
            
        }
        else{
            velocity.x = 0;
        }
        
        //velocity.x = 0;
        collidedLeft = true;
    }
    
    if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        
        if(entityType == ENEMY){
            if (aiType == PAPARAZZI && aiState == RUNNING){
                Jump();
            }
            else{
                velocity *= -1;
            }
            
        }
        else{
            velocity.x = 0;
        }
        
        //velocity.x = 0;
        collidedRight = true;
    }
}

void Entity::CheckCollisionsY(Map* map)
{
    // Probes for tiles
    glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);
    
    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
    
    float penetration_x = 0;
    float penetration_y = 0;
    if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    
    if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
}

bool Entity::CheckPartialOnLedge(Map* map)
{
    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    
    if ((map->IsSolid(bottom, &penetration_x, &penetration_y)) && !(map->IsSolid(bottom_right, &penetration_x, &penetration_y))) {
        position.y += penetration_y;
        //velocity.y = 0;
        
        return true;
    }
    if ((map->IsSolid(bottom, &penetration_x, &penetration_y)) && !(map->IsSolid(bottom_left, &penetration_x, &penetration_y))) {
        position.y += penetration_y;
        //velocity.y = 0;
        
        return true;
    }

    return false;
}

void Entity :: CheckSlideOffLedge(Map* map){
    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    if ((map->IsSolid(bottom, &penetration_x, &penetration_y))&& !(map->IsSolid(bottom_right, &penetration_x, &penetration_y)) && velocity.x < 0){
        position.y += penetration_y;
        //velocity.y = 0;
    }
    else if ((map->IsSolid(bottom, &penetration_x, &penetration_y))&& !(map->IsSolid(bottom_left, &penetration_x, &penetration_y)) && velocity.x > 0){
        position.y += penetration_y;
        //velocity.y = 0;
        
    }
    else{
        velocity.x *= -1;
    }
}

void Entity::Jump()
{
    if (collidedBottom)
    {
        velocity.y = 7.0f;
        /*if (collidedBottom)
         {
         acceleration.x = 5.2f;
         }*/
    }
}

//IDLE, WALKING, RUNNING, SLOW_DOWN

void Entity::AIPaparazzi(Entity player, Map* map) {
    switch (aiState) {
        case IDLE:
            velocity = glm::vec3(0, 0, 0);
            break;
        case WALKING:
            if(CheckPartialOnLedge(map)){
                CheckSlideOffLedge(map);
                //velocity.x = 0;
            }
            if (glm::distance(position, player.position) < 4.5f){
                aiState = RUNNING;
                velocity.x = 3.5;
                timer = 50.0f;
            }
            break;
            
        case RUNNING:
            //std::cout << "RUNNING" << std::endl;
            if (CheckPartialOnLedge(map)) {
                Jump();
            }
            timer -= 1.0f;
            if (player.position.x > position.x){
                velocity.x = 3.5f;
            }
            else{
                velocity.x = -3.5f;
            }
            if (timer <= 0.0f) {
                timer = 75.0f;
                aiState = SLOW_DOWN;
                velocity.x = 1.25f;
            }
            break;
            //if in their slow down state they are too far off, they will go back to walking
        case SLOW_DOWN:
            //std::cout << "SLOW DOWN" << std::endl;
            timer -= 1.0f;
            /*
            if (glm::distance(position, player.position) < 5.0f) {
                aiState = WALKING;
            }
             */
            if (player.position.x > position.x){
                velocity.x = 1.5f;
            }
            else{
                velocity.x = -1.5f;
            }
            if (timer <= 0.0f) {
                timer = 50.0f;
                aiState = RUNNING;
                velocity.x = 3.5f;
            }
            if (CheckPartialOnLedge(map)) {
                Jump();
            }
        case AOE:
            break;
    }
}
void Entity::AIJoomba(Entity player, Map* map) {
    switch (aiState) {
        case IDLE:
            velocity = glm::vec3(0, 0, 0);
            break;
        case WALKING:
            if (CheckPartialOnLedge(map)) {
                velocity.x *= -1;
                //velocity.x = 0;
            }
            timer -= 1.0f;
            if (timer <= 0.0f) {
                timer = 25.0f;
                aiState = AOE;
                velocity.x *= 0.001f;
            }
            //velocity.x *= 1;
            
            break;
        case RUNNING:
            break;
        case SLOW_DOWN:
            break;
        case AOE:
            //int temp_size = effects_num;
            int aoe_sprite_left = 2;
            bool left_sprite_done = false;
            bool right_sprite_done = false;
            for (int i = 0; i < effects_num; ++i) {
                if (aoe_sprite_left > 0) {
                    if (effects[i].isActive == false && left_sprite_done == false) {
                        effects[i].isActive = true;
                        effects[i].position = glm::vec3(position.x - 1.0f, position.y, 0);
                        left_sprite_done = true;
                    }
                    else if (effects[i].isActive == false && left_sprite_done == true) {
                        effects[i].isActive = true;
                        effects[i].position = glm::vec3(position.x + 1.0f, position.y, 0);
                        right_sprite_done = true;
                    }
                    aoe_sprite_left -= 1;
                }
                else {
                    break;
                }
            }
            
            timer -= 1.0f;
            if (timer <= 0.0f) {
                timer = 100.0f + rand() % 200 + 1;
                aiState = WALKING;
                velocity.x *= 1000.0f;
                for (int i = 0; i < effects_num; ++i) {
                    effects[i].isActive = false;
                }
            }
            break;
    }
}
void Entity::AI(Entity player, Map* map) {//, Entity* effects_sprites, int ef_s_size){
    switch (aiType) {
        case PAPARAZZI:
            AIPaparazzi(player, map);
            break;
        case JOOMBA:
            AIJoomba(player, map);
            break;
    }
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram* program, int index)
{
    float u = (float)(index % cols) / (float)cols;
    float v = (float)(index / cols) / (float)rows;
    
    float width = 1.0f / (float)cols;
    float height = 1.0f / (float)rows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v };
    
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}


void Entity::Update(float deltaTime, Entity* objects, int objectCount, Map* map, Entity* enemies, int enemyCount)
{
    if(isActive){
        collidedTop = false;
        collidedBottom = false;
        collidedLeft = false;
        collidedRight = false;
    }
    
    
    velocity += acceleration * deltaTime;
    
    position.y += velocity.y * deltaTime; // Move on Y
    CheckCollisionsY(map);
    CheckCollisionsY(objects, objectCount); // Fix if needed
    
    position.x += velocity.x * deltaTime; // Move on X
    CheckCollisionsX(map);
    CheckCollisionsX(objects, objectCount); // Fix if needed
    if (entityType == PLAYER)
    {
        CheckCollisionsX(enemies, enemyCount);
        CheckCollisionsY(enemies, enemyCount);
    }
    
    if(entityType == ENEMY){
        CheckCollisionsX(objects, objectCount);
        CheckCollisionsY(objects, objectCount);
        
        if(!isStatic){
            AI(*objects, map);
        }
        else{
            velocity = glm::vec3(0,0,0);
            isStatic = true;
        }
    }
    
    if (velocity.x == 0 && velocity.y == 0) return;
    
    if (velocity.x > 0)
    {
        currentAnim = walkRight;
    }
    if (velocity.x < 0)
    {
        currentAnim = walkLeft;
    }
    /*if (velocity.y > 0)
     {
     currentAnim = jumpUp;
     }
     if (currentAnim == jumpUp)
     {
     animFrames = 1;
     }
     else
     {
     animFrames = 6;
     }*/
    animTime += deltaTime;
    if (animTime >= 0.25f)
    {
        animTime = 0;
        animIndex++;
        if (animIndex >= animFrames)
        {
            animIndex = 0;
        }
    }
}



void Entity::Render(ShaderProgram *program) {
    if (isActive == true)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        program->SetModelMatrix(modelMatrix);
        
        if (entityType == PLAYER)
        {
            DrawSpriteFromTextureAtlas(program, currentAnim[animIndex]);
        }
        else
        {
            float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
            float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
            
            glBindTexture(GL_TEXTURE_2D, textureID);
            
            glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
            glEnableVertexAttribArray(program->positionAttribute);
            
            glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
            glEnableVertexAttribArray(program->texCoordAttribute);
            
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            glDisableVertexAttribArray(program->positionAttribute);
            glDisableVertexAttribArray(program->texCoordAttribute);
        }
    }
}

