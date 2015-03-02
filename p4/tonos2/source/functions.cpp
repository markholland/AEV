#include <nds.h>

#include <stdio.h>
#include <stdlib.h>

#include <inttypes.h>

#include <system.h>

#define Color_Red "\x1b[31m" // Color Red
#define Color_Green "\x1b[32m" // Color Green
#define Color_Blue "\x1b[34m" // Color Blue
#define Color_Yellow "\x1b[33m" // Color Yellow
#define Color_Text "\x1b[38m"  // Color Grey

const int MIN_FREQ 		= 20;
const int MAX_FREQ 		= 20000;
const int MIN_VOL 		= 0;
const int MAX_VOL 		= 127;
const int PAN_LEFT 		= 0;
const int PAN_RIGHT 	= 127;
const int PAN_CENTER	= 64;

void waitfor(int keys);

void topScreenAndConsole(void) {

	videoSetMode(MODE_0_2D);
	consoleInit(0,0,BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true);	
}

int channel = 0;
bool play = true;

int type = 0;

// freq = 0, volume = 1, pan = 2
int selected = 0;
int freq = MIN_FREQ; // start in 20Hz
int volume = 64;
int pan = PAN_CENTER;

//this function will be called by the timer.
// PSG = 0, Noise = 1
void timerCallBack(void)
{

	consoleClear();

	iprintf("%sUse arrows to change selection\nand adjust values\n\n", Color_Text);

	switch(selected) {
		case 0:
			iprintf("%sFrequency selected\n\n", Color_Green);
			break;
		case 1:
			iprintf("%sVolume selected\n\n", Color_Red);
			break;
		case 2:
			iprintf("%sPan selected\n\n", Color_Yellow);
			break;
	}

	if(type) {
		iprintf("%sPlaying Noise with:\nfrequency = %s%dHz\n%svolume = %s%d\n%span = %s%d%s",Color_Text, Color_Green, freq, Color_Text, Color_Red, volume, Color_Text, Color_Yellow, pan, Color_Text);
	} else {
		iprintf("%sPlaying PSG with:\nfrequency = %s%dHz\n%svolume = %s%d\n%span = %s%d%s",Color_Text, Color_Green, freq, Color_Text, Color_Red, volume, Color_Text, Color_Yellow, pan, Color_Text);
	}

	if(play) {
		soundPause(channel);
		soundSetFreq(channel, freq);
		soundSetVolume(channel, volume);
		soundSetPan(channel, pan);

	}
	else {
		soundResume(channel);
	}

	play = !play;

	//freq += 100; //Increase by 100Hz each call

	// if(freq > MAX_FREQ) {
	// 	soundKill(channel);
	// 	timerStop(0);
	// 	freq=MIN_FREQ;
	// 	iprintf("\nFinished playing until frqeuency 20KHz");
	// }


}

void playPSG(void) {
	topScreenAndConsole();

	type = 0;
	
	soundEnable();

	channel = soundPlayPSG(DutyCycle_50, freq, volume, pan);

	//calls the timerCallBack function 2 times per second.
	timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(5), timerCallBack);

	waitfor(KEY_A);

}
void playNoise(void) {

	topScreenAndConsole();

	type = 1;

	soundEnable();
	
	channel = soundPlayNoise(freq, volume, pan);
	//calls the timerCallBack function 2 times per second.
	timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(5), timerCallBack);

	waitfor(KEY_A);
	 
}


void waitfor(int keys)
{
	scanKeys();
	while((keysDown() & keys & KEY_A) == 0)
	{
		swiWaitForVBlank();
		scanKeys();
		keys = keysDown();
			
		if(keys & KEY_RIGHT) selected++;
		if(keys & KEY_LEFT) selected--;

		if(selected < 0) selected=0;
		if(selected >= 2) selected=2;


		if(keys & KEY_UP) {
			switch(selected) {
				case 0:
					freq+=100;
					break;
				case 1:
					volume+=10;
					break;
				case 2:
					pan += 10;
					break;
			}
		}
		if(keys & KEY_DOWN) {
			switch(selected) {
				case 0:
					freq-=100;
					break;
				case 1:
					volume-=10;
					break;
				case 2:
					pan -= 10;
					break;
			}

		}

		if(freq < 0) freq = MIN_FREQ;
		if(freq > MAX_FREQ) freq = MAX_FREQ;

		if(volume < 0) volume = MIN_VOL;
		if(volume > MAX_VOL) volume = MAX_VOL;

		if(pan < 0) pan = PAN_LEFT;
		if(pan > PAN_RIGHT) pan = PAN_RIGHT;

	}

	soundKill(channel);
	timerStop(0);
	freq = MIN_FREQ;
	volume = 64;
	pan = PAN_CENTER;
	selected = 0;
 	iprintf("\nPlaying halted");
}
