#ifndef COMMON_H
#define COMMON_H

#include "MyArduboy.h"

/*  Defines  */

//#define DEBUG

#define GAME_TITLE      "HOPPER"
#define GAME_ID         "JANEY_N2"
#define GAME_VERSION    "1.0.0.0"
#define GAME_RELEASED   "2021-2-7"
#define APP_DESIGNED    "JaneyXu"


//The  authorship  原作者信息
#define APP_TITLE       "HOPPER"
#define APP_CODE        "OBN-Y02"
#define APP_VERSION     "0.22"
#define APP_RELEASED    "NOVEMBER 2017"

/*  Typedefs  */

typedef unsigned char   uchar;
typedef unsigned int    uint;

/*  Global Functions  */

void initLogo(void);
bool updateLogo(void);
void drawLogo(void);

void initTitle(void);
bool updateTitle(void);
void drawTitle(void);
uint8_t setLastScore(int score, uint32_t time);

void initGame(void);
bool updateGame(void);
void drawGame(void);

/*  Global Variables  */

extern MyArduboy arduboy;

/*  For Debugging  */

#ifdef DEBUG
extern bool             dbgPrintEnabled;
extern char             dbgRecvChar;
#define dprint(...)     (!dbgPrintEnabled || Serial.print(__VA_ARGS__))
#define dprintln(...)   (!dbgPrintEnabled || Serial.println(__VA_ARGS__))
#else
#define dprint(...)
#define dprintln(...)
#endif

#endif // COMMON_H
