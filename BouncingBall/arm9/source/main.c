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

#define bg0map    ((u16*)BG_MAP_RAM(1))
#define bg1map    ((u16*)BG_MAP_RAM(2))

/* sprite */

#define tiles_ball      0 // ball tiles (16x16 tile 0->3)

#define tile2objram(t) (SPRITE_GFX + (t) * 16)

#define pal2objram(p) (SPRITE_PALETTE + (p) * 16)
#define pal_ball      0 // ball palette (entry 0->15)

typedef struct t_spriteEntry
{
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 affine_data;
} spriteEntry;

#define sprites ((spriteEntry*)OAM)

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

		/* Bricks */

		// libnds prefixes the register names with REG_
		REG_BG0CNT = BG_MAP_BASE(1);
		REG_BG1CNT = BG_MAP_BASE(2);
		REG_BG0VOFS = 112; // offset down vertically 112 pixels

		// Clear brick tilemap to zero
		for( n = 0; n < 1024; n++ )
        	bg0map[n] = 0;

        // Draw 32x6 image of bricks
        int x, y;
	    for( x = 0; x < 32; x++ )
	    {
	        for( y = 0; y < 6; y++ )
	        {
	            // magical formula to calculate if the tile needs to be flipped.
	            int hflip = (x & 1) ^ (y & 1);
	            
	            // set the tilemap entry
	            bg0map[x + y * 32] = tile_brick | (hflip << 10) | (pal_bricks << 12);
	        }
	    }

	    /* Gradient */

	    for( n = 0; n < 1024; n++ )
        	bg1map[n] = 0;

        for( x = 0; x < 32; x++ )
	    {
	        for( y = 0; y < 8; y++ )
	        {
	            int tile = tile_gradient + y;
	            bg1map[ x + y * 32 ] = tile | (pal_gradient << 12);
	        }
	    }

	    /* Blend BG1 */

	    REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG1 | BLEND_DST_BACKDROP;
    	REG_BLDALPHA = (4) + (16<<8);


    	/* Sprite */

    	// copy graphic
    	dmaCopyHalfWords( 3, gfx_ballTiles, tile2objram(tiles_ball), gfx_ballTilesLen );

    	// copy palette
    	dmaCopyHalfWords( 3, gfx_ballPal, pal2objram(pal_ball), gfx_ballPalLen );

    	// disable sprite entries
    	for( n = 0; n < 128; n++ )
        	sprites[n].attr0 = ATTR0_DISABLED;

        // code to test out the sprite engine
	    for( n = 0; n < 50; n++ )
	    {
	        // attribute0: set vertical position 0->screen_height-sprite_height, 
	        // other default options will be okay (default == zeroed)
	        sprites[n].attr0 = rand() % (192 - 16);

	        // attribute1: set horizontal position 0->screen_width-sprite_width
	        // also set 16x16 size mode
	        sprites[n].attr1 = (rand() % (256 - 16)) + ATTR1_SIZE_16;

	        // attribute2: select tile number and palette number
	        sprites[n].attr2 = tiles_ball + (pal_ball << 12);
	    }

	}

	while(1) {
		
		setupGraphics();

		// wait for the vblank period
		swiWaitForVBlank();
		videoSetMode( MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT );
	}

	return 0;
}

