
// Nécessaire pour l'environnement Kitco
#include "kitco_fork.h"
#include <EEPROM.h>

#define AIRE_JEU_X2 30
#define AIRE_JEU_X1 30


int record = 0;
int setup_done = 0;

struct Obstacle {
  byte height;
  byte width;
  byte x;
  byte y;
  byte inverse;
};

struct Obstacle infos[]  = { 
  { 10 , 10 , 68, 0, 0 },
  { 10 , 10 , 38, 0, 1 }
 };
// La partie Setup concerne ce qui va être exécuté au démarrage de Kitco
void setup() {
  Serial.begin(9600);
  // Cette commande est nécessaire pour intialiser Kitco à son démarrage
  initialiserKitco(1);
  lcdBegin();
  setContrast(50);
  record = EEPROM.read(0)+EEPROM.read(1)*255;
}

// createRectangle will draw a rectangle from x0,y0 top-left corner to
// a x1,y1 bottom-right corner. Can be filled with the fill
// parameter, and colored with bw.
// This function was grabbed from the SparkFun ColorLCDShield
// library.


void drawObstacle(struct Obstacle infos[]) {
  int i = 0;
  for(i=0;i<2;i++) {
    int x1 = infos[i].x +infos[i].width;
    int y1;
    int y2;
    if (infos[i].inverse == 0) {
      y1 = infos[i].y + 30;
      y2 = infos[i].y + infos[i].height;
    } else {
      y1 = infos[i].y;
      y2 = infos[i].y + infos[i].height;
    }
    createRectangle(infos[i].x, y1, x1, y2, true, NOIR);
  }
     
  updateDisplay();
}


void setupGame(struct Obstacle infos[]) {
  clearDisplay(BLANC);
  drawObstacle(infos);
}

void moveObstacle(struct Obstacle *info) {
  (*info).x -= 1;
  int x1 = (*info).x + (*info).width;
  int y2 = (*info).y + (*info).height;
  createRectangle((*info).x, (*info).y, x1, y2, true, NOIR);
}

void moveObstacles(struct Obstacle infos[]){
   int i = 0;
   clearDisplay(BLANC);
    for(i=0;i<2;i++) {
      moveObstacle(&infos[i]);
    }
    updateDisplay();
}


// Main loop run after setUp
void loop() {
  delay(500);
  if (setup_done == 0){
    setupGame(infos);
    setup_done = 1;
  } else {
    moveObstacles(infos);
  }
  


}
