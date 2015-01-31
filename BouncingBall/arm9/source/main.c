#include <nds.h>

int main ( void )
{
	irqInit();					// initialize interrupts
	irqEnable(  IRQ_VBLANK);	// enable vblank interrupt
	while(1)
		swiWaitForVBlank();		// wait for next VBlank AND halt the cpu

	return 0;
}

