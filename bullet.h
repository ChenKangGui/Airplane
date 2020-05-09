#ifndef BULLET_H
#define BULLET_H

#include "config.h"
#include <QPixmap>

class bullet
{
public:
    bullet();

    QPixmap m_bullet;
    QRect rect;

    int x;
    int y;
    int speed;
    bool free;
    void setPosistion();
};

#endif // BULLET_H

