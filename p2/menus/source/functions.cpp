#include <nds.h>

#include <system.h>

void LCDMainOnBottom(void) {
	lcdMainOnBottom();

}
void LCDMainOnTop(void) {
	lcdMainOnTop();
}
void LCDSwap(void) {
	lcdSwap();
}
void LEDBlink(void) {
	ledBlink(10);
}
void SystemShutDown(void) { 
	systemShutDown();
}
void SystemSleep(void) {
	systemSleep();
}
