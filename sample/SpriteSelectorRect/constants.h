#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stddef.h>

typedef unsigned char byte;

#define TANKS_COUNT 2
#define OBJECTS_COUNT 32
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int SCREEN_FPS = 60;
constexpr int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
constexpr int SCALE_FACTOR = 3;

constexpr int PLAYER_TANK_A_CLIP_X = 1;
constexpr int PLAYER_TANK_A_CLIP_Y = 2;
constexpr size_t PLAYER_TANK_A_CLIP_W = 13;
constexpr size_t PLAYER_TANK_A_CLIP_H = 12;

constexpr int ENEMY1_TANK_A_CLIP_X = 129;
constexpr int ENEMY1_TANK_A_CLIP_Y = 2;
constexpr size_t ENEMY1_TANK_A_CLIP_W = PLAYER_TANK_A_CLIP_W;
constexpr size_t ENEMY1_TANK_A_CLIP_H = PLAYER_TANK_A_CLIP_H;

constexpr int BLOCKS_CLIP_X = 256;
constexpr int BLOCKS_CLIP_Y = 16;
constexpr size_t BLOCKS_CLIP_W = 16;
constexpr size_t BLOCKS_CLIP_H = 16;

constexpr int PROJECTILE_CLIP_X = 323;
constexpr int PROJECTILE_CLIP_Y = 102;
constexpr int PROJECTILE_CLIP_W = 3;
constexpr int PROJECTILE_CLIP_H = 4;
constexpr int PROJECTILE_CLIP_CENTER_X =
    (PROJECTILE_CLIP_W * SCALE_FACTOR) / 2;
constexpr int PROJECTILE_CLIP_CENTER_Y =
    (PROJECTILE_CLIP_H * SCALE_FACTOR) / 2;

constexpr int EXPLOSION0_TANK_A_CLIP_X = 256;
constexpr int EXPLOSION0_TANK_A_CLIP_Y = 128;
constexpr size_t EXPLOSION0_TANK_A_CLIP_W = 16;
constexpr size_t EXPLOSION0_TANK_A_CLIP_H = 16;

constexpr int EXPLOSION1_TANK_A_CLIP_X = 272;
constexpr int EXPLOSION1_TANK_A_CLIP_Y = 128;
constexpr size_t EXPLOSION1_TANK_A_CLIP_W = 16;
constexpr size_t EXPLOSION1_TANK_A_CLIP_H = 16;

constexpr int EXPLOSION2_TANK_A_CLIP_X = 289;
constexpr int EXPLOSION2_TANK_A_CLIP_Y = 128;
constexpr size_t EXPLOSION2_TANK_A_CLIP_W = 16;
constexpr size_t EXPLOSION2_TANK_A_CLIP_H = 16;

constexpr int EXPLOSION3_TANK_A_CLIP_X = 304;
constexpr int EXPLOSION3_TANK_A_CLIP_Y = 128;
constexpr size_t EXPLOSION3_TANK_A_CLIP_W = 30;
constexpr size_t EXPLOSION3_TANK_A_CLIP_H = 29;

constexpr int EXPLOSION4_TANK_A_CLIP_X = 334;
constexpr int EXPLOSION4_TANK_A_CLIP_Y = 128;
constexpr size_t EXPLOSION4_TANK_A_CLIP_W = 34;
constexpr size_t EXPLOSION4_TANK_A_CLIP_H = 32;

constexpr int PROJECTILE_SPEED = 2 * SCALE_FACTOR;
constexpr int PROJECTILE_TTL = 500; // Milliseconds


/// Sprite 
constexpr int WATER_SPRITE_1_X = 256;
constexpr int WATER_SPRITE_1_Y = 32;
constexpr int WATER_SPRITE_1_W = 16;
constexpr int WATER_SPRITE_1_H = 16;

constexpr int WATER_SPRITE_2_X = 256;
constexpr int WATER_SPRITE_2_Y = 32+16;
constexpr int WATER_SPRITE_2_W = 16;
constexpr int WATER_SPRITE_2_H = 16;

constexpr int WATER_SPRITE_3_X = 256+16;
constexpr int WATER_SPRITE_3_Y = 32+15;
constexpr int WATER_SPRITE_3_W = 16;
constexpr int WATER_SPRITE_3_H = 16;

#endif
