/*---------------------------------------------------------------------------------

	Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>

void playPSG(void);
void playNoise(void);

struct Demo
{
	fp go;
	const char* name;
	const char* description;
};

struct Category
{
	const char* name;
	Demo *demos;
	int count;
};


struct Demo functions[] =
{ 
	{playPSG, "playPSG", "Play PSG"},
	{playNoise, "playNoise", "Play Noise"}
	
};

struct Category categories[] = 
{
	{"Functions", functions, sizeof(functions) / sizeof(Demo)},
};

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	int keys;
	

	
	while(1) {
		int selectedCategory = 0;
		int selectedDemo = 0;
		
		bool selected = false;
		
		int catCount = sizeof(categories) / sizeof(Category);
		int demoCount = 0;
		
		videoSetModeSub(MODE_0_2D);
		consoleDemoInit();
		
		while(!selected) {

			scanKeys();
			
			keys = keysDown();
			
			if(keys & KEY_UP) selectedCategory--;
			if(keys & KEY_DOWN) selectedCategory++;
			if(keys & KEY_A) selected = true;
			
			if(selectedCategory < 0) selectedCategory = catCount - 1;
			if(selectedCategory >= catCount) selectedCategory = 0;
			
			swiWaitForVBlank();
			consoleClear();
			for(int ci = 0; ci < catCount; ci++) {
				iprintf("%c%d: %s\n", ci == selectedCategory ? '*' : ' ', ci + 1, categories[ci].name); 		
			}	
		}
		
		selected = false;
		
		demoCount = categories[selectedCategory].count;
		
		while(!selected) {

			scanKeys();
			
			keys = keysDown();
			
			if(keys & KEY_UP) selectedDemo--;
			if(keys & KEY_DOWN) selectedDemo++;
			if(keys & KEY_A) selected = true;
			if(keys & KEY_B) break;
			
			if(selectedDemo < 0) selectedDemo = demoCount - 1;
			if(selectedDemo >= demoCount) selectedDemo = 0;
			
			swiWaitForVBlank();
			consoleClear();

			for(int di = 0; di < demoCount; di++) {
				iprintf("%c%d: %s\n", di == selectedDemo ? '*' : ' ', di + 1, categories[selectedCategory].demos[di].name); 		
			}	
		}
		
		if(selected) {
			consoleClear();
			//iprintf("Use arrow keys to scroll\nPress 'B' to exit");
			categories[selectedCategory].demos[selectedDemo].go();
		}
	}
	
}

