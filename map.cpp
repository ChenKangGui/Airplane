#include "map.h"
#include "config.h"

Map::Map()
{
    map1.load(MAP_PATH);
    map2.load(MAP_PATH);

    map1_y = 0;
    map2_y = -GAME_HEIGTH;
}

void Map::updataPosistion()
{
    map1_y += MAP_SPEED;
    if(map1_y >= GAME_HEIGTH)
    {
        map1_y = 0;
    }

    map2_y += MAP_SPEED;
    if(map2_y >= 0)
    {
        map2_y = -GAME_HEIGTH;
    }
}
