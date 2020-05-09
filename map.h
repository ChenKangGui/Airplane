#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class Map
{
public:
    Map();

    QPixmap map1;
    QPixmap map2;

    int map1_y;
    int map2_y;

    int speed;

    void updataPosistion();
};

#endif // MAP_H
