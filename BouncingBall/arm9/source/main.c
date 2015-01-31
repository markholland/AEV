#include <nds.h>

//-----------------------------------------------
// graphic references
//-----------------------------------------------
#include "gfx_ball.h"
#include "gfx_brick.h"
#include "gfx_gradient.h"

//-----------------------------------------------
// tile entries
//-----------------------------------------------

#define tile_empty     0 // tile 0 = empty
#define tile_brick     1 // tile 1 = brick
#define tile_gradient  2 // tile 2 to 9 = gradient

// macro for calculating BG VRAM memory
// address with tile index
#define tile2bgram(t) (BG_GFX + (t) * 16)

// BG PALETTES
#define pal_bricks        0    // brick palette (entry 0->15)
#define pal_gradient      1    // gradient palette (entry 16->31)

#define backdrop_colour   RGB8( 190, 225, 255 )
#define pal2bgram(p)      (BG_PALETTE + (p) * 16)

int main ( void )
{
	irqInit();					// initialize interrupts
	irqEnable(  IRQ_VBLANK);	// enable vblank interrupt

	void setupGraphics( void ) {
		vramSetBankE( VRAM_E_MAIN_BG ); 	// set vram E to use main engine BG setting
		vramSetBankF( VRAM_F_MAIN_SPRITE ); // set vram F to use main engine OBJ setting
		
		// generate the first blank tile by clearing it to zero
    	int n;
    	for( n = 0; n < 16; n++ )
        	BG_GFX[n] = 0;
    
	    // copy bg graphics
	    dmaCopyHalfWords( 3, gfx_brickTiles, tile2bgram( tile_brick ), gfx_brickTilesLen );
	    dmaCopyHalfWords( 3, gfx_gradientTiles, tile2bgram( tile_gradient ), gfx_gradientTilesLen );

	    // palettes goto palette memory
		dmaCopyHalfWords( 3, gfx_brickPal, pal2bgram(pal_bricks), gfx_brickPalLen );
		dmaCopyHalfWords( 3, gfx_gradientPal, pal2bgram(pal_gradient), gfx_gradientPalLen );

		// set backdrop color
		BG_PALETTE[0] = backdrop_colour;
	}

	while(1) {
		
		setupGraphics();

		// wait for the vblank period
		swiWaitForVBlank();
		videoSetMode( MODE_0_2D );		
	}

	return 0;
}

