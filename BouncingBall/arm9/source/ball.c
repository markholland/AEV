#include <nds.h>
#include "ball.h"

#define c_radius (8<<8)

//-----------------------------------------------------------------
// update ball object (call once per frame)
//-----------------------------------------------------------------
void ballUpdate( ball* b )
//-----------------------------------------------------------------
{
    // add X velocity to X position
    b->x += (b->xvel>>4);

     // apply air friction to X velocity
    b->xvel = (b->xvel * (256-c_air_friction)) >> 8;
    
    // clamp X velocity to the limits
    b->xvel = clampint( b->xvel, -max_xvel, max_xvel );

    // add gravity to Y velocity
    b->yvel += c_gravity;
    
    // add Y velocity to Y position
    b->y += (b->yvel);

    if( b->y + c_radius >= c_platform_level )
    {
        // apply ground friction to X velocity
        // (yes this may be done multiple times)
        b->xvel = (b->xvel * (256-c_ground_friction)) >> 8;
        
        // check if the ball has been squished to minimum height
        if( b->y > c_platform_level - min_height )
        {
            // mount Y on platform
            b->y = c_platform_level - min_height;
            
            // negate Y velocity, also apply the bounce damper
            b->yvel = -(b->yvel * (256-c_bounce_damper)) >> 8;
        
            // clamp Y to mininum velocity (minimum after bouncing, so the ball does not settle)
            if( b->yvel > -min_yvel )
                b->yvel = -min_yvel;
        }
       
        // calculate the height
        b->height = (c_platform_level - b->y) * 2;
    }
    else
    {
        b->height = c_diam << 8;
    }
}

void ballRender( ball* b, int camera_x, int camera_y )
{
    u16* sprite = OAM + b->sprite_index * 4;

    int x, y;
    x = ((b->x - c_radius * 2) >> 8) - camera_x;
    y = ((b->y - c_radius * 2) >> 8) - camera_y;

    // check if renedering out of bounds before continuing
    if( x <= -16 || y <= -16 || x >= 256 || y >= 192 )
    {
        // sprite is out of bounds
        // disable the sprite
        sprite[0] = ATTR0_DISABLED;
        return;
    }

    sprite[0] = (y & 255) | ATTR0_ROTSCALE_DOUBLE;
    sprite[1] = (x & 511) | ATTR1_SIZE_16 | ATTR1_ROTDATA( b->sprite_affine_index );
    sprite[2] = 0;

    u16* affine;
    affine = OAM + b->sprite_affine_index * 16 + 3;
    affine[4] = 0; // PB and PC aren't used with scaling
    affine[8] = 0;

    int pa = (b->height * (65536/c_diam)) >> 16;
    int pd = 65536 / pa;

    affine[0] = pa;
    affine[12] = pd;
    
}