#ifndef OBJECT_H
#define OBJECT_H
#include "raylib.h"

extern Texture2D textureArray[10];

typedef struct 
{
    Vector2 topLeftAnchor;
    Vector2 topRightAnchor;
    Vector2 bottomLeftAnchor;
    Vector2 bottomRightAnchor;    
    Vector2 centerAnchor;
    Rectangle textureArea;
    unsigned short opacity;
    unsigned int texture;
    double angle;
    unsigned int layer;
} Sprite;

typedef struct  
{
    Vector2 topLeftAnchor;
    Vector2 topRightAnchor;
    Vector2 bottomLeftAnchor;
    Vector2 bottomRightAnchor;    
    Vector2 centerAnchor;
    Vector2 spriteOffset;
    Rectangle collider;
    Sprite *sprite;
    double angle;
} Object;

enum Textures  
{
    TEXTURE_PIPE1,
    TEXTURE_PIPE2,
    TEXTURE_PARTICLE,
    TEXTURE_PLAYER,
};

enum ObjectLayers 
{
    LAYERS_PLAYER,
    LAYERS_PARTICLE,
    LAYERS_PIPES,
};

void initTextures();
Object* createObject(Rectangle collider, Sprite *sprite, double angle);
Sprite* createSprite(Rectangle area, unsigned int texture, unsigned int layer, double angle);

void destroyObject(Object *object);
void destroySprite(Sprite *sprite);
void updateObjectAnchors(Object *object);
void updateSpriteAnchors(Sprite *sprite);
void moveObject(Object *object, float x, float y);
void moveObjectRelative(Object *object, float x, float y);
void moveSprite(Sprite *sprite, float x, float y);
void moveSpriteRelative(Sprite *sprite, float x, float y);
void drawSprites();
//void allObjectsLayerSort(); 
void freeObjects();
void freeSprites();
int returnObjectAmount();
bool layersSortedCorrectly();

#endif