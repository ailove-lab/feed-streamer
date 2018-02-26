#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <yaml.h>

#include "raylib.h"
#include "raymath.h"
#include "easings.h"
#include "timeline.h"

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

int screenWidth   = 640;
int screenHeight  = 360;
int frame = 0;
Texture2D product;
SpriteFont font;
int fontSize = 96;
char* msg = "$199";

Timeline tl;

void init();
void cleanup();

int main() {
    InitWindow(screenWidth, screenHeight, "feed-stream");

    init();
    
    float scale = MAX(
        (float)screenWidth /product.width, 
        (float)screenHeight/product.height);
    float price_x = -200.0;
    float rotation = 0.0;

    Channel* c = CreateTimelineChannel(&tl, &scale);
    AddKey(c,  60, 0.0, EaseCubicOut);
    AddKey(c, 120, scale, EaseLinearNone); 
    AddKey(c, 320, scale+0.1, EaseCubicIn);
    AddKey(c, 380, 0.0, NULL);

    c = CreateTimelineChannel(&tl, &price_x);
    AddKey(c, 100, -200.0, EaseElasticOut);
    AddKey(c, 150,   20.0, EaseLinearNone); 
    AddKey(c, 320,   20.0, EaseCubicIn);
    AddKey(c, 380, -200.0, NULL);
    
    while (!WindowShouldClose()) {

        UpdateTimeline(&tl, frame);
        BeginDrawing();
        {
            ClearBackground(WHITE);

            Vector2 position = {
                 screenWidth /2.0 - product.width /2.0*scale, 
                 screenHeight/2.0 - product.height/2.0*scale};

            // Vector2 position = {0,0};
            DrawTextureEx(
                product,
                position,
                rotation, 
                scale, 
                WHITE);
                      
            // DrawText("feed-stream", 8, 8, 20, LIGHTGRAY);

            Vector2 size = MeasureTextEx(font, msg, fontSize, 0);
            Vector2 pos  = {price_x, screenHeight - 30.0};
            DrawRectangle(pos.x-10, pos.y-size.y+20, size.x+20, size.y, GOLD);
            DrawTextEx(font, msg, Vector2Add(pos,(Vector2){2,2}), fontSize, 0, GRAY);
            DrawTextEx(font, msg, pos, fontSize, 0, WHITE);
            DrawFPS(screenWidth - 88, screenHeight - 28);

        }
        EndDrawing();
        usleep(15*1000);
        frame++;
        frame %= 420;
    }
    cleanup();
    CloseWindow();
    
    return 0;
}

void init() {
    product = LoadTexture("resources/product.png");
    font = LoadSpriteFontEx("resources/Roboto-Black.ttf", fontSize, 0, 0); 
    tl = CreateTimeline();
}

void cleanup() {
    UnloadTexture(product);
    UnloadSpriteFont(font);
    DestroyTimeline(&tl);
}
