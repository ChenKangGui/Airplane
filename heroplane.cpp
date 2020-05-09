#include "heroplane.h"
#include "config.h"
#include <stdio.h>
#include <QDebug>
#include "bullet.h"
#include "mainscene.h"

HeroPlane::HeroPlane()
{
    plane.load(HEROPLANE_PATH);
    plane_death.load(PLANEDEATH_PATH);
    x = (GAME_WIDTH - plane.width())*0.5;
    y = GAME_HEIGTH - plane.height();

    rect.setWidth(plane.width());
    rect.setHeight(plane.height());
    rect.moveTo(x, y);

    death_rect.setWidth(plane.width());
    death_rect.setHeight(plane.height());
    death_rect.moveTo(x, y);

    finahit_num = FINALHIT_NUM;
    death = false;
    life = 20;
}


void HeroPlane::shoot()
{
    for(int i=0; i<BULLET_NUM; i++)
    {
        if(m_bullet[i].free)
        {
            m_bullet[i].free = false;
            m_bullet[i].x = x+20;
            m_bullet[i].y = y;
            m_bullet[i].rect.moveTo(m_bullet[i].x, m_bullet[i].y);
            break;
        }
    }
}

void HeroPlane::final_hit()
{
    for(int i=0; i<TOTAL_FINALHIT; i++)
    {
        if(m_finalhit[i].free)
        {
            for(int j=0; j<ONCE_FINALHIT; j++)
            {
                m_finalhit[i+j].free = false;

                m_finalhit[i+j].x = 105 * j;
                qDebug() << m_finalhit[i+j].x;
                m_finalhit[i+j].y = GAME_HEIGTH - m_finalhit[i].rect.height();
            }
            break;
        }
    }
}
