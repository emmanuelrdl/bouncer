
// Nécessaire pour l'environnement Kitco
#include "kitco.h"
#include <EEPROM.h>

#define AIRE_JEU_X2 30
#define AIRE_JEU_X1 30

int record = 0;

struct Obstacle {
  byte height;
  byte width;
  byte x;
  byte y;
  byte inverse;
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
void createRectangle(int x0, int y0, int x1, int y1, boolean fill, boolean bw)
{
  // check if the rectangle is to be filled
  if (fill == 1)
  {
    int xDiff;

    if(x0 > x1)
      xDiff = x0 - x1; //Find the difference between the x vars
    else
      xDiff = x1 - x0;

    while(xDiff > 0)
    {
      ligneEcran(x0, y0, x0, y1, bw);

      if(x0 > x1)
        x0--;
      else
        x0++;

      xDiff--;
    }
  }
  else
  {
    // best way to draw an unfilled rectangle is to draw four lines
    ligneEcran(x0, y0, x1, y0, bw);
    ligneEcran(x0, y1, x1, y1, bw);
    ligneEcran(x0, y0, x0, y1, bw);
    ligneEcran(x1, y0, x1, y1, bw);
  }
}


void drawObstacle(struct Obstacle infos) {
  int x1 = infos.x + infos.width;
  int y2 = infos.y + infos.height;
  createRectangle(infos.x, infos.y, x1, y2, true, NOIR);
  updateDisplay();
}


void setupGame() {
  clearDisplay(BLANC);
  struct Obstacle infos  = { 10 , 10 , 8, 8, 0 };
  drawObstacle(infos);
}

// Loop est la boucle principale, va se lancer en boucle après Setup
void loop() {
  delay(500);
  setupGame();



}
