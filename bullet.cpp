#include "bullet.h"

bullet::bullet()
{
    m_bullet.load(BULLET_PATH);    
    x = 0;
    y = 0;
    free = true;

    rect.setWidth(m_bullet.width());
    rect.setHeight(m_bullet.height());
    rect.moveTo(x, y);
}

void bullet::setPosistion()
{
    if(free)
    {
        return ;
    }
    y -= BULLET_SPEED;
    rect.moveTo(x, y);

    if(y < 0)
    {
        free = true;
    }
}


