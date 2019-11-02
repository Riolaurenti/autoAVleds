static bool memoryArray[MATRIX_WIDTH][MATRIX_HEIGHT];
static bool liveArray[MATRIX_WIDTH][MATRIX_HEIGHT];
static int myCounter;
int maxCount = 30;

void liveSet(bool x, bool y) {
  if (leds[x, y]) { //is lit
    *memoryArray[x, y] = true;
  }
  else { //is black
    *memoryArray[x, y] = false;
  }
}
int liveCheck(int x, int y) {
  //Serial.println("livechecking");
  if (memoryArray[x, y] == 1) { //is lit
    //Serial.println("liveCheck = 1");
    return 1;
  }
  else { //is black
    //Serial.println("liveCheck = 0");
    return 0;
  }
}
void seed() {
  Serial.println("seeded");
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    for (int j = 0; j < MATRIX_HEIGHT; j++) {
      memoryArray[i][j] = random8(0, 2);
      //Serial.println(memoryArray[i][j]);
    }
  }
}
void gameOfLifeDraw() {
  //Serial.println("Draw Triggered");
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    for (int j = 0; j < MATRIX_HEIGHT; j++) {
      Serial.print(liveArray[i][j]);
      Serial.print(",");
      if (liveArray[i][j] == 1) {
        leds(i, j) = 255, 0, 0;
      }
      else {
        leds(i, j) = 0, 0, 0;
      }
    }
    FastLED.show();
    Serial.println("drawn");
  }
  myCounter++;
  if ((myCounter >= maxCount) || (liveArray == 0)) {
    myCounter = 0;
  }
}
void gameOfLife() {
  static int check1[2], check2[2], check3[2], neighbourCounter;
  if (myCounter == 0) {
    seed();
  }
  else {
    for (int i = 0; i < MATRIX_WIDTH; i++) {
      for (int j = 0; j < MATRIX_HEIGHT; j++) {
        liveSet(i, j);
      }
    }
  }
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    for (int j = 0; j < MATRIX_HEIGHT; j++) {
      check1[0] = i - 1;
      check1[1] = j + 1;
      check2[0] = i - 1;
      check2[1] = j;
      check3[0] = i - 1;
      check3[1] = j - 1;
      for (int k = check1[1]; k < check1[1] + 3; k++) {
        if (liveCheck(k, check1[2]) == 1) {
          neighbourCounter++;
        }
      }
      for (int l = check2[1]; l < check2[1] + 3; l++) {
        if (liveCheck(l, check2[2]) == 1) {
          neighbourCounter++;
        }
      }
      for (int m = check3[1]; m < check3[1] + 3; m++) {
        if (liveCheck(m, check3[2]) == 1) {
          neighbourCounter++;
        }
        Serial.print("neighbour counter = ");
        Serial.println(neighbourCounter);
      }
      if (liveCheck(i, j) == 1) {
        neighbourCounter = neighbourCounter - 1;
        if (neighbourCounter < 2 || neighbourCounter > 3) {
          *liveArray[i, j] = 0;
        }
        else {
          *liveArray[i, j] = 1;
        }
      }
      else if (neighbourCounter == 3) {
        *liveArray[i, j] = 1;
      }
      neighbourCounter = 0;
    }
  }
  gameOfLifeDraw();
}
