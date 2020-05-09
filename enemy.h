#ifndef ENEMY_H
#define ENEMY_H

#include "config.h"
#include <QPixmap>
#include "enemybullet.h"

class Enemy
{
public:
    Enemy();

    QPixmap pic;
    QRect rect;
    EnemyBullet bul[BUL_NUM];
    QPixmap pic_death;
    bool death;

    int x;
    int y;
    int speed;
    bool free;
    int recorder;
    void shoot();
    void explode();
    void updatePosistion();
    void allDeath();
};

#endif // ENEMY_H
