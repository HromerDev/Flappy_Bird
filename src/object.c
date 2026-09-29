#include "dynamic_array.h"
#include "object.h"
#include "stdio.h"
#include "stdlib.h"

Texture2D textureArray[10];
dynarray *allObjects;
dynarray *allSprites;

void initTextures() 
{
    allObjects = malloc(sizeof(dynarray)); 
    dynarray_init(allObjects, 1);

    allSprites = malloc(sizeof(dynarray));
    dynarray_init(allSprites, 1);

    textureArray[TEXTURE_PLAYER] = LoadTexture("assets/player.png");
    textureArray[TEXTURE_PIPE1] = LoadTexture("assets/pipe1.png");
    textureArray[TEXTURE_PIPE2] = LoadTexture("assets/pipe2.png");
    textureArray[TEXTURE_PARTICLE] = LoadTexture("assets/particle4.png");
}

Object* createObject(Rectangle collider, Sprite *sprite, double angle)
{
    Object *object = malloc(sizeof(Object));

    object->collider = collider;
    object->sprite = sprite;
    object->angle = angle;
    
    object->spriteOffset = (Vector2){0,0};

    updateObjectAnchors(object);

    moveSprite(object->sprite, object->centerAnchor.x + object->spriteOffset.x - object->sprite->textureArea.width / 2, object->centerAnchor.y + object->spriteOffset.y - object->sprite->textureArea.height / 2);  
    dynarray_push(allObjects, object);
    
    return object;
}

Sprite* createSprite(Rectangle textureArea, unsigned int texture, unsigned int layer, double angle)
{
    Sprite* sprite = malloc(sizeof(Sprite));    

    sprite->textureArea = textureArea;
    sprite->texture = texture; 
    sprite->layer = layer;
    sprite->angle = angle;
    sprite->opacity = 255;

    updateSpriteAnchors(sprite);
    dynarray_push(allSprites, sprite);

    // Binary search for the insertion position.
    int low = 0;
    int high = allSprites->size - 1;

    Sprite* temp = allSprites->items[0];

    while (low < high)
    {
        int mid = low + (high - low) / 2;
        temp = allSprites->items[mid];

        if (temp->layer < sprite->layer)       
            low = mid + 1;        
        else        
            high = mid;        
    }

    int insertIndex = low;
    temp = allSprites->items[insertIndex];
    // If the new sprite belongs after the last element.
    if (temp->layer < sprite->layer)
        insertIndex++;

    // Shift elements right to make room.
    for (int i = allSprites->size - 1; i > insertIndex; i--)   
        allSprites->items[i] = allSprites->items[i - 1];
    
    allSprites->items[insertIndex] = sprite;

    return sprite;
}

bool layersSortedCorrectly() 
{        
    for(int i = 0; i < allSprites->size - 1; i++) 
    {   
        Sprite* temp1 = allSprites->items[i];
        Sprite* temp2 = allSprites->items[i + 1];
        
        if(temp1->layer > temp2->layer)
            return true;
    }
    return true;
}

void destroySprite(Sprite *sprite) 
{
    dynarray_remove(allSprites, sprite);
}

void destroyObject(Object *object) 
{
    dynarray_remove(allObjects, object);
}

void updateObjectAnchors(Object *object) 
{
    object->topLeftAnchor = (Vector2){object->collider.x, object->collider.y}; 
    object->topRightAnchor = (Vector2){object->collider.x + object->collider.width, object->collider.y};
    
    object->bottomLeftAnchor = (Vector2){object->collider.x, object->collider.y + object->collider.height};
    object->bottomRightAnchor = (Vector2){object->collider.x + object->collider.width, object->collider.y + object->collider.height};

    object->centerAnchor = (Vector2){object->collider.x + object->collider.width / 2, object->collider.y + object->collider.height / 2};
}

void updateSpriteAnchors(Sprite *sprite) 
{
    sprite->centerAnchor = (Vector2){sprite->textureArea.x + sprite->textureArea.width / 2, sprite->textureArea.y + sprite->textureArea.height / 2};
}

void moveSprite(Sprite *sprite, float x, float y) 
{
    sprite->textureArea.x = x;
    sprite->textureArea.y = y;

    updateSpriteAnchors(sprite);
}

void moveSpriteRelative(Sprite *sprite, float x, float y)
{
    sprite->textureArea.x += x;
    sprite->textureArea.y += y;

    updateSpriteAnchors(sprite);
}

void moveObject(Object *object, float x, float y)
{
    object->collider.x = x;
    object->collider.y = y;

    updateObjectAnchors(object);

    if(object->sprite != NULL)     
        moveSprite(object->sprite, object->centerAnchor.x + object->spriteOffset.x - object->sprite->textureArea.width / 2, object->centerAnchor.y + object->spriteOffset.y - object->sprite->textureArea.height / 2);
    
}

void moveObjectRelative(Object *object, float x, float y) 
{
    object->collider.x += x;
    object->collider.y += y;

    updateObjectAnchors(object);

    if(object->sprite != NULL)     
        moveSpriteRelative(object->sprite, x, y);
}

void drawSprites()
{
    ClearBackground((Color){203, 219, 252, 255});
    
    for(int i = 0; i < allSprites->size; i++) 
    {
        Sprite *temp = allSprites->items[i];
        //Object *temp = allObjects->items[i];
        
        DrawTexturePro(textureArray[temp->texture], (Rectangle){0,0, textureArray[temp->texture].width, textureArray[temp->texture].height}, (Rectangle) {temp->centerAnchor.x , temp->centerAnchor.y, temp->textureArea.width, temp->textureArea.height}, (Vector2){temp->textureArea.width / 2,temp->textureArea.height / 2}, temp->angle, (Color) {255,255,255,temp->opacity});
        /*
        DrawCircle(temp->topLeftAnchor.x, temp->topLeftAnchor.y, 4, GREEN);
        DrawCircle(temp->topRightAnchor.x, temp->topRightAnchor.y, 4, GREEN);
        DrawCircle(temp->bottomLeftAnchor.x, temp->bottomLeftAnchor.y, 4, GREEN);
        DrawCircle(temp->bottomRightAnchor.x, temp->bottomRightAnchor.y, 4, GREEN);
        */
    }  
    
    /*
    for(int i = 0; i < allObjects->size; i++) 
    {
        Object *temp = allObjects->items[i];
        
        DrawCircle(temp->topLeftAnchor.x, temp->topLeftAnchor.y, 4, GOLD);
        DrawCircle(temp->topRightAnchor.x, temp->topRightAnchor.y, 4, GOLD);
        DrawCircle(temp->bottomLeftAnchor.x, temp->bottomLeftAnchor.y, 4, GOLD);
        DrawCircle(temp->bottomRightAnchor.x, temp->bottomRightAnchor.y, 4, GOLD);
        
    }
    */
}

void freeObjects() 
{
    dynarray_free(allObjects);
    free(allObjects);
    allObjects = NULL;
}

void freeSprites() 
{
    dynarray_free(allSprites);
    free(allSprites);
    allSprites = NULL;
}

int returnObjectAmount() 
{
    return allObjects->size; // min >> max
}