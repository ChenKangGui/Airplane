#include "enemybullet.h"
#include "config.h"

EnemyBullet::EnemyBullet()
{
    m_bullet.load(ENEMYBULLET_PATH);

    x = 50;
    y = 0;
    rect.setWidth(m_bullet.width());
    rect.setHeight(m_bullet.height());
    rect.moveTo(x, y);

    speed = BULLET_SPEED;
    free = true;
}

void EnemyBullet::setPosistion()
{
    if(free)
    {
        return ;
    }

    y += BULLET_SPEED;
    rect.moveTo(x, y);
}

void EnemyBullet::allDisappear()
{
    free = true;
}
