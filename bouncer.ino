

#include "kitco_fork.h"
#include <EEPROM.h>
#define SCREEN_HEIGHT  48
#define SCREEN_WIDTH  84
#define OBSTACLES_COUNT  5

int record = 0;
int setup_done = 0;
int game_over = 0;

struct Obstacle {
  byte height;
  byte width;
  byte x;
  byte y;
  byte inverse;
};


struct Obstacle obstacles[]  = { 
  { 15 , 7 , 10, SCREEN_HEIGHT, 1 },
  { 15 , 7 , 75, SCREEN_HEIGHT, 1 },
  { 15 , 7 , 35, 0, 0 },
  { 15 , 7 , 50, 0, 0 },
  { 15 , 7 , 65, 0, 0 }
 };

struct Ball {
  byte height;
  byte width;
  byte x;
  byte y;
};

struct Ball ball = { 5 , 5 , 5, 5 };


void setup() {
  Serial.begin(9600);
  initialiserKitco(1);
  lcdBegin();
  setContrast(50);
  record = EEPROM.read(0)+EEPROM.read(1)*255;
}


void manageInput(){

  if (toucheHaut()) {
    ball.y--;
  }

  if (toucheBas() ) {
    ball.y++;
  }

}

void manageGame(){
   if (toucheDroite()) {
    setup_done = 0;
    game_over = 0;
    ball = { 5 , 5 , 5, 5 };
  }
}



void drawObstacles(struct Obstacle obstacles[]) {
  int i = 0;
  for(i=0; i < OBSTACLES_COUNT; i++) {
    int x1 = obstacles[i].x;
    int x2 = obstacles[i].x + obstacles[i].width;
    int y1;
    int y2;
    if (obstacles[i].inverse == 0) {
      y1 = obstacles[i].y ;
      y2 = y1 + obstacles[i].height;
    } else {
      y1 = obstacles[i].y;
      y2 = y1 - obstacles[i].height;
    }
    createRectangle(x1, y1, x2, y2, true, NOIR);
  }
     
  
}


void drawBall(struct Ball ball) {
  int x1 = ball.x;
  int x2 = x1 + ball.width;
  int y1 = ball.y;
  int y2 = y1 + ball.height;
  createRectangle(x1, y1, x2, y2, true, NOIR);
}


void setupGame(struct Obstacle obstacles[], struct Ball ball) {
  clearDisplay(BLANC);
  drawBall(ball);
  drawObstacles(obstacles);
}



void moveObstacles(struct Obstacle obstacles[]){
   int i = 0;
    for(i=0; i < OBSTACLES_COUNT; i++) {
      if (obstacles[i].x > 0) {
          obstacles[i].x -= 1;
        } else {
          obstacles[i].x = SCREEN_WIDTH;
          obstacles[i].width = 7;
          obstacles[i].height = rand() % 40;
        }
    }
   drawObstacles(obstacles);
}

void checkCollision() {
  for(int i=0; i < OBSTACLES_COUNT; i++) {
   int y1;
   int y2;
   if ((ball.x  + 5 > obstacles[i].x) && (ball.x < obstacles[i].x + 7)) {
      // Fake same X
      if (obstacles[i].inverse == 0) {
        y1 = obstacles[i].y ;
        y2 = y1 + obstacles[i].height;
      } else {
        y1 = obstacles[i].y;
        y2 = y1 - obstacles[i].height;
      }
      if (ball.y + ball.height > y1 && ball.y < y2 ) {
        clearDisplay(BLANC);
        ecrireEcran("GAME OVER",15,15,NOIR);
        ecrireEcran("press to play",2,25,NOIR);
        game_over = 1;
        break;
      }
      
   }
   
  }
}


// Main loop run after setUp
void loop() {
  delay(50);
  if (setup_done == 0 && game_over == 0){
    setupGame(obstacles, ball);
    setup_done = 1;
  } else if (setup_done == 1 && game_over == 0)  {
    manageInput();
    clearDisplay(BLANC);
    drawBall(ball);
    moveObstacles(obstacles);
    checkCollision();
    updateDisplay();
  } else if (game_over == 1)  {
    manageGame();
  }


}
