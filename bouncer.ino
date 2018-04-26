
// Nécessaire pour l'environnement Kitco
#include "kitco.h"
#include <EEPROM.h>

#define AIRE_JEU_X2 30
#define AIRE_JEU_X1 30

int record = 0;


// La partie Setup concerne ce qui va être exécuté au démarrage de Kitco
void setup() {

  // Cette commande est nécessaire pour intialiser Kitco à son démarrage
  initialiserKitco(1);
  lcdBegin();
  setContrast(50);
  record = EEPROM.read(0)+EEPROM.read(1)*255;
}



void setupGame() {
  int c = 1;
  clearDisplay(BLANC);
  // ecrireEcran(s,c,5,NOIR);
  setChar('c', 10, 10, 1);
  updateDisplay();
}

// Loop est la boucle principale, va se lancer en boucle après Setup
void loop() {
  setupGame();



}
