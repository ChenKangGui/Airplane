#include "finalhit.h"

FinalHit::FinalHit()
{
    finalHit.load(HEROPLANE_PATH);

    x = 0;
    y = 0;
    rect.setWidth(finalHit.width());
    rect.setHeight(finalHit.height());
    rect.moveTo(x, y);

    free = true;
    speed = FINALHIT_SPEED;
}

void FinalHit::updatePosistion()
{
    if(free)
    {
        return ;
    }

    y -= speed;
    rect.moveTo(x, y);
    if(y <= -GAME_HEIGTH)
    {
        free = true;
    }
}
