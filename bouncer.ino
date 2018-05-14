
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

struct Obstacle infos[2]  = { 
  { 10 , 10 , 68, 0, 0 },
  { 10 , 10 , 38, 0, 0 }
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
    int x1 = infos[i].x + infos[i].width;
    int y2 = infos[i].y + infos[i].height;
    createRectangle(infos[i].x, infos[i].y, x1, y2, true, NOIR);
    updateDisplay();
  }
}


void setupGame(struct Obstacle infos[]) {
  clearDisplay(BLANC);
  drawObstacle(infos);
}

void moveObstacle(struct Obstacle *infos) {
  (*infos).x -= 1;
  clearDisplay(BLANC);
  drawObstacle(infos);
}


// Main loop run after setUp
void loop() {
  delay(200);
  if (setup_done == 0){
    setupGame(infos);
    setup_done = 1;
  } else {
    int i = 0;
    for(i=0;i<2;i++) {
      moveObstacle(&infos[i]);
    }
  }
  


}
