

#include "kitco_fork.h"
#include <EEPROM.h>
#define SCREEN_HEIGHT  48
#define SCREEN_WIDTH  84
#define OBSTACLES_COUNT  5

int record = 0;
int setup_done = 0;

struct Obstacle {
  byte height;
  byte width;
  byte x;
  byte y;
  byte inverse;
};

struct Obstacle obstacles[]  = { 
  { 15 , 10 , 10, SCREEN_HEIGHT, 1 },
  { 15 , 10 , 30, SCREEN_HEIGHT, 1 },
  { 15 , 10 , 30, 0, 0 },
  { 15 , 10 , 50, 0, 0 },
  { 15 , 10 , 70, 0, 0 }
 };

void setup() {
  Serial.begin(9600);
  initialiserKitco(1);
  lcdBegin();
  setContrast(50);
  record = EEPROM.read(0)+EEPROM.read(1)*255;
}



void drawObstacles(struct Obstacle obstacles[]) {
  int i = 0;
  for(i=0; i <= OBSTACLES_COUNT; i++) {
    int x1 = obstacles[i].x + obstacles[i].width;
    int y1;
    int y2;
    if (obstacles[i].inverse == 0) {
      y1 = obstacles[i].y ;
      y2 = y1 + obstacles[i].height;
    } else {
      y1 = obstacles[i].y;
      y2 = y1 - obstacles[i].height;
    }
    createRectangle(obstacles[i].x, y1, x1, y2, true, NOIR);
  }
     
  updateDisplay();
}


void setupGame(struct Obstacle obstacles[]) {
  clearDisplay(BLANC);
  drawObstacles(obstacles);
}



void moveObstacles(struct Obstacle obstacles[]){
   int i = 0;
   clearDisplay(BLANC);
    for(i=0; i <= OBSTACLES_COUNT; i++) {
      obstacles[i].x -= 1;
    }
   drawObstacles(obstacles);
}


// Main loop run after setUp
void loop() {
  delay(500);
  if (setup_done == 0){
    setupGame(obstacles);
    setup_done = 1;
  } else {
    moveObstacles(obstacles);
  }
  


}
