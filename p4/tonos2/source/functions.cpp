#include <nds.h>

#include <stdio.h>
#include <stdlib.h>

#include <inttypes.h>

#include <system.h>

const int MIN_FREQ = 20;
const int MAX_FREQ = 20000;

void topScreenAndConsole(void) {

	videoSetMode(MODE_0_2D);
	consoleInit(0,0,BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true);	
}

int channel = 0;
bool play = true;
int freq=MIN_FREQ; // start in 20Hz

void waitfor(int keys)
{
	scanKeys();
	while((keysDown() & keys) == 0)
	{
		swiWaitForVBlank();
		scanKeys();
	}

	soundKill(channel);
	timerStop(0);
	freq=MIN_FREQ;
	iprintf("\nPlaying halted");
}

//this function will be called by the timer.
void timerCallBack()
{

	consoleClear();
	iprintf("Playing PSG with \nfrequency = %dHz\n",freq);

	if(play) {
		soundPause(channel);
		soundSetFreq(channel, freq); // Update frequency
	}
	else {
		soundResume(channel);
	}

	play = !play;

	freq += 100; //Increase by 100Hz each call

	if(freq > MAX_FREQ) {
		soundKill(channel);
		timerStop(0);
		freq=MIN_FREQ;
		iprintf("\nFinished playing until frqeuency 20KHz");
	}


}

void playPSG(void) {
	topScreenAndConsole();
	
	soundEnable();

	channel = soundPlayPSG(DutyCycle_50, freq, 127, 64);

	//calls the timerCallBack function 2 times per second.
	timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(5), timerCallBack);

	waitfor(KEY_A);

}
void playNoise(void) {
	topScreenAndConsole();
	iprintf("hello");
	 
}
