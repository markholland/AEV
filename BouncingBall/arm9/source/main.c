#include <nds.h>

int main ( void )
{
	irqInit();					// initialize interrupts
	irqEnable(  IRQ_VBLANK);	// enable vblank interrupt

	vramSetBankE( VRAM_E_MAIN_BG ); 	// set vram E to use main engine BG setting
	vramSetBankF( VRAM_F_MAIN_SPRITE ); // set vram F to use main engine OBJ setting

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

