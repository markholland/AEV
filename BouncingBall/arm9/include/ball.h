// ball.h

#ifndef BALL_H
#define BALL_H

typedef struct t_ball
{
    int x;     // 24.8 fixed point
    int y;     // 24.8 fixed point 
    int xvel;  // 20.12 fixed point
    int yvel;  // 24.8 fixed point
    
    u8  sprite_index;        // OAM entry (0->127)
    u8  sprite_affine_index; // OAM affine entry (0->31)
    
    int height; // height of ball
} ball;

void ballUpdate( ball* b );
void ballRender( ball* b, int camera_x, int camera_y );

#define c_gravity           80                 // gravity constant (add to vertical velocity) (*.8 fixed)

#define c_air_friction      1                  // friction in the air... multiply X velocity by (256-f)/256
#define c_ground_friction   30                 // friction when the ball hits the ground, multiply X by (256-f)/256
#define c_platform_level    ((192-48) << 8)    // the level of the brick platform in *.8 fixed point
#define c_bounce_damper     20                 // the amount of Y velocity that is absorbed when you hit the ground
	
#define c_radius            (8<<8)             // the radius of the ball in *.8 fixed point
#define c_diam              16                 // the diameter of the ball (integer)

#define min_height          (1200)             // the minimum height of the ball (when it gets squished) (*.8)

#define min_yvel            (1200)             // the minimum Y velocity (*.8)
#define max_xvel            (1000<<4)          // the maximum X velocity (*.12)

//-----------------------------------------------------------------
// clamp integer to range
//-----------------------------------------------------------------
static inline int clampint( int value, int low, int high )
//-----------------------------------------------------------------
{
    if( value < low ) value = low;
    if( value > high) value = high;
    return value;
}

#endif