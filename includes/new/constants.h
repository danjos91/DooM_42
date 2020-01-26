#ifndef CONSTANTS_H
# define CONSTANTS_H
/* Define window size */
# define WIN_W 1280
# define WIN_H 720
/* Define various vision related constants */
#define EYE_H  6    //Camera height from floor when standing
#define CROUCH_H 2.5  //And when crouching
#define HEAD_H 1    //How much room there is above camera before the head hits the ceiling
#define NOT_JUMP_H 2    //How tall obstacles the player can simply walk over without jumping
#define HOR_FOV (0.73f * WIN_H)  //Affects the horizontal field of vision
#define VER_FOV (.2f * WIN_H)    //Affects the vertical field of vision
#define MAX_QUEUE 32 //maximum number of pending portal renders (engine)
#define MAX_DOORS 100 //maximum number of doors
#define MAX_BUT 100 //maximum number of buttons

#endif