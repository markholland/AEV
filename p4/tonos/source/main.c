#include <nds.h>

void waitfor(int keys)
{
	scanKeys();
	while((keysDown() & keys) == 0)
	{
		swiWaitForVBlank();
		scanKeys();
	}
}


int channel = 0;
bool play = true;
int freq=20; // start in 20Hz

//this function will be called by the timer.
void timerCallBack()
{
	if(play) {
		soundPause(channel);
		soundSetFreq(channel, freq); // Update frequency
	}
	else {
		soundResume(channel);
	}

	play = !play;

	freq += 100; //Increase by 100Hz each call


}

int main()
{
	
	soundEnable();

	channel = soundPlayPSG(DutyCycle_50, freq, 127, 64);

	//calls the timerCallBack function 2 times per second.
	timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(5), timerCallBack);

	waitfor(KEY_A);

	return 0;
}
