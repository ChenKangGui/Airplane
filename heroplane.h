#ifndef HEROPLANE_H
#define HEROPLANE_H

#include "config.h"
#include <QPixmap>
#include <QKeyEvent>
#include "bullet.h"
#include "finalhit.h"

class HeroPlane
{
public:
    HeroPlane();

    QPixmap plane;
    QPixmap plane_death;
    QRect rect;
    QRect death_rect;
    int x;
    int y;
    int life;
    bool death;
    void shoot();
    void final_hit();

    bullet m_bullet[BULLET_NUM];
    FinalHit m_finalhit[TOTAL_FINALHIT];
    int finahit_num;
};

#endif // HEROPLANE_H
