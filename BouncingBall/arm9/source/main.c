#include <nds.h>

int main ( void )
{
	irqInit();					// initialize interrupts
	irqEnable(  IRQ_VBLANK);	// enable vblank interrupt
	
	while(1) {
		/* Rendering period: */
		// update game objects
		update_logic();

		// wait for the vblank period
		swiWaitForVBlank();		// halts the cpu

		/* VBlank Period: */
		// move the graphics around
		update_graphics();
	}
}

