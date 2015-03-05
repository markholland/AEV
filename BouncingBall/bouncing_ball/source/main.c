#include <nds.h>
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"

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

/* The ball */
#include "ball.h"

ball g_ball;

/* Key input */
#define x_tweak    (2<<8)  // for user input
#define y_tweak    25      // for user input

/* camera */
int g_camera_x;
int g_camera_y;

//-----------------------------------------------------------
// setup interrupt handler with vblank irq enabled
//-----------------------------------------------------------
void setupInterrupts( void )
//-----------------------------------------------------------
{
    // initialize interrupt handler
    irqInit();
    
    // enable vblank interrupt (required for swiWaitForVBlank!)
    irqEnable( IRQ_VBLANK );
}

//-----------------------------------------------------------
// reset ball attributes
//-----------------------------------------------------------
void resetBall( void )
//-----------------------------------------------------------
{
    // use sprite index 0 (0->127)
    g_ball.sprite_index = 0;
    
    // use affine matrix 0 (0->31)
    g_ball.sprite_affine_index = 0;
    
    // X = 128.0
    g_ball.x = 128 << 8;
    
    // Y = 64.0
    g_ball.y = 64 << 8;
   
    // start X velocity a bit to the right
    g_ball.xvel = 100 << 4;
   
    // reset Y velocity
    g_ball.yvel = 0;
}

void setupGraphics( void ) {
        vramSetBankE( VRAM_E_MAIN_BG );     // set vram E to use main engine BG setting
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

        
    }

void processInput( void )
{
    scanKeys();

    int keysh = keysHeld();
    // process user input
    if( keysh & KEY_UP )      // check if UP is pressed
    {
        // tweak y velocity of ball
        g_ball.yvel -= y_tweak;
    }
    if( keysh & KEY_DOWN )    // check if DOWN is pressed
    {
        // tweak y velocity of ball
        g_ball.yvel += y_tweak;
    }
    if( keysh & KEY_LEFT )    // check if LEFT is pressed
    {
        // tweak x velocity
        g_ball.xvel -= x_tweak;
    }
    if( keysh & KEY_RIGHT )   // check if RIGHT is pressed
    {
        // tweak y velocity
        g_ball.xvel += x_tweak;
    }
}

void updateCamera( void )
{
    // cx = desired camera X
    int cx = ((g_ball.x)) - (128 << 8);
    
    // dx = difference between desired and current position
    int dx;
    dx = cx - g_camera_x;
    
    // 10 is the minimum threshold
    if( dx > 10 || dx < -10 )
        dx = (dx * 50) >> 10; // scale the value by some amount
    
    // add the value to the camera X position
    g_camera_x += dx;
    
    // camera Y is always 0
    g_camera_y  = 0;
}

//-----------------------------------------------------------
// update graphical information (call during vblank)
//-----------------------------------------------------------
void updateGraphics( void )
//-----------------------------------------------------------
{
    // update ball sprite
    ballRender( &g_ball, g_camera_x >> 8, g_camera_y >> 8 );
    
    REG_BG0HOFS = g_camera_x >> 8;
}

void processLogic( void ) {

    processInput();
    ballUpdate( &g_ball );
    updateCamera();
}

//-----------------------------------------------------------
// program entry point
//-----------------------------------------------------------
int main( void )
//-----------------------------------------------------------
{
    // setup things
    setupInterrupts();
    setupGraphics();
    resetBall();

    videoSetMode( MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT );

    // Theme song
    mmInitDefaultMem((mm_addr)soundbank_bin);
    
    // load the module
    mmLoad( MOD_FLATOUTLIES );

    // Start playing module
    mmStart( MOD_FLATOUTLIES, MM_PLAY_LOOP );

    // load sound effect
    mmLoadEffect( SFX_BALL_BOUNCE );

    mm_sound_effect ball_bounce = {
        { SFX_BALL_BOUNCE } ,         // id
        (int)(1.0f * (1<<10)),  // rate
        0,      // handle
        255,    // volume
        0,      // panning
    };

    // start main loop
    while( 1 )
    {
        // update game logic
        processLogic();

        // wait for new frame
        swiWaitForVBlank();

        // update graphics
        updateGraphics();
    }
    return 0;
}

