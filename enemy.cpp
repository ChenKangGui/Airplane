#include "enemy.h"
#include <QDebug>
#include <QBitmap>

Enemy::Enemy()
{
    pic.load(ENEMY_PATH);
    pic_death.load(ENEMYDEATH_PATH);
    x = 0;
    y = 0;
    rect.setWidth(pic.width());
    rect.setHeight(pic.height());
    rect.moveTo(x, y);

    free = true;
    death = false;
    speed = ENEMY_SPEED;
    recorder = 0;

    QBitmap mask =  pic.createMaskFromColor(QColor(255,255,255),Qt::MaskInColor);
    pic.setMask(mask);
}

void Enemy::shoot()
{
    if(free)
    {
        return ;
    }
    for(int i=0; i<BUL_NUM; i++)
    {
        if(bul[i].free)
        {
            bul[i].free = false;
            bul[i].x = x+20;
            bul[i].y = y+60;
            bul[i].rect.moveTo(bul[i].x, bul[i].y);
            break;
        }
    }
}

void Enemy::explode()
{

}

void Enemy::updatePosistion()
{
    if(free)
    {
        return ;
    }

    if(x > GAME_WIDTH || y > GAME_HEIGTH)
    {
        free = true;
        return ;
    }
    x += speed;
    y += 10;
    if(x < 0)
    {
        speed = ENEMY_SPEED;
    }
    else if(x > GAME_WIDTH-rect.width())
    {
        speed = -ENEMY_SPEED;
    }

    rect.moveTo(x, y);
}

void Enemy::allDeath()
{
    free = true;
    death = true;
}

