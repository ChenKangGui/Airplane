#ifndef CONFIG_H
#define CONFIG_H

enum Direction
{
    DOWN,
    UP,
    LEFT,
    RIGHT
};

#define ENEMYBULLET_INTERVAL 5
#define ENEMY_APPEAR 50
#define ENEMY_NUM 15
#define ENMEY_INTERVAL 30
#define BUL_NUM 30
#define BUL_SPEED 5
#define MAP_SPEED 2
#define GAME_RATE 10
#define ENEMY_SPEED 5
#define BULLET_NUM 5
#define BUL_INTERVAL 20
#define GAME_WIDTH 480
#define PLANE_SPEED 10
#define GAME_HEIGTH 650
#define BULLET_SPEED 5
#define ONCE_FINALHIT 5
#define FINALHIT_NUM  10
#define TOTAL_FINALHIT 50
#define FINALHIT_SPEED 10

#define GAME_TITLE "飞机大战"
#define MAP_PATH ":/res/map.jpg"
#define GAME_ICO ":/res/game.ico"
#define BULLET_PATH ":/res/bullet.png"
#define ENEMY_PATH  ":/res/1.png"
#define HEROPLANE_PATH ":/res/heroplane.png"
#define PLANEDEATH_PATH ":/res/plane_death.png"
#define ENEMYDEATH_PATH ":/res/enemy_death.png"
#define ENEMYBULLET_PATH ":/res/enemy_bullet.png"

#endif // CONFIG_H
