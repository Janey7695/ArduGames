#pragma once

#include <Arduboy2.h>
#include "at24cxx.h"

#define GAME_TITLE      "FLAPPYBIRD"
#define GAME_ID         "JANEY_N1"
#define GAME_VERSION    "1.0.4.6"
#define GAME_RELEASED   "2021-2-7"
#define APP_DESIGNED    "JaneyXu"

#define GAME_FPS	30

#define GAME_OVER	    0
#define GAME_CONTINUE	1
#define GAME_MENU       2
#define GAME_PAUSE      3


// #define GameLEVEL_EASY	0
// #define GameLEVEL_MID	1
// #define GameLEVEL_HARD	2

#define FlappyBirdScore_ADDR	64
#define FlappyBirdScore_ADDR_END	FlappyBirdScore_ADDR+1

#define MainMenu	0
#define BeginGame	1
#define HeightList	2

typedef struct bird
{
    float y;
    unsigned char fullspeed;
}BirdStruct;

#define BirdRISE	1
#define BirdFULL	0

typedef struct pillar
{
    float x;
    float y;
    float pillarClearance;
    struct pillar* nextpillar;
}Pillarstruct;

bool nextFrame();

void initmenu();
void updatemenu();
void rendermenu();

void initgame();
void updategame();
void rendergame();

void inithighscore();
void updatehighscore();
void renderhigiscore();

extern Arduboy2 arduboy;
extern uint8_t g_gamestatus;
extern unsigned char g_birdStatus;
extern unsigned char g_menustatus;
extern unsigned char per_menustatus;
