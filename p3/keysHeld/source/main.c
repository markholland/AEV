
#include <nds.h>
#include <stdio.h>

#include <input.h>

#define Color_Red "\x1b[31m" // Color Red
#define Color_Green "\x1b[32m" // Color Green
#define Color_Blue "\x1b[34m" // Color Blue
#define Color_Yellow "\x1b[33m" // Color Yellow
#define Color_Text "\x1b[38m"  // Color Grey


int main(void) {
	int held;
 	consoleDemoInit();

 	while(1) {

 		printf("%sKeys pressed program\n", Color_Yellow);
 		printf("--------------------\n");
 		
		scanKeys();
		held = keysHeld();
		if( held & KEY_A)
			printf("%sKey %sA%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sA%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_B)
			printf("%sKey %sB%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sB%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_SELECT)
			printf("%sKey %sSELECT%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sSELECT%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_START)
			printf("%sKey %sSTART%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sSTART%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_RIGHT)
			printf("%sKey %sRIGHT%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sRIGHT%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_LEFT)
			printf("%sKey %sLEFT%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sLEFT%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_UP)
			printf("%sKey %sUP%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sUP%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_DOWN)
			printf("%sKey %sDOWN%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sDOWN%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_R)
			printf("%sKey %sR%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sR%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_L)
			printf("%sKey %sL%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sL%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_X)
			printf("%sKey %sX%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sX%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_Y)
			printf("%sKey %sY%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sY%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		if( held & KEY_TOUCH)
			printf("%sTouch pad %sis touched\n", Color_Text, Color_Green);
		else
			printf("%sTouch pad %sis not touched\n", Color_Text, Color_Red);

		if( held & KEY_LID)
			printf("%sKey %sLID%s is %spressed\n", Color_Text, Color_Blue, Color_Text, Color_Green);
		else
			printf("%sKey %sLID%s is %sreleased\n", Color_Text, Color_Blue, Color_Text, Color_Red);

		swiWaitForVBlank();

		consoleClear();
	}

	return 0; 

}