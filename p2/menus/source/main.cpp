/*---------------------------------------------------------------------------------

	Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>

void UsersName(void);
void AlarmHour(void);
void AlarmMinute(void);
void BirthDay(void);
void BirthMonth(void);
void RTCoffset(void);
void Theme(void);
void UsersMessage(void);

void LCDMainOnBottom(void);
void LCDMainOnTop(void);
void LCDSwap(void);
void LEDBlink(void);
void SystemShutDown(void);
void SystemSleep(void);

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

struct Demo personalData[] =
{ 
	{UsersName, "Users name", "Displays the users name."},
	{AlarmHour, "Alarm hour", "Displays the alarm hour."},
	{AlarmMinute, "Alarm minute", "Displays the alarm minute."},
	{BirthDay, "Birth day", "Displays the users birth day."},
	{BirthMonth, "Birth month", "Displays the users birth month."},
	{RTCoffset, "RTC offset", "Displays the RTC offset(timezone)."},
	{Theme, "Theme", "Displays the users chosen theme ID."},
	{UsersMessage, "Users message", "Displays the users defined poersonal message."},
		
};

struct Demo functions[] =
{ 
	{LCDMainOnBottom, "lcdMainOnBottom", "Makes the bottom screen the Main"},
	{LCDMainOnTop, "lcdMainOnTop", "Makes the top screen the Main"},
	{LCDSwap, "lcdSwap", "Swaps the displays"},
	{LEDBlink, "ledBlink", "Set the LED blink mode."},
	{SystemShutDown, "systemShutDown", "Turn off the system"},
	{SystemSleep, "systemSleep", "Put the system to sleep"},
	
};

struct Category categories[] = 
{
	{"Personal Data", personalData, sizeof(personalData) / sizeof(Demo)},
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

