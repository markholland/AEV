
#include <nds.h> 
#include <stdlib.h>
#include <stdio.h>

#define NUM_STARS 40

typedef struct
{
	int x;
	int y;
	int speed;
	unsigned short color;
}Star;


Star stars[NUM_STARS];

void MoveStar(Star* star) {
	star->x += star->speed;
	star->y += star->speed/rand() % 4 + 1;
	//iprintf("pos:%d",star->x);
	if(star->x >= SCREEN_WIDTH || star->x >= SCREEN_HEIGHT) {
		star->color = RGB15(rand() % 31 + 1,rand() % 31 + 1,rand() % 31 + 1);
		star->x = 0;
		star->y = rand() % 192; 
		star->speed = rand() % 4 + 1;
	}
}

void ClearScreen(void) {
	int i;

	for(i = 0; i < 256 * 192; i++)
		VRAM_A[i] = RGB15(0,0,0);
	}
	
void InitStars(void) {
	int i;
	for(i = 0; i < NUM_STARS; i++) {
		stars[i].color = RGB15(rand() % 31 + 1,rand() % 31 + 1,rand() % 31 + 1); 
		stars[i].x = rand() % 256; 
		stars[i].y = rand() % 192;
		stars[i].speed = rand() % 4 + 1;
	}
}
	
void DrawStar(Star* star) { 
	VRAM_A[star->x + star->y * SCREEN_WIDTH] = star->color;
}

void EraseStar(Star* star) {
	VRAM_A[star->x + star->y * SCREEN_WIDTH] = RGB15(0,0,0); 
}

int main(void) {
	consoleDemoInit();
	int i; 
	irqInit();
	irqEnable(IRQ_VBLANK);
	videoSetMode(MODE_FB0); 
	vramSetBankA(VRAM_A_LCD);
	ClearScreen();
	InitStars();

	//we like infinite loops in console dev!
	while(1) {
		swiWaitForVBlank();
		for(i = 0; i < NUM_STARS; i++) {
			EraseStar(&stars[i]);
			MoveStar(&stars[i]);
			DrawStar(&stars[i]); 
		}
	}
	return 0; 
}