static bool memoryArray[MATRIX_WIDTH][MATRIX_HEIGHT];
static bool liveArray[MATRIX_WIDTH][MATRIX_HEIGHT];
static int myCounter;
int maxCount = 30;

void liveSet(x,y){
	if (leds[x,y]){//is lit
		memoryArray[x,y] = 1;
	}
	else{//is black
		memoryArray[x,y] = 0;
	}
}
bool liveCheck(x,y){
	if (leds[x,y]){//is lit
		return 1;
	}
	else{//is black
		return 0;
	}
}
void seed(){
	for (int i = 0; i < MATRIX_WIDTH; i++){
		for (int j = 0; j < MATRIX_HEIGHT; j++){
			memoryArray[i][j]= random(0,1);
		}
	}
}
void gameOfLifeDraw(){
	for (int i = 0; i < MATRIX_WIDTH; i++){
		for (int j = 0; j < MATRIX_HEIGHT; j++){
			if (liveArray[i][j]==1){
				leds(i,j)=CRGB::red;
			}
			else {
				leds(i,j)=0,0,0;
			}
		}
	}
	myCounter++;
	if (myCounter >= maxCount){
		myCounter=0;
	}
}
void gameOfLife(){
	int check1[2],check2[2],check3[2],neighbourCounter; 
	if (myCounter == 1){
		seed();
	}
	for (int i = 0; i < MATRIX_WIDTH; i++){
		for (int j = 0; j < MATRIX_HEIGHT; j++){
			liveSet(i,j);
		}
	}
	for (int i = 0; i < MATRIX_WIDTH; i++){
		for (int j = 0; j < MATRIX_HEIGHT; j++){			
			check1 = (i-1,j+1);
			check2 = (i-1,j);
			check3 = (i-1,j-1);
			for (int k = check1[1]; k < check1[1]+3; k++){
				if (liveCheck(k,check1[2])=1){
					neighbourCounter++;
				}
			}
			for (int l = check1[1]; l < check2[1]+3; l++){
				if (liveCheck(l,check2[2])=1){
					neighbourCounter++;
				}
			}
			for (int m = check3[1]; m < check3[1]+3; m++){
				if (liveCheck(m,check3[2])=1){
					neighbourCounter++;
				}
			}
			if (livecheck(i,j)=1{
				neighbourCounter=neighbourCounter-1;
				if (neighbourCounter<2||neighbourCounter>3){
					liveArray[i,j]=0;
				}
				else{
					liveArray[i,j]=1;
				}
			}
			else if (neighbourCounter==3){
				liveArray[i,j]=1;
			}
		}
	}
	gameOfLifeDraw();
}