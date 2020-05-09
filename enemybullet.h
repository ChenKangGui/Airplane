#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include <QPixmap>
#include "bullet.h"

class EnemyBullet : public bullet
{
public:
    EnemyBullet();

    void setPosistion();
    void allDisappear();
};

#endif // ENEMYBULLET_H
