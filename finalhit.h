#ifndef FINALHIT_H
#define FINALHIT_H

#include "finalhit.h"
#include <QPixmap>
#include "config.h"

class FinalHit
{
public:
    FinalHit();

    QPixmap finalHit;
    QRect rect;
    int x;
    int y;
    int speed;
    bool free;
    void updatePosistion();
};

#endif // FINALHIT_H
