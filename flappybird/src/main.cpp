#include <Arduino.h>
#include "flappybird.h"

typedef struct {
    void (*initFunc)(void);
    void (*updateFunc)(void);
    void (*renderFunc)(void);
} MODULE_FUNCS;

static const MODULE_FUNCS moduleTable[] = {
    { initmenu,  updatemenu,  rendermenu },
    { initgame, updategame, rendergame },
    { inithighscore,  updatehighscore,  renderhigiscore },
};

uint8_t Mode = MainMenu;

void setup() {
  // put your setup code here, to run once:
  arduboy.boot();
  arduboy.blank();
  arduboy.flashlight();
  arduboy.systemButtons();
  arduboy.setFrameRate(GAME_FPS);

  randomSeed(analogRead(35));
  moduleTable[Mode].initFunc();
}

void loop() {
  if (! nextFrame()) return;
  
  arduboy.clear();
  moduleTable[Mode].updateFunc();
  moduleTable[Mode].renderFunc();
  arduboy.display();

  if(per_menustatus != g_menustatus){
    per_menustatus = g_menustatus;
    Mode = g_menustatus;
    if(Mode != MainMenu)  moduleTable[Mode].initFunc();
  }
  // put your main code here, to run repeatedly:
}